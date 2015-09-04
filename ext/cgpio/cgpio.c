#include <ruby.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>

/* direction types */
#define GPIO_OUTPUT 0x01
#define GPIO_INPUT 0x02

/* register addresses */
#define GPIO0_ADDR 0x44E07000
#define GPIO1_ADDR 0x4804C000
#define GPIO2_ADDR 0x481AC000
#define GPIO3_ADDR 0x481AF000

/* register offsets */
#define OE_ADDR (0x134 / 4)
#define GPIO_DATAOUT (0x13C / 4)
#define GPIO_DATAIN (0x138 / 4)

struct Cgpio
{
    int nr;
    ulong *pinconf;
    int offset;
};

struct GlobalConfig
{
    ulong *pinconfs[4];
} config;

static VALUE
cgpio_setup(VALUE self, VALUE p_nr)
{
    struct Cgpio *ptr;
    int nr;

    nr = FIX2INT(p_nr);

    Data_Get_Struct(self, struct Cgpio, ptr);

    // precalculate some stuff
    ptr->nr = nr;
    ptr->pinconf = config.pinconfs[nr / 32];
    ptr->offset = 1 << (nr % 32);

    return self;
}

static VALUE
cgpio_set_direction(VALUE self, VALUE dir)
{
    struct Cgpio *ptr;

    Data_Get_Struct(self, struct Cgpio, ptr);

    if (NUM2INT(dir) == GPIO_OUTPUT)
        ptr->pinconf[OE_ADDR] &= ~ptr->offset;
    else
        ptr->pinconf[OE_ADDR] |= ptr->offset;

    return self;
}

static VALUE
cgpio_get_direction(VALUE self)
{
    struct Cgpio *ptr;

    Data_Get_Struct(self, struct Cgpio, ptr);

    if (ptr->pinconf[OE_ADDR] & ptr->offset)
        return INT2NUM(GPIO_INPUT);
    else
        return INT2NUM(GPIO_OUTPUT);
}

static VALUE
cgpio_set_value(VALUE self, VALUE p_value)
{
    struct Cgpio *ptr;

    Data_Get_Struct(self, struct Cgpio, ptr);

    if (p_value == Qtrue)
        ptr->pinconf[GPIO_DATAOUT] |= ptr->offset;
    else if (p_value == Qfalse)
        ptr->pinconf[GPIO_DATAOUT] &= ~ptr->offset;
    else
        rb_raise(rb_eRuntimeError, "gpio value have to be true or false");

    return p_value;
}

static VALUE
cgpio_get_value(VALUE self)
{
    struct Cgpio *ptr;

    Data_Get_Struct(self, struct Cgpio, ptr);

    if (ptr->pinconf[GPIO_DATAIN] & ptr->offset)
        return Qtrue;
    else
        return Qfalse;
}

static VALUE
cgpio_alloc(VALUE klass)
{
    VALUE obj;
    struct Cgpio *ptr;

    obj = Data_Make_Struct(klass, struct Cgpio, NULL, NULL, ptr);

    return obj;
}

void
Init_cgpio()
{
    VALUE module_Cgpio;
    VALUE class_RealGpio;
    int fd;

    // get module
    module_Cgpio = rb_const_get(rb_cObject, rb_intern("Cgpio"));

    // get class
    class_RealGpio = rb_const_get(module_Cgpio, rb_intern("RealGpio"));

    rb_define_alloc_func(class_RealGpio, cgpio_alloc);
    rb_define_private_method(class_RealGpio, "setup", cgpio_setup, 1);
    rb_define_private_method(class_RealGpio, "set_direction", cgpio_set_direction, 1);
    rb_define_private_method(class_RealGpio, "get_direction", cgpio_get_direction, 0);
    rb_define_method(class_RealGpio, "value=", cgpio_set_value, 1);
    rb_define_method(class_RealGpio, "value", cgpio_get_value, 0);

    fd = open("/dev/mem",O_RDWR | O_SYNC);
	if (fd == -1)
	{
		rb_raise(rb_eRuntimeError, "could not open /dev/mem (used for gpio memory mapping)");
		return;
	}

    // map all the gpio memory addresses
    config.pinconfs[0] = (ulong*) mmap(NULL, 0x1000, PROT_READ | PROT_WRITE,
		MAP_SHARED, fd, GPIO0_ADDR);

    config.pinconfs[1] = (ulong*) mmap(NULL, 0x1000, PROT_READ | PROT_WRITE,
		MAP_SHARED, fd, GPIO1_ADDR);

    config.pinconfs[2] = (ulong*) mmap(NULL, 0x1000, PROT_READ | PROT_WRITE,
		MAP_SHARED, fd, GPIO2_ADDR);

    config.pinconfs[3] = (ulong*) mmap(NULL, 0x1000, PROT_READ | PROT_WRITE,
		MAP_SHARED, fd, GPIO3_ADDR);
}
