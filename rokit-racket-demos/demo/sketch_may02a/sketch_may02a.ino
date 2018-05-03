#include <SmartInventor.h>

void setup()
{
  SmartInventor.DCMotorUse();
}


void loop()
{
  SmartInventor.DCMove(forward,127);
  delay(1000);
  SmartInventor.DCMove(stop,127);
  delay(1000);
}

