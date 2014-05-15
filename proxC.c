#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#define LED 0
//to compile: gcc -o proxC proxC.c -lwiringPi

int main()
{
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
    wiringPiI2CWriteReg8(fd, 0x83, 0x0a); //Should increase range of the sensor
    pinMode(LED, OUTPUT);
    digitalWrite(LED, 1);
    while(loop == 1) {
      wiringPiI2CWriteReg8(fd, 0x80, 0xa8);
      int lowByte = wiringPiI2CReadReg8(fd, 0x88);
      int highByte = wiringPiI2CReadReg8(fd, 0x87);
      int reading = (highByte << 8) | lowByte;
      /* if(reading >= 3000) {
	digitalWrite(LED, 0);
      } else {
	digitalWrite(LED, 1);
      }*/
      delay(80);
      printf("%d\n",reading);
    }
  } else {
    printf("Device not found\n");
  }
}
