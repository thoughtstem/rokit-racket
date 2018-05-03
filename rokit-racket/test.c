#include <SmartInventor.h>

void setup()
{
  SmartInventor.DCMotorUse();

  SmartInventor.DCMove(forward,127);
  delay(1000);
  SmartInventor.DCMove(forward,127);
}


void loop()
{

}
