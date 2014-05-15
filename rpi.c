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
	delay(WAIT);
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
	delay(WAIT);
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
	delay(WAIT);
}

void stop() {
	digitalWrite(RE, 0);
	digitalWrite(LE, 0);
}

int readProx(int fd) {
  int loop;
  int ver = wiringPiI2CReadReg8(fd, 0x81);
  //printf("version:%d\n", ver);
  if(ver == 0x11) {
   // printf("Device found\n");
    //wiringPiI2CWriteReg8(fd, 0x03, 0x08); //Should increase range of the sensor
    wiringPiI2CWriteReg8(fd, 0x80, 0xa8);
    int lowByte = wiringPiI2CReadReg8(fd, 0x88);
    int highByte = wiringPiI2CReadReg8(fd, 0x87);
    int reading = (highByte << 8) | lowByte;
    //printf("%d\n",reading);
    return reading;
    delay(30);
  } else {
    //printf("Device not found\n");
    return -1;
  }
}

int proxAvg(int fd) {
	int i = 0;
	int prox;
	int sum = 0;
	for(i; i < 30; i++) {
	prox = readProx(fd);
		if(prox != -1) {
			sum += prox;
		} else {
			i = i - 1;
		}
		delay(5);
	}
	int average = sum / 30;
	sum = 0;
	//printf("%d\n", average);
	return average;
}

int evalProx(int fd) {
	int reading = proxAvg(fd);
	if(reading < GO) {
		return 1;
	} else {
		return 0;
	}
}

int avoid(int fd) {
	rTurn(133);
	int reading = evalProx(fd);
	if(evalProx(fd) == 1) {
		forward(75);
		lTurn(133);
		if(evalProx(fd) == 1) {
			return 1;
		} else {
			return 0;
		}
	} else {
		lTurn(133);
		lTurn(133);
		if(evalProx(fd) == 1) {
			forward(75);
			if(evalProx(fd) == 1) {
				return 1;
			} else {
				return 0;
			}
		} else {
			return 0;
		}
	}
}

int readClear(int fd) {		
	wiringPiI2CWrite(fd, 0x80 | 0x14);
	int clearLow = wiringPiI2CReadReg8(fd, 0x14);
	wiringPiI2CWrite(fd, 0x80 | 0x15);
	int clearHigh = wiringPiI2CReadReg8(fd, 0x15);
	int clear = (clearHigh << 8) | clearLow;
	//printf("clear: %d", clear);
	return clear;
}

int readRed(int fd) {		
	wiringPiI2CWrite(fd, 0x80 | 0x16);
	int redLow = wiringPiI2CReadReg8(fd, 0x16);
	wiringPiI2CWrite(fd, 0x80 | 0x17);
	int redHigh = wiringPiI2CReadReg8(fd, 0x17);
	int red = (redHigh << 8) | redLow;
	//printf(" red: %d", red);
	return red;
}

int readGreen(int fd) {		
	wiringPiI2CWrite(fd, 0x80 | 0x18);
	int greenLow = wiringPiI2CReadReg8(fd, 0x18);
	wiringPiI2CWrite(fd, 0x80 | 0x19);
	int greenHigh = wiringPiI2CReadReg8(fd, 0x19);
	int green = (greenHigh << 8) | greenLow;
	//printf(" green: %d\n", green);
	return green;
}

int readTeam(int fd, int color) {
	int ver = wiringPiI2CReadReg8(fd, 0x80 | 0x12);
	//printf("version:%d\n", ver);
	if(ver == 0x44) {
		//printf("Device found\n");
		wiringPiI2CWrite(fd, 0x80 | 0x00); //Enable
		wiringPiI2CWrite(fd, 0x01 | 0x02); //Power on
		int reading;
		if(color == 0) {
			reading = readClear(fd);
			delay(10);
			return reading;
		} else if(color == 1) {
			reading = readRed(fd);
			delay(10);
			return reading;
		} else if(color == 2) {
			reading = readGreen(fd);
			delay(10);
			return reading;
		} else {
			return -1;
		}
	} else {
		return -1;
	}
}

int lightAvg(int fd, int color) {
	int ver = wiringPiI2CReadReg8(fd, 0x80 | 0x12);
	//printf("version:%d\n", ver);
	if(ver == 0x44) {
		//printf("Device found\n");
		wiringPiI2CWrite(fd, 0x80 | 0x00); //Enable
		wiringPiI2CWrite(fd, 0x01 | 0x02); //Power on
		int i = 0;
		int reading = 0;
		int average = 0;
		if(color == 0) {
			for(i; i < 15; i++) {
				reading += readClear(fd);
				delay(5);
			}
			average = reading / 15;
			return average;
		} else if(color == 1) {
			for(i; i < 15; i++) {
				reading += readRed(fd);
				delay(5);
			}
			average = reading / 15;
			return average;
		} else if(color == 2) {
			for(i; i < 15; i++) {
				reading += readGreen(fd);
				delay(5);
			}
			average = reading / 15;
			return average;
		} else {
			return -1;
		}
	} else {
		return -1;
	}
}

int claim(int fd) {
/*	struct termios options;
	tcgetattr(fd, &options);
	options.c_cflag = B300 | CS8 | CLOCAL | CREAD;
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &options); */
	digitalWrite(MOD, 0);
	serialFlush(fd);
	int avail = serialDataAvail(fd);
	if(avail > 0) {
		unsigned int reading = serialGetchar(fd);
		unsigned int trans = (~reading) & 0xff;
		printf("%u --> %u\n", reading, trans);
		digitalWrite(MOD, 1);
		delay(10);
		serialPutchar(fd, trans);
		delay(40);
		digitalWrite(MOD, 0);
		return 1; //Something was written
	} 
	serialFlush(fd);
	serialClose(fd);
	return 0; //Nothing was written
}



























































































































































































































































