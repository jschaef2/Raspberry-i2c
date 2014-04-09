#include <wiringPiI2C.h>
#include <stdio.h>
#include <wiringPi.h>

//to compile: gcc -o proxC proxC.c -lwiringPi

int main()
{
  int fd = wiringPiI2CSetup(0x29); //0x29 is determined by i2cdetect -y 1#
  int loop;

  if(fd >= 0) {
    loop = 1;
  } else {
    loop = 0;
    printf("Setup failed\n");
  }

  int ver = wiringPiI2CReadReg8(fd, 0x80 | 0x12);
  printf("version:%d\n", ver);
  if(ver == 0x44) {
    printf("Device found\n");
    wiringPiI2CWrite(fd, 0x80 | 0x00); //Enable
    wiringPiI2CWrite(fd, 0x01 | 0x02); //Power on

    while(loop == 1) {
      wiringPiI2CWrite(fd, 0x80 | 0x14);
      int clearLow = wiringPiI2CReadReg8(fd, 0x14);
      wiringPiI2CWrite(fd, 0x80 | 0x15);
      int clearHigh = wiringPiI2CReadReg8(fd, 0x15);
      int clear = (clearHigh << 8) | clearLow;
      printf("clear: %d", clear);

      wiringPiI2CWrite(fd, 0x80 | 0x16);
      int redLow = wiringPiI2CReadReg8(fd, 0x16);
      wiringPiI2CWrite(fd, 0x80 | 0x17);
      int redHigh = wiringPiI2CReadReg8(fd, 0x17);
      int red = (redHigh << 8) | redLow;
      printf(" red: %d", red);

      wiringPiI2CWrite(fd, 0x80 | 0x18);
      int greenLow = wiringPiI2CReadReg8(fd, 0x18);
      wiringPiI2CWrite(fd, 0x80 | 0x19);
      int greenHigh = wiringPiI2CReadReg8(fd, 0x19);
      int green = (greenHigh << 8) | greenLow;
      printf(" green: %d\n", green);

      delayMicrosecondsHard(10000);
    }
  } else {
    printf("Device not found\n");
  }
}
