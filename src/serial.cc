#include "serial.h"

int serial_open_device(serial_t *s) {
	int sfd = open(device.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
	if (s->fd == -1) {
		return 1;
	}
	else {
		fcntl(s->fd, F_SETFL, 0);
	}

	struct termios tos;
	struct serial_struct ss;
	int ret;

	ioctl(s->fd, TIOCGSERIAL, &ss);
	ss.flags = (ss.flags & ~ASYNC_SPD_MASK) | ASYNC_SPD_CUST;
	ss.custom_divisor = (ss.baud_base + (s->baudrate / 2)) / s->baudrate;
	s->baudrate = ss.baud_base / ss.custom_divisor;

	if(ioctl(s->fd, TIOCSSERIAL, &ss) !=0) {
		return 2;
	}

	cfsetispeed(&tos, B38400);
	cfsetospeed(&tos, B38400);
	
	tos.c_cflag &= ~(PARENB | CSTOPB | CSIZE);
	tos.c_cflag |= CS8;
	tos.c_cflag |= CRTSCTS;
	tos.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	tos.c_iflag &= ~(INPCK | IGNPAR | PARMRK | ISTRIP | IXON | IXOFF);
	tos.c_iflag &= ~(IXANY | BRKINT | INLCR | IGNCR | ICRNL | IUCLC | IMAXBEL);
	tos.c_oflag &= ~OPOST;

	if (tcsetattr(s->fd, TCSANOW, &tos)) {
		return 4;
	}

	return 0;
}
