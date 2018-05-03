#include <Dynamixel.h>
#include <math.h>

#define DIR_PIN  2
#define DIR_TX  HIGH
#define DIR_RX  LOW

#define DXL_NUM  3
#define DXL_ID   1
#define DXL_BAUD 1000000

float phase[DXL_NUM];
float theta = 0;

void setup()
{
  Dynamixel.attachSerial(&Serial1);
  Dynamixel.attachPins(DIR_PIN, DIR_TX, DIR_RX);
  Dynamixel.begin(DXL_BAUD);
  
  for(int i=0; i<DXL_NUM; i++)
    phase[i] = 2 * PI * (float)i / (float)DXL_NUM;
}

void loop()
{
  float fPos;
  
  Dynamixel.beginPose(POSE_POS);
  for(int i=0; i<DXL_NUM; i++)
  {
    fPos = (sin(theta + phase[i]) + 1.0) * 512;
    Dynamixel.addPose(DXL_ID + i, (word)fPos);
  }
  Dynamixel.endPose();
  
  theta += 0.01;
  if(theta > 2 * PI)
    theta -= 2 * PI;
  delay(10);
}
