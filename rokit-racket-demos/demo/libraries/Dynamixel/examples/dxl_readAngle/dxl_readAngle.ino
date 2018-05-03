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
  Dynamixel.write(DXL_ID, 24, (byte)0); // Torque disable
  
  Serial.begin(57600);
}

void loop()
{
  word pos;
  
  if(Dynamixel.read(DXL_ID, 36, &pos) == COMMERROR_NONE) // read present position
  {
    Serial.println(pos);
    delay(10); 
  }
}
