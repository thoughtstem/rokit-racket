#include <MsTimer2.h>
#include <DCM.h>

DCM motor1;
DCM motor2;

void setup()
{
    motor1.attachPins(12,13);  
    motor2.attachPins(14,15);
    
}

void loop()
{
  unsigned char i = 0;
  
  for (i=0; i < 10; i++)
  {
     motor1.write(CCW, i);
     motor2.write(CW, i);
     delay(1000); 
  }
  
  for (i=0; i < 10; i++)
  {
     motor1.write(CW, i);
     motor2.write(CCW, i);
     delay(1000); 
  }
  motor1.write(STOP, 10);
  motor2.write(STOP, 10);
  while(1);  
  
}

