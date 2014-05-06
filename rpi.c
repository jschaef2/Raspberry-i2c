#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>

#define LE 0
#define RE 1
#define LD 2
#define RD 3
#define LSA 4
#define RSA 5
#define LSB 6
#define RSB 7

unsigned int L_QUAD_PHASE = 0;
unsigned int R_QUAD_PHASE = 0;
unsigned int INPUT_DISTANCE;
unsigned int RIGHT_TEST;
unsigned int LAST_RIGHT_TEST;
unsigned int LEFT_TEST;
unsigned int LAST_LEFT_TEST;

wiringPiSetup();
pinMode(LE, OUTPUT); //Left Enable
pinMode(RE, OUTPUT); //Right Enable
pinMode(LD, OUTPUT); //Left Direction
pinMode(RD, OUTPUT); //Right Direction
pinMode(LSA, INPUT); //Left Sensor A
pinMode(RSA, INPUT); //Right Sensor A
pinMode(LSB, INPUT); //Left Sensor B
pinMode(RSB, INPUT); //Right Sensor B

void rSensorTest(int gpio1, int gpio2) {
	LAST_RIGHT_TEST1 = RIGHT_TEST1;
	LAST_RIGHT_TEST2 = RIGHT_TEST2;
	RIGHT_TEST1 = digitalRead(gpio1);
	RIGHT_TEST2 = digitalRead(gpio2);
	if((RIGHT_TEST1 != LAST_RIGHT_TEST1) || (RIGHT_TEST2 != LAST_RIGHT_TEST2))
	{
		R_QUAD_PHASE++;
	}
}

void lSensorTest(int gpio1, int gpio2) {
	LAST_LEFT_TEST1 = LEFT_TEST1;
	LAST_LEFT_TEST2 = LEFT_TEST2;
	LEFT_TEST1 = digitalRead(LSA);
	LEFT_TEST2 = digitalRead(LSB);
	if((LEFT_TEST1 != LAST_LEFT_TEST1) || (LEFT_TEST2 != LAST_LEFT_TEST2));
	{
		L_QUAD_PHASE++;
	}
}

void forward(int ticks) {
	L_QUAD_PHASE = 0;
	R_QUAD_PHASE = 0;
	while(L_QUAD_PHASE < ticks && R_QUAD_PHASE < ticks)
	{
		if(R_QUAD_PHASE == L_QUAD_PHASE)
		{
			digitalWrite(LE, 1);
			digitalWrite(RE, 1);
			digitalWrite(LD, 1);
			digitalWrite(RD, 0);
			delay(.13);
			digitalWrite(LE, 0);
			digitalWrite(RE, 0);
			delay(.13);
			rSensorTest(RSA, RSB);
			lSensorTest(LSA, LSB);
		}
		if(R_QUAD_PHASE < L_QUAD_PHASE)
		{
			digitalWrite(LE, 0);
			digitalWrite(RE, 1);
			digitalWrite(RD, 0);
			delay(.13);
			digitalWrite(RE, 0);
			delay(.13);
			digitalWrite(RE, 1);
			rSensorTest(RSA, RSB);
			lSensorTest(LSA, LSB);
		}
		if(R_QUAD_PHASE > L_QUAD_PHASE) 
		{
			digitalWrite(RE, 0);
			digitalWrite(LE, 1);
			digitalWrite(LD, 1);
			delay(.13);
			digitalWrite(LE, 0);
			delay(.13);
			digitalWrite(LE, 1);
			rSensorTest(RSA, RSB);
			lSensorTest(LSA, LSB);
		}
	}
}

void lTurn(int ticks) {
	L_QUAD_PHASE = 0;
	R_QUAD_PHASE = 0;
	while(L_QUAD_PHASE < ticks && R_QUAD_PHASE < ticks)
	{
		if(R_QUAD_PHASE == L_QUAD_PHASE)
		{
			digitalWrite(LE, 1);
			digitalWrite(RE, 1);
			digitalWrite(LD, 0);
			digitalWrite(RD, 0);
			delay(.13);
			digitalWrite(LE, 0);
			digitalWrite(RE, 0);
			delay(.13);
			rSensorTest(RSA, RSB);
			lSensorTest(LSA, LSB);
		}
		if(R_QUAD_PHASE < L_QUAD_PHASE)
		{
			digitalWrite(LE, 0);
			digitalWrite(RE, 1);
			digitalWrite(RD, 0);
			delay(.13);
			digitalWrite(RE, 0);
			delay(.13);
			digitalWrite(RE, 1);
			rSensorTest(RSA, RSB);
			lSensorTest(LSA, LSB);
		}
		if(R_QUAD_PHASE > L_QUAD_PHASE) 
		{
			digitalWrite(RE, 0);
			digitalWrite(LE, 1);
			digitalWrite(LD, 0);
			delay(.13);
			digitalWrite(LE, 0);
			delay(.13);
			digitalWrite(LE, 1);
			rSensorTest(RSA, RSB);
			lSensorTest(LSA, LSB);
		}
	}
}

void rTurn(int ticks) {
	L_QUAD_PHASE = 0;
	R_QUAD_PHASE = 0;
	while(L_QUAD_PHASE < ticks && R_QUAD_PHASE < ticks)
	{
		if(R_QUAD_PHASE == L_QUAD_PHASE)
		{
			digitalWrite(LE, 1);
			digitalWrite(RE, 1);
			digitalWrite(LD, 1);
			digitalWrite(RD, 1);
			delay(.13);
			digitalWrite(LE, 0);
			digitalWrite(RE, 0);
			delay(.13);
			rSensorTest(RSA, RSB);
			lSensorTest(LSA, LSB);
		}
		if(R_QUAD_PHASE < L_QUAD_PHASE)
		{
			digitalWrite(LE, 0);
			digitalWrite(RE, 1);
			digitalWrite(RD, 1);
			delay(.13);
			digitalWrite(RE, 0);
			delay(.13);
			digitalWrite(RE, 1);
			rSensorTest(RSA, RSB);
			lSensorTest(LSA, LSB);
		}
		if(R_QUAD_PHASE > L_QUAD_PHASE) 
		{
			digitalWrite(RE, 0);
			digitalWrite(LE, 1);
			digitalWrite(LD, 1);
			delay(.13);
			digitalWrite(LE, 0);
			delay(.13);
			digitalWrite(LE, 1);
			rSensorTest(RSA, RSB);
			lSensorTest(LSA, LSB);
		}
	}
}

void stop() {
	digitalWrite(RE, 0);
	digitalWrite(LE, 0);
}

int main() {
	forward(50);
	delay(1000);
	rTurn(133);
	delay(1000);
	lTurn(133);
	delay(1000);
	stop();
}






























































































































































































































































