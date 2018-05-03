#include <Servo.h> 

#define  LedPin_01  8
#define  LedPin_02  9
#define  LedPin_03  10

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int pos;
int pos1;
void setup() {
 
    pinMode(LedPin_01, OUTPUT); 
    pinMode(LedPin_02, OUTPUT); 
    pinMode(LedPin_03, OUTPUT); 

    servo1.attach(16);  // attaches the servo on pin 16 to the servo object
    servo2.attach(17);  // attaches the servo on pin 17 to the servo object
    servo3.attach(18);  // attaches the servo on pin 18 to the servo object
    servo4.attach(19);  // attaches the servo on pin 19 to the servo objec
  
    pinMode(24, INPUT_PULLUP);
    pinMode(25, INPUT_PULLUP);
    
    digitalWrite(LedPin_01, HIGH);
    digitalWrite(LedPin_02, LOW);
    digitalWrite(LedPin_03, LOW);
    
    //basic motion
    servo1.write(135); servo2.write(90);    
    servo3.write(0); servo4.write(180);    
    delay(500);   
        
}

void loop() {
  
    if(digitalRead(24) == LOW)    
    {
      digitalWrite(LedPin_01, LOW);
      digitalWrite(LedPin_02, HIGH);
      digitalWrite(LedPin_03, LOW);
 
      //left motion - step1
      servo1.write(45);
      servo2.write(90); 
      servo3.write(0);
      servo4.write(45);  
      delay(1500); 
      
      //step2
      
      for(pos = 0; pos < 85; pos += 1)  // goes from 0 degrees to 180 degrees 
      {       
         servo2.write(90 - pos);
         servo3.write(pos);  
         delay(15); 
      }     
      
      //step3
      servo4.write(90);    
      delay(500); 

      //step4
      for(pos = 55; pos < 90; pos += 1)  // goes from 0 degrees to 180 degrees 
      {       
         servo2.write(pos);
         servo3.write(90 - pos);  
         delay(15); 
      }     
      //step5
      for(pos = 45; pos < 135; pos += 1)  // goes from 0 degrees to 180 degrees 
      {       
         servo1.write(pos);
         delay(15); 
      }   

      //step6
      
      for(pos = 0; pos < 85; pos += 1)  
      {   
        servo2.write(90 - pos);    
        servo3.write(pos); 
        delay(15); 
      }     

      //step7
      servo4.write(45);    
      delay(500); 
      
      //step8
      for(pos = 55; pos < 90; pos += 1)  // goes from 0 degrees to 180 degrees 
      {       
         servo2.write(pos);
         servo3.write(90 - pos); 
         delay(15); 
      }          
      //step8
      
      digitalWrite(LedPin_01, HIGH);
      digitalWrite(LedPin_02, LOW);
      digitalWrite(LedPin_03, LOW);
      
    }

    else if(digitalRead(25) == LOW) 
    {
      digitalWrite(LedPin_01, LOW);
      digitalWrite(LedPin_02, HIGH);
      digitalWrite(LedPin_03, LOW);
      
      //right motion - step1
      servo1.write(135); 
      servo2.write(90);    
      servo3.write(0); 
      servo4.write(45);    
      delay(1500); 
      
      //step2
      for(pos = 0; pos < 85; pos += 1)  // goes from 0 degrees to 180 degrees 
      {       
         servo2.write(90 - pos);
         servo3.write(pos);  
         delay(15); 
      }       

      //step3
      servo4.write(90);    
      delay(500); 

      //step4
      for(pos = 55; pos < 90; pos += 1)  // goes from 0 degrees to 180 degrees 
      {       
         servo2.write(pos);
         servo3.write(90 - pos); 
         delay(15); 
      }    
         
      //step5
      for(pos = 135; pos > 45; pos -= 1)  // goes from 0 degrees to 180 degrees 
      {       
         servo1.write(pos);
         delay(15); 
      } 
      
      //step6
      for(pos = 0; pos < 85; pos += 1)  
      {   
        servo2.write(90 - pos);    
        servo3.write(pos); 
        delay(15); 
      }       
      
      //step7
      servo4.write(45);    
      delay(500); 
      
      //step8
      for(pos = 55; pos < 90; pos += 1)  // goes from 0 degrees to 180 degrees 
      {       
         servo2.write(pos);
         servo3.write(90 - pos); 
         delay(15); 
      }          
      digitalWrite(LedPin_01, LOW);
      digitalWrite(LedPin_02, LOW);
      digitalWrite(LedPin_03, HIGH);
      
    }
    
}
