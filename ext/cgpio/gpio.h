#ifndef _GPIO_H_
#define _GPIO_H_

#define GPIO_MODE_OUTPUT	0x01
#define GPIO_MODE_INPUT		0x02

struct Gpio
{
    /* file descriptor of the /sys/value/gpio%d/value file */
    int fd_value;

    /* number of the gpio */
    int nr;
};

extern struct Gpio *gpio_setup(int n);
extern int gpio_set(struct Gpio *gpio, int value);
extern int gpio_get(struct Gpio *gpio);
extern int gpio_mode(struct Gpio *gpio, int mode);
extern void gpio_close(struct Gpio *gpio, int unexport);

#endif
