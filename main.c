#include "rpi.h"

int main() {
	wiringPiSetup();
	pinMode(LE, OUTPUT); //Left Enable
	pinMode(RE, OUTPUT); //Right Enable
	pinMode(LD, OUTPUT); //Left Direction
	pinMode(RD, OUTPUT); //Right Direction
	pinMode(LSA, INPUT); //Left Sensor A
	pinMode(RSA, INPUT); //Right Sensor A
	pinMode(LSB, INPUT); //Left Sensor B
	pinMode(RSB, INPUT); //Right Sensor B

	//--------MOTOR TESTING--------
	/*	while(1) {
		rSensorTest(RSA, RSB);
		delay(100);
	}
	forward(75);
	delay(3000);
	rTurn(133);
	delay(3000);
	lTurn(133);
	delay(3000); 
	stop(); */
	
	//-------PROX TESTING-----------
	system("i2cset -y 1 0x70 0xe3 0x01");
	system("i2cset -y 1 0x70 0x83 0x0a");
	int fd = wiringPiI2CSetup(0x13); //0x13 is determined by i2cdetect -y 1
  	wiringPiI2CWriteReg8(fd, 0x80, 0xa8);
	while(1) {
		int avgProx = proxAvg(fd);
		printf("%d\n", avgProx);
		if(avgProx < 2170) {
			forward(75);
			stop();
			delay(25);
		}
		avgProx = proxAvg(fd);
		printf("%d\n", avgProx);
		if(avgProx >= 2170) {
			rTurn(133);
			delay(25);
			avgProx = proxAvg(fd);
			printf("%d\n", avgProx);
			if(avgProx < 2170) {
				forward(75);
				stop();
			} else {
				lTurn(133);
				delay(25);
				lTurn(133);
				delay(25);
			}
		}
	}
}
