#include <Herkulex.h>

int n=1; //motor ID - verify your ID !!!!

void setup()  
{
  Herkulex.beginSerial1(115200); //open serial1
  Herkulex.reboot(n); //reboot first motor
  delay(500); 
  Herkulex.initialize(); //initialize motors
  delay(200);
  Herkulex.torqueOFF(n);
  Serial.begin(57600);

}

void loop()
{
  float angle;
  
  angle = Herkulex.getAngle(n);
  Serial.println(angle);
  delay(10);
}



