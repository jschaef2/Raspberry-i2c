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
//	for(i; i < 1000; i++) {
	while(1) {
		int avail = serialDataAvail(fd);
		if(serialDataAvail(fd) > 0) {
			unsigned int reading = serialGetchar(fd);
/*			unsigned int count = read(fd, &x, 1);
			unsigned int reading = ((int)x) & 0xff;*/
			unsigned int trans = (~reading) & 0xff;
//			delay(30);
			printf("%u --> %u\n", reading, trans);
			digitalWrite(0, 1);
			delay(10);
			serialPutchar(fd, trans);
			delay(35);
//			int reading = read(fd, &x, 8);
//			printf("%d - %d\n", i, x);
//			serialFlush(fd);
		} 
		digitalWrite(0, 0);
//		serialPutchar(fd, 125); 
//		int reading = serialGetchar(fd);
//		int reading = read(fd, &x, 8);
//		printf("%d\n", x);
//		serialPutchar(fd, reading);
//		delay(100);
		serialFlush(fd);
	}
	serialClose(fd);
}
