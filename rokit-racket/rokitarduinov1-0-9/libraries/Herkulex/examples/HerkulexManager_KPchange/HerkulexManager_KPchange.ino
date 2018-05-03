#include <Herkulex.h>

int n=1; //motor ID - verify your ID !!!!

void setup()  
{
  Herkulex.beginSerial1(115200); //open serial1
  Herkulex.reboot(n); //reboot first motor
  delay(500); 
  Herkulex.initialize(); //initialize motors
  delay(200);  

  Herkulex.set_KP(n,125);  //id 1 : KP 125 SET

  delay(200);  
}

void loop(){

}



