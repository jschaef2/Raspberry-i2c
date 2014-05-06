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
/*	while(1) {
		rSensorTest(RSA, RSB);
		delay(100);
	}*/
	forward(75);
	delay(3000);
	rTurn(133);
	delay(3000);
	lTurn(133);
	delay(3000); 
	stop();
}
