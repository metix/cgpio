#ifndef _GPIO_H_
#define _GPIO_H_

#define GPIO_MODE_OUTPUT	0x01
#define GPIO_MODE_INPUT		0x02

struct Gpio
{
    int fd_value;
    int nr;
};

extern struct Gpio *gpio_setup(int n);
extern int gpio_set(struct Gpio *gpio, int value);
extern int gpio_mode(struct Gpio *gpio, int mode);
extern void gpio_close(struct Gpio *gpio, int unexport);

#endif
