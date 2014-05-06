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
	forward(50);
	delay(1000);
	rTurn(133);
	delay(1000);
	lTurn(133);
	delay(1000);
	stop();
}