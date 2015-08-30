#include <ruby.h>
#include "gpio.h"

struct Cgpio
{
    struct Gpio *gpio;
};

static VALUE
cgpio_setup(VALUE self, VALUE p_port)
{
    struct Cgpio *ptr;
    struct Gpio *gpio;

    int port = NUM2INT(p_port);

    Data_Get_Struct(self, struct Cgpio, ptr);

    gpio = gpio_setup(port);

    if (gpio == NULL)
            rb_raise(rb_eRuntimeError, "unable to export gpio %d", port);

    ptr->gpio = gpio;

    return self;
}

static VALUE
cgpio_set_direction(VALUE self, VALUE p_dir)
{
    struct Cgpio *ptr;
    int dir;

    dir = NUM2INT(p_dir);

    Data_Get_Struct(self, struct Cgpio, ptr);

    if (gpio_mode(ptr->gpio, dir) == -1)
    {
            rb_raise(rb_eRuntimeError, "unable to set direction of gpio");
    }

    return self;
}

static VALUE
cgpio_get_direction(VALUE self)
{
    struct Cgpio *ptr;
    int dir;

    Data_Get_Struct(self, struct Cgpio, ptr);

    dir = gpio_get_mode(ptr->gpio);

    if (dir == -1)
    {
        rb_raise(rb_eRuntimeError, "unable to read direction of gpio");
        return self;
    }

    return INT2NUM(dir);
}

static VALUE
cgpio_set_value(VALUE self, VALUE p_value)
{
    struct Cgpio *ptr;

    Data_Get_Struct(self, struct Cgpio, ptr);

    if (p_value != Qtrue && p_value != Qfalse)
    {
        rb_raise(rb_eArgError, "gpio value have to be true or false");
        return self;
    }

    if (gpio_set(ptr->gpio, RTEST(p_value)) == -1)
        rb_raise(rb_eRuntimeError, "unable to set gpio value");

    return self;
}

static VALUE
cgpio_get_value(VALUE self)
{
    struct Cgpio *ptr;
    int value;

    Data_Get_Struct(self, struct Cgpio, ptr);
    value = gpio_get(ptr->gpio);

    if (value == -1)
        rb_raise(rb_eRuntimeError, "unable to read gpio value");
    else if (value)
        return Qtrue;

    return Qfalse;
}

static void
cgpio_free(void *p)
{
    struct Cgpio *ptr = p;

    // only close but dont unexport the gpio
    if (ptr->gpio)
        gpio_close(ptr->gpio, 0);
}

static VALUE
cgpio_alloc(VALUE klass)
{
    VALUE obj;
    struct Cgpio *ptr;

    obj = Data_Make_Struct(klass, struct Cgpio, NULL, cgpio_free, ptr);

    ptr->gpio = NULL;

    return obj;
}

void
Init_cgpio()
{
    VALUE module_Cgpio;
    VALUE class_RealGpio;

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
}
