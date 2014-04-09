#include <wiringPiI2C.h>
#include <stdio.h>

//to compile: gcc -o proxC proxC.c -lwiringPi

int main()
{
  int fd = wiringPiI2CSetup(0x13); //0x13 is determined by i2cdetect -y 1
  int loop;
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
    while(loop == 1) {
      wiringPiI2CWriteReg8(fd, 0x80, 0xa8);
      int lowByte = wiringPiI2CReadReg8(fd, 0x88);
      int highByte = wiringPiI2CReadReg8(fd, 0x87);
      int reading = (highByte << 8) | lowByte;
      printf("%d\n",reading);
    }
  } else {
    printf("Device not found\n");
  }
}
