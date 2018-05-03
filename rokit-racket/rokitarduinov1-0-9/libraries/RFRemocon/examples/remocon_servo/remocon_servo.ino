#include <RFRemocon.h>
#include <Servo.h>

Servo myservo0;  // create servo object to control a servo0 
Servo myservo1;  // create servo object to control a servo1 

void setup()
{
  RFRemocon.begin(57600);  //ZigBee - baud rate
  
  myservo0.attach(16);  // attaches the servo on pin 16 to the servo object 
  myservo1.attach(17);  // attaches the servo on pin 17 to the servo object 
}

void loop()
{
  int data = RFRemocon.receive();
  if(data >= 0)
  {
  if(data & KEY_U)
  {
    myservo0.write(10);  
    myservo1.write(170);  
   }
  if(data & KEY_D)
  {
    myservo0.write(120);  
    myservo1.write(60);  
  }
  if(data & KEY_L)
  {
    myservo0.write(90); 
    myservo1.write(90);   
  }
  if(data & KEY_R)
  {
    myservo0.write(0);  
    myservo1.write(180);  
  }
  }
}
