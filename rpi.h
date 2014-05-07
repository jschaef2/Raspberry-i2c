#ifndef __RPI_H__
#define __RPI_H__

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

extern unsigned int L_QUAD_PHASE;
extern unsigned int R_QUAD_PHASE;
extern unsigned int LAST_RIGHT_TEST1;
extern unsigned int LAST_RIGHT_TEST2;
extern unsigned int LAST_LEFT_TEST1;
extern unsigned int LAST_LEFT_TEST2;
extern unsigned int LEFT_TEST1;
extern unsigned int LEFT_TEST2;
extern unsigned int RIGHT_TEST1;
extern unsigned int RIGHT_TEST2;

void rSensorTest(int gpio1, int gpio2);
void lSensorTest(int gpio1, int gpio2);
void forward(int ticks);
void lTurn(int ticks);
void rTurn(int ticks);
void stop();
int readProx(int fd);

#endif
