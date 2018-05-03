#include <Servo.h> 
#include <MsTimer2.h>
#include <DCM.h>
#include <RFRemocon.h>


DCM motor1;
DCM motor2;

Servo servo1;
Servo servo2;
Servo servo3;

int angle1 = 90;
int angle2 = 90;
int angle3 = 90;

void setup() {
  
    RFRemocon.begin(57600);
       
    motor1.attachPins(20,21);  
    motor2.attachPins(22,23);
    
    servo1.attach(16);  // attaches the servo on pin 9 to the servo object
    servo2.attach(17);  // attaches the servo on pin 9 to the servo object
    servo3.attach(18);  // attaches the servo on pin 9 to the servo object
   
    servo1.write(angle1); 
    servo2.write(angle2);  
    servo3.write(angle3);
}

void loop() {
  // put your main code here, to run repeatedly: 
    int Data = RFRemocon.recieve();
    if(Data >= 0)
    {
      if(Data == KEY_U) {motor1.write(CCW,10); motor2.write(CW, 10);}
   else if(Data == KEY_D) {motor1.write(CW, 10); motor2.write(CCW,10);} 
   else if(Data == KEY_L) {motor1.write(CW,10); motor2.write(CW,10); }
   else if(Data == KEY_R) {motor1.write(CCW,10); motor2.write(CCW,10); }
   else { motor1.write(LOOSE,10); motor2.write(LOOSE,10);}
   
   if(Data == KEY_1) 
   {
     if(angle1 > 75)
      {
        angle1 = angle1 - 1;
      }  
   }
    
   else if(Data == KEY_2) 
   {
     if(angle2 < 125)
      {
        angle2 = angle2 + 1;
      }  
   }  
     
   else if(Data == KEY_3)  
   {
     if(angle1 < 180)
      {
        angle1 = angle1 + 1;
      }    
    }
   
   else if(Data == KEY_4)  
   {
     if(angle2 > 0)
      {
        angle2 = angle2 - 1;
      }  
    }  
    
   else if(Data == KEY_5)  
   {
     if(angle3 < 90)
     {
        angle3 = angle3 + 1;
     }  
   }   
   else if(Data == KEY_6)  
   {
     if(angle3 > 60)
     {
       angle3 = angle3 - 1;
     }  
   }  
 } 
   servo1.write(angle1); 
   servo2.write(angle2);  
   servo3.write(angle3);
  //delay(1);
//  delayMicroseconds() ;
}


