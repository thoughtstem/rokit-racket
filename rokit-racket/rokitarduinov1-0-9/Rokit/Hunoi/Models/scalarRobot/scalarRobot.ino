#include <Servo.h> 
#include <RFRemocon.h>

#define  LedPin_01  8
#define  LedPin_02  9
#define  LedPin_03  10



Servo servo1;
Servo servo2;
Servo servo3;

int red = 0;
int blue = 0;
int green = 0;


void setup() {
  
    RFRemocon.begin(57600);
    
    pinMode(LedPin_01, OUTPUT); 
    pinMode(LedPin_02, OUTPUT); 
    pinMode(LedPin_03, OUTPUT); 

    servo1.attach(16);  // attaches the servo on pin 16 to the servo object
    servo2.attach(17);  // attaches the servo on pin 17 to the servo object
    servo3.attach(18);  // attaches the servo on pin 18 to the servo object
    
    //basic motion
    servo1.write(180); 
    servo2.write(30);    
    servo3.write(70);     
    delay(500);   

}

void loop() {
  
    int Data = RFRemocon.recieve();
    if(Data >= 0)
    {
    red = analogRead(A0);     
    blue = analogRead(A1);     
    green = analogRead(A2);   

     if(Data == KEY_U)
     { 
       servo1.write(180); 
       servo2.write(30); 
       servo3.write(90); 
       delay(1000);

       servo1.write(180); 
       servo2.write(170); 
       servo3.write(90); 
       delay(1500);
        
       servo1.write(180); 
       servo2.write(170); 
       servo3.write(170); 
       delay(1000);
        
       servo1.write(180); 
       servo2.write(30); 
       servo3.write(170); 
       delay(1500);

      
     }

    if(green < 900) 
    {
      digitalWrite(LedPin_01, LOW);
      digitalWrite(LedPin_02, LOW);      
      digitalWrite(LedPin_03, HIGH); 
     
        servo1.write(180); 
        servo2.write(30); 
        servo3.write(170); 
        delay(1500);
       
        servo1.write(90); 
        servo2.write(30); 
        servo3.write(170); 
        delay(1500);
  
        servo1.write(90); 
        servo2.write(170); 
        servo3.write(170); 
        delay(1500);
         
        servo1.write(90); 
        servo2.write(170); 
        servo3.write(50); 
        delay(1000);     
        
        servo1.write(180); 
        servo2.write(30); 
        servo3.write(170); 
        delay(2000);     
       
    }
    
    else if(blue < 700) 
    {
      digitalWrite(LedPin_01, LOW);
      digitalWrite(LedPin_02, HIGH);
      digitalWrite(LedPin_03, LOW);
      
      servo1.write(180); 
      servo2.write(30); 
      servo3.write(170); 
      delay(1500);
     
      servo1.write(45); 
      servo2.write(30); 
      servo3.write(170); 
      delay(1500);

      servo1.write(45); 
      servo2.write(170); 
      servo3.write(170); 
      delay(1500);
       
      servo1.write(45); 
      servo2.write(170); 
      servo3.write(50); 
      delay(1000);     
      
      servo1.write(180); 
      servo2.write(30); 
      servo3.write(170); 
      delay(2000);    
     
    }
    
    else if(red < 700) 
    {
      digitalWrite(LedPin_01, HIGH);
      digitalWrite(LedPin_02, LOW);
      digitalWrite(LedPin_03, LOW);
      
      servo1.write(0); 
      servo2.write(30); 
      servo3.write(170); 
      delay(1500);

      servo1.write(0); 
      servo2.write(170); 
      servo3.write(170); 
      delay(1500);
       
      servo1.write(0); 
      servo2.write(170); 
      servo3.write(50); 
      delay(1000);     
      
      servo1.write(180); 
      servo2.write(30); 
      servo3.write(170); 
      delay(2000);  
    }
    
    else
   {
      digitalWrite(LedPin_01, LOW);
      digitalWrite(LedPin_02, LOW);
      digitalWrite(LedPin_03, LOW);
    }
    }
} 
