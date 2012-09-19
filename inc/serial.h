#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <linux/serial.h>
#include <sys/ioctl.h>
#include <unistd.h>

typedef struct {
	char *device;
	int baudrate;
	int fd;
} serial_t;

int serial_open_device(serial_t *s);
int serial_close_device(serial_t *s);

#endif
