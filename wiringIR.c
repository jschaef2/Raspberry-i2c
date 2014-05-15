#include <fcntl.h>
#include <termios.h>
#include <wiringSerial.h>
#include <wiringPi.h>

int main() {
	wiringPiSetup();
//	int fd = serialOpen("/dev/ttyAMA0", 300);
	int fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);
/*	struct termios options;
	tcgetattr(fd, &options);
	options.c_cflag = B300 | CS8 | CLOCAL | CREAD;
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &options); */
	pinMode(0, OUTPUT);
	digitalWrite(0, 0);
	serialFlush(fd);
	int i = 0;
	unsigned int x[8];
	while(1) {
		int avail = serialDataAvail(fd);
		if(serialDataAvail(fd) > 0) {
			unsigned int reading = serialGetchar(fd);
			unsigned int trans = (~reading) & 0xff;
			printf("%u --> %u\n", reading, trans);
			digitalWrite(0, 1);
			delay(10);
			serialPutchar(fd, trans);
			delay(35);
		} 
		digitalWrite(0, 0);
		serialFlush(fd);
	}
	serialClose(fd);
}
