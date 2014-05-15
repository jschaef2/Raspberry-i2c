#include "rpi.h"
#include <stdlib.h>

int main() {
	//PROX SETUP
	system("sudo i2cset -y 1 0x70 0x00 0x01"); 
	wiringPiSetup();
	int pfd = wiringPiI2CSetup(0x13); //0x13 is determined by i2cdetect -y 1
    	wiringPiI2CWriteReg8(pfd, 0x83, 0x0a); //Should increase range of the sensor
  	wiringPiI2CWriteReg8(pfd, 0x80, 0xa8); //Get the prox ready to be read
	
	//LIGHT SETUP
	int lfd = wiringPiI2CSetup(0x29);
	
	//IR SETUP
	int ifd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);
	
	pinMode(LE, OUTPUT); //Left Enable
	pinMode(RE, OUTPUT); //Right Enable
	pinMode(LD, OUTPUT); //Left Direction
	pinMode(RD, OUTPUT); //Right Direction
	pinMode(LSA, INPUT); //Left Sensor A
	pinMode(RSA, INPUT); //Right Sensor A
	pinMode(LSB, INPUT); //Left Sensor B
	pinMode(RSB, INPUT); //Right Sensor B
	pinMode(MOD, OUTPUT); //Pin to Basys for 38KHZ Carrier
	
	//PHASE 1 (CLAIM THE FIRST BEACON)
	while(millis() < 25000) {
		if(lightAvg(lfd, 0) > 25) { //Activate			
//			int clear = readTeam(lfd, 0);
//			int team = readTeam(lfd, TEAM);
			while((readTeam(lfd, 0) < MAGIC_CLEAR) && (readTeam(lfd, TEAM) < MAGIC_TEAM)) {
//				printf("Clear avg: %d Team avg: %d\n", clear, team);
				printf("Spinning\n");
				digitalWrite(LE, 1);
				digitalWrite(RE, 1);
				digitalWrite(LD, 1);
				digitalWrite(RD, 1);
				delay(5);
				stop();
			}
			stop();
			delay(WAIT);
			printf("Forward\n");
			forward(75);
	/*		int proxCheck = evalProx(pfd);
			if(proxCheck == 0) {
//				int tag = claim();
				int proceed = avoid(pfd);
				while(proceed == 0) {
					printf("avoid\n");
					proceed = avoid(pfd);
				}
			}*/		
		}
	}
	stop();
}
