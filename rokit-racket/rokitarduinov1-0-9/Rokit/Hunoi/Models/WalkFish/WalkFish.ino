
#include <Servo.h> 

#define  LedPin_01  8
#define  LedPin_02  9
#define  LedPin_03  10

int light = 0;
int wait = 120;
Servo servo1;
Servo servo2;

void setup() {

pinMode(LedPin_01, OUTPUT); 
pinMode(LedPin_02, OUTPUT); 
pinMode(LedPin_03, OUTPUT); 

pinMode(24, INPUT_PULLUP);

servo1.attach(16);  // attaches the servo on pin 16 to the servo object
servo2.attach(17);  // attaches the servo on pin 17 to the servo object


}

void loop() {
  // put your main code here, to run repeatedly: 
   
  if(light==1)
  {
  digitalWrite(LedPin_01, HIGH);
  digitalWrite(LedPin_02, LOW);
  digitalWrite(LedPin_03, LOW);
  }  
  
  else if(light==2)
  {
  digitalWrite(LedPin_01, LOW);
  digitalWrite(LedPin_02, HIGH);
  digitalWrite(LedPin_03, LOW);
  }  
  
  else if(light==3)
  {
  digitalWrite(LedPin_01, LOW);
  digitalWrite(LedPin_02, LOW);
  digitalWrite(LedPin_03, HIGH);
  }  
  
  else
  {
  light=0;
  digitalWrite(LedPin_01, LOW);
  digitalWrite(LedPin_02, LOW);
  digitalWrite(LedPin_03, LOW);
  }  
  
  light=light+1;
  
  if (digitalRead(24) == HIGH)
  {
    servo1.write(110);    
    servo2.write(115);   
    delay(wait);   
    
    servo1.write(70);    
    servo2.write(115);    
    delay(wait);   
    
    servo1.write(70);    
    servo2.write(65);    
    delay(wait);   
    
    servo1.write(110);    
    servo2.write(65);    
    delay(wait);   
  }
}
