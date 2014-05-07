#include "rpi.h"

int main() {
	//PROX SETUP
	wiringPiSetup();
	system("i2cset -y 1 0x70 0xe3 0x01"); 
//	system("i2cset -y 1 0x70 0x83 0x0a");
	int pfd = wiringPiI2CSetup(0x13); //0x13 is determined by i2cdetect -y 1
  	wiringPiI2CWriteReg8(pfd, 0x80, 0xa8); //Get the prox ready to be read
	
	//LIGHT SETUP
	int lfd = wiringPiI2CSetup(0x29);
	
	pinMode(LE, OUTPUT); //Left Enable
	pinMode(RE, OUTPUT); //Right Enable
	pinMode(LD, OUTPUT); //Left Direction
	pinMode(RD, OUTPUT); //Right Direction
	pinMode(LSA, INPUT); //Left Sensor A
	pinMode(RSA, INPUT); //Right Sensor A
	pinMode(LSB, INPUT); //Left Sensor B
	pinMode(RSB, INPUT); //Right Sensor B

	//PHASE 1 (CLAIM THE FIRST BEACON)
	while(1) {
		if(lightAvg(lfd, 0) > 25) { //Activate
			while((lightAvg(lfd, 0) < MAGIC_CLEAR) || (lightAvg(lfd, TEAM) < MAGIC_TEAM)) {
				digitalWrite(LE, 1);
				digitalWrite(RE, 1);
				digitalWrite(LD, 1);
				digitalWrite(RD, 0);
			}
			stop();
			delay(WAIT);
			forward(75);
			stop();
			delay(WAIT);
			int proxCheck = evalProx(pfd);
			if(proxCheck == 0) {
//				int tag = claim();
				int proceed = avoid();
				while(proceed == 0) {
					proceed = avoid();
				}
			}		
		}
	}
}
