#include <Dynamixel.h>

#define DIR_PIN  2
#define DIR_TX  HIGH
#define DIR_RX  LOW

#define DXL_ID  1
#define DXL_BAUD 1000000
#define MIN_POS  0
#define MAX_POS  1023

boolean toggle = false;

void setup()
{
  Dynamixel.attachSerial(&Serial1);
  Dynamixel.attachPins(DIR_PIN, DIR_TX, DIR_RX);
  Dynamixel.begin(DXL_BAUD);
  
  Dynamixel.write(DXL_ID, 8, (word)1023); //Dynamixel angle-mode set
//  Dynamixel.write(DXL_ID, 8, (word)0);   //Dynamixel wheel-mode set
}

void loop()
{
  if(toggle == false)
  {
    Dynamixel.joint(DXL_ID, MIN_POS);
    toggle = true;
  }
  else
  {
    Dynamixel.joint(DXL_ID, MAX_POS);
    toggle = false;
  }
  
  delay(3000);
}
