#include "gpio.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define GPIO_PATH "/sys/class/gpio/"
#define BUF_SIZE 1024

static int
gpio_export(int n)
{
	char buf[BUF_SIZE];
	int fd, written;

	// open gpio export file
	fd = open(GPIO_PATH "export", O_WRONLY);
	if (fd == -1)
		return -1;

	// write gpio number in export file
	sprintf(buf, "%d", n);
	written = write(fd, buf, strlen(buf));
	close(fd);
	if (written == -1)
		return -1;

	return 0;
}

static int
gpio_exists(int n)
{
	char buf[BUF_SIZE];
	sprintf(buf, GPIO_PATH "gpio%d", n);

	if(access(buf, F_OK) != -1 )
		return 1;
	return 0;
}

struct Gpio*
gpio_setup(int n)
{
	char buf[BUF_SIZE];
	int fd;
	struct Gpio *gpio;

	if (!gpio_exists(n))
	{
		if (gpio_export(n) == -1)
		{
			printf("gpio error: couldn't export gpio %d\n", n);
			return NULL;
		}
	}

	// open the value file of the exported gpio
	sprintf(buf, GPIO_PATH "gpio%d/value", n);
	fd = open(buf, O_RDWR);
	if (fd == -1)
	{
		printf("gpio error: error at open value file for gpio %d\n", n);
		return NULL;
	}

	// allocate the gpio structure
	gpio = malloc(sizeof (struct Gpio));
	gpio->nr = n;
	gpio->fd_value = fd;

	return gpio;
}

void
gpio_close(struct Gpio *gpio, int unexport)
{
	char buf[BUF_SIZE];
	int written;

	if (unexport)
	{
		// open gpio unexport file
		int fd = open(GPIO_PATH "unexport", O_WRONLY);
		if (fd == -1)
			return;

		// write gpio number in unexport file
		sprintf(buf, "%d", gpio->nr);
		written = write(fd, buf, strlen(buf));
		close(fd);
		if (written == -1)
			return;
	}

	// close the value file of the gpio
	close(gpio->fd_value);

	// free the gpio structure
	free(gpio);
}

int
gpio_set(struct Gpio *gpio, int value)
{
	int written = -1;

	if (value)
		written = write(gpio->fd_value, "1", 1);
	else
		written = write(gpio->fd_value, "0", 1);

	lseek(gpio->fd_value, 0, SEEK_SET);

	return written;
}

int
gpio_get(struct Gpio *gpio)
{
	int readb;
	char buf[1];

	readb = read(gpio->fd_value, buf, 1);

	if (readb == -1)
	{
		lseek(gpio->fd_value, 0, SEEK_SET);
		return -1;
	}

	lseek(gpio->fd_value, 0, SEEK_SET);

	return buf[0] == '1';
}

int
gpio_mode(struct Gpio *gpio, int mode)
{
	char buf[BUF_SIZE];
	int fd, written = -1;

	// open the direction file of the gpio
	sprintf(buf, GPIO_PATH "gpio%d/direction", gpio->nr);

	fd = open(buf, O_WRONLY);
	if (fd == -1)
		return -1;

	if (mode == GPIO_MODE_INPUT)
	{
		written = write(fd, "in", 2);
	}
	else if (mode == GPIO_MODE_OUTPUT)
	{
		written = write(fd, "out", 3);
	}

	if (written == -1)
		return -1;

	return 0;
}
