#include <Servo.h>
int angle = 0;
Servo servo1;

void setup()
{
   servo1.attach(16);  //PC0 - Servomotor 
}

void loop()
{
   int a = analogRead(A0); 
   angle = map(a, 0, 1023, 0, 179);
   servo1.write(angle);
   delay(5);
}
