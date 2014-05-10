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
	while(millis() < 6000) {
		if(lightAvg(lfd, 0) > 25) { //Activate			
			int clearAvg = lightAvg(lfd, 0);
			int teamAvg = lightAvg(lfd, TEAM);
			while((clearAvg < MAGIC_CLEAR) && (teamAvg < MAGIC_TEAM)) {
				printf("Clear avg: %d Team avg: %d\n", clearAvg, teamAvg);
				digitalWrite(LE, 1);
				digitalWrite(RE, 1);
				digitalWrite(LD, 1);
				digitalWrite(RD, 1);
	//			printf("clear: %d red: %d green: %d\n", readClear(lfd), readRed(lfd), readGreen(lfd));
				clearAvg = lightAvg(lfd, 0);
				teamAvg = lightAvg(lfd, TEAM);
			}
			stop();
			delay(WAIT);
			printf("Forward\n");
			forward(75);
			int proxCheck = evalProx(pfd);
			if(proxCheck == 0) {
//				int tag = claim();
				int proceed = avoid(pfd);
				while(proceed == 0) {
					printf("avoid\n");
					proceed = avoid(pfd);
				}
			}		
		}
	}
	stop();
}
