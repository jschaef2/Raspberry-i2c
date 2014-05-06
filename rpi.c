#include "rpi.h"

unsigned int L_QUAD_PHASE = 0;
unsigned int R_QUAD_PHASE = 0;
unsigned int LAST_RIGHT_TEST1;
unsigned int LAST_RIGHT_TEST2;
unsigned int LAST_LEFT_TEST1;
unsigned int LAST_LEFT_TEST2;
unsigned int LEFT_TEST1 = 0;
unsigned int LEFT_TEST2 = 0;
unsigned int RIGHT_TEST1 = 0;
unsigned int RIGHT_TEST2 = 0;

void rSensorTest(int gpio1, int gpio2) {
	LAST_RIGHT_TEST1 = RIGHT_TEST1;
	LAST_RIGHT_TEST2 = RIGHT_TEST2;
	RIGHT_TEST1 = digitalRead(gpio1);
	RIGHT_TEST2 = digitalRead(gpio2);
//	printf("Right 1: %d, Last: %d\n", RIGHT_TEST1, LAST_RIGHT_TEST1);
//	printf("Right 2: %d, Last: %d\n", RIGHT_TEST2, LAST_RIGHT_TEST2);
	if((RIGHT_TEST1 != LAST_RIGHT_TEST1) || (RIGHT_TEST2 != LAST_RIGHT_TEST2))
	{
		R_QUAD_PHASE++;
//		printf("%d\n", R_QUAD_PHASE);
	}
}

void lSensorTest(int gpio1, int gpio2) {
	LAST_LEFT_TEST1 = LEFT_TEST1;
	LAST_LEFT_TEST2 = LEFT_TEST2;
	LEFT_TEST1 = digitalRead(gpio1);
	LEFT_TEST2 = digitalRead(gpio2);
//	printf("Left 1: %d, Last: %d\n", LEFT_TEST1, LAST_LEFT_TEST1);
//	printf("Left 2: %d, Last: %d\n", LEFT_TEST2, LAST_LEFT_TEST2);
	if((LEFT_TEST1 != LAST_LEFT_TEST1) || (LEFT_TEST2 != LAST_LEFT_TEST2))
	{
//		printf("Left 1: %d, Last: %d\n", LEFT_TEST1, LAST_LEFT_TEST1);
//		printf("Left 2: %d, Last: %d\n", LEFT_TEST2, LAST_LEFT_TEST2);
		L_QUAD_PHASE++;
//		printf("%d\n", L_QUAD_PHASE);
	}
}

void forward(int ticks) {
	L_QUAD_PHASE = 0;
	R_QUAD_PHASE = 0;
	while((L_QUAD_PHASE < ticks) && (R_QUAD_PHASE < ticks))
	{
		if(R_QUAD_PHASE == L_QUAD_PHASE)
		{
			digitalWrite(LE, 1);
			digitalWrite(RE, 1);
			digitalWrite(LD, 1);
			digitalWrite(RD, 0);
			delay(1);
			digitalWrite(LE, 0);
			digitalWrite(RE, 0);
			delay(1);
			rSensorTest(RSA, RSB);
			lSensorTest(LSA, LSB);
		}
		if(R_QUAD_PHASE < L_QUAD_PHASE)
		{
			digitalWrite(LE, 0);
			digitalWrite(RE, 1);
			digitalWrite(RD, 0);
			delay(1);
			digitalWrite(RE, 0);
			delay(1);
			digitalWrite(RE, 1);
			rSensorTest(RSA, RSB);
			lSensorTest(LSA, LSB);
		}
		if(R_QUAD_PHASE > L_QUAD_PHASE) 
		{
			digitalWrite(RE, 0);
			digitalWrite(LE, 1);
			digitalWrite(LD, 1);
			delay(1);
			digitalWrite(LE, 0);
			delay(1);
			digitalWrite(LE, 1);
			rSensorTest(RSA, RSB);
			lSensorTest(LSA, LSB);
		}
	}
	stop();
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
			delay(1);
			digitalWrite(LE, 0);
			digitalWrite(RE, 0);
			delay(1);
			rSensorTest(RSA, RSB);
			lSensorTest(LSA, LSB);
		}
		if(R_QUAD_PHASE < L_QUAD_PHASE)
		{
			digitalWrite(LE, 0);
			digitalWrite(RE, 1);
			digitalWrite(RD, 0);
			delay(1);
			digitalWrite(RE, 0);
			delay(1);
			digitalWrite(RE, 1);
			rSensorTest(RSA, RSB);
			lSensorTest(LSA, LSB);
		}
		if(R_QUAD_PHASE > L_QUAD_PHASE) 
		{
			digitalWrite(RE, 0);
			digitalWrite(LE, 1);
			digitalWrite(LD, 0);
			delay(1);
			digitalWrite(LE, 0);
			delay(1);
			digitalWrite(LE, 1);
			rSensorTest(RSA, RSB);
			lSensorTest(LSA, LSB);
		}
	}
	stop();
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
			delay(1);
			digitalWrite(LE, 0);
			digitalWrite(RE, 0);
			delay(1);
			rSensorTest(RSA, RSB);
			lSensorTest(LSA, LSB);
		}
		if(R_QUAD_PHASE < L_QUAD_PHASE)
		{
			digitalWrite(LE, 0);
			digitalWrite(RE, 1);
			digitalWrite(RD, 1);
			delay(1);
			digitalWrite(RE, 0);
			delay(1);
			digitalWrite(RE, 1);
			rSensorTest(RSA, RSB);
			lSensorTest(LSA, LSB);
		}
		if(R_QUAD_PHASE > L_QUAD_PHASE) 
		{
			digitalWrite(RE, 0);
			digitalWrite(LE, 1);
			digitalWrite(LD, 1);
			delay(1);
			digitalWrite(LE, 0);
			delay(1);
			digitalWrite(LE, 1);
			rSensorTest(RSA, RSB);
			lSensorTest(LSA, LSB);
		}
	}
	stop();
}

void stop() {
	digitalWrite(RE, 0);
	digitalWrite(LE, 0);
}
































































































































































































































































