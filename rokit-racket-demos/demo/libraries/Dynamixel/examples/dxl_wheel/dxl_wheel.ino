#include <Dynamixel.h>

#define DIR_PIN  2
#define DIR_TX  HIGH
#define DIR_RX  LOW

#define DXL_ID  1
#define DXL_BAUD 1000000

void setup()
{
  Dynamixel.attachSerial(&Serial1);
  Dynamixel.attachPins(DIR_PIN, DIR_TX, DIR_RX);
  Dynamixel.begin(DXL_BAUD);

  Dynamixel.write(DXL_ID, 8, (word)0);   //Dynamixel wheel-mode set
 //Dynamixel.write(DXL_ID, 8, (word)1023); //Dynamixel angle-mode set

}

void loop()
{
  //must wheel mode
  Dynamixel.wheel(DXL_ID,-500);
  delay(2000);

  Dynamixel.wheel(DXL_ID,500);
  delay(2000);

  Dynamixel.wheel(DXL_ID,0);
  while(1);
}


