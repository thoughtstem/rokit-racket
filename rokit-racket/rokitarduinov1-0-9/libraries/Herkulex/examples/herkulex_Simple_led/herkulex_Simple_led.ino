#include <Herkulex.h>

void setup()  
{
  int n=1; //set the motor ID
  Herkulex.beginSerial1(115200); //open serial1
  Herkulex.reboot(n); //reboot first motor
  delay(500); 
  Herkulex.initialize(); //initialize motors
  delay(200);  

  /*
   LED_GREEN =  0x01;
   LED_BLUE  =  0x02;
   LED_CYAN  =  0x03;
   LED_RED   =  0x04;
   LED_GREEN2=  0x05;
   LED_PINK= 0x06;
   LED_WHITE =  0x07;
   */

  Herkulex.setLed(n,LED_GREEN); //set the led to green

  Herkulex.end();
}

void loop(){
}





