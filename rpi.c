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

int readProx() {
//  int mfd = wiringPiI2CSetup(0x71); //0x72 is multiplexer channel 1
  int fd = wiringPiI2CSetup(0x13); //0x13 is determined by i2cdetect -y 1
 // wiringPiSetup();
  int loop;
  int pin = 0;
  wiringPiI2CWriteReg8(fd, 0x80, 0xa8);

  if(fd >= 0) {
    loop = 1;
  } else {
    loop = 0;
  }

  int ver = wiringPiI2CReadReg8(fd, 0x81);
  printf("version:%d\n", ver);
  if(ver == 0x11) {
    printf("Device found\n");
    //wiringPiI2CWriteReg8(fd, 0x03, 0x08); //Should increase range of the sensor
    pinMode(LED, OUTPUT);
    digitalWrite(LED, 1);
    while(loop == 1) {
		wiringPiI2CWriteReg8(fd, 0x80, 0xa8);
		int lowByte = wiringPiI2CReadReg8(fd, 0x88);
		int highByte = wiringPiI2CReadReg8(fd, 0x87);
		int reading = (highByte << 8) | lowByte;
		//printf("%d\n",reading);
		return reading;
		delay(30);
    }
  } else {
    //printf("Device not found\n");
	return -1;
  }
}






























































































































































































































































