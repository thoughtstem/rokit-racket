#include <Herkulex.h>

void setup()  
{
  Herkulex.beginSerial1(115200); //open serial1
  // Herkulex.reboot(BROADCAST_ID); //reboot all motor
  Herkulex.reboot(1); //reboot first motor
  Herkulex.reboot(2); //reboot second motor
  delay(500); 
  Herkulex.initialize(); //initialize motors
  delay(200);  

  Herkulex.moveSpeedAll(1,300,1);
  Herkulex.moveSpeedAll(2,300,1);
  Herkulex.actionAll(672);
  delay(2500); 

  // move all to position
  Herkulex.moveAll(1, 200, 2); //move to position 200
  Herkulex.moveAll(2, 420, 2); //move to position 820 
  Herkulex.actionAll(1000); //start movement in 1500 milliseconds
  delay(1100);

  // move all to angle
  Herkulex.moveAllAngle(1, 120.5, 2);
  Herkulex.moveAllAngle(2, -120.5, 2); 
  Herkulex.actionAll(2000);
  delay(2100);

  Herkulex.setLed(2,LED_PINK); //set the led 
  Herkulex.setLed(1,LED_GREEN2); //set the led

  Herkulex.end();
}

void loop(){
}


