#include <Herkulex.h>

int n=1; //motor ID - verify your ID !!!!

void setup()  
{
  Herkulex.beginSerial1(115200); //open serial1
  Herkulex.reboot(n); //reboot first motor
  delay(500); 
  Herkulex.initialize(); //initialize motors
  delay(200);  
}

void loop(){

  Herkulex.moveSpeedOne(n, 500, 500, LED_BLUE);
  delay(1200);

  Herkulex.moveSpeedOne(n, -500, 500, LED_BLUE);
  delay(1200);

  Herkulex.moveSpeedOne(n, 0, 500, LED_BLUE);
  delay(1200);

  while(1);
}



