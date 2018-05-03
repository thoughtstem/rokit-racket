#include <MsTimer2.h>
#include <DCM.h>

DCM motor1;
DCM motor2;
DCM motor3;
DCM motor4;

void setup()
{
    motor1.attachPins(12,13);  
    motor2.attachPins(14,15);
    motor3.attachPins(20,21);
    motor4.attachPins(22,23);
}

void loop()
{
  motor1.write(CW,5);
  motor2.write(CW,5);
  motor3.write(CW,5);
  motor4.write(CW,5);
  delay(1000);
  motor1.write(CCW,5);
  motor2.write(CCW,5);
  motor3.write(CCW,5);
  motor4.write(CCW,5);
  delay(1000);
}

