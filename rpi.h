#ifndef __RPI_H__
#define __RPI_H__

#include <fcntl.h>
#include <termios.h>
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
#define MOD 14 //38khz clock signal toggled on the basys by the pi
#define WAIT 25
#define GO 2170
#define TEAM 1
#define MAGIC_CLEAR 2000	//subject to change
#define MAGIC_TEAM 800
//1 means green team, 2 means red team

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
int proxAvg(int fd);
int evalProx(int fd);
int avoid(int fd);
int readClear(int fd);
int readRed(int fd);
int readGreen(int fd);
int lightAvg(int fd, int color);
int claim(int fd);
#endif
