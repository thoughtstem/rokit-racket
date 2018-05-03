#include <Servo.h> 
#include <MsTimer2.h>
#include <DCM.h>
#include <RFRemocon.h>

int flag=0;

DCM motor1;
DCM motor2;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

void setup() {
    
    RFRemocon.begin(57600);
       
    motor1.attachPins(20,21);  
    motor2.attachPins(22,23);
    
    servo1.attach(16);  // attaches the servo on pin 9 to the servo object
    servo2.attach(17);  // attaches the servo on pin 9 to the servo object
    servo3.attach(18);  // attaches the servo on pin 9 to the servo object
    servo4.attach(19);  // attaches the servo on pin 9 to the servo object

}

void loop() {
    int Data = RFRemocon.recieve();
    if(Data >= 0)
    {
      if(Data == 0){ motor1.write(LOOSE,10); motor2.write(LOOSE,10);}
      else{
      if(Data == KEY_U) {motor1.write(CW,10); motor2.write(CCW, 10);}
      else if(Data == KEY_D) {motor1.write(CCW, 10); motor2.write(CW,10);} 
      else if(Data == KEY_L) {motor1.write(CW,10); motor2.write(CW,10); }
      else if(Data == KEY_R) {motor1.write(CCW,10); motor2.write(CCW,10); }
      
      
      else if(Data == KEY_1) 
      {servo1.write(0); servo2.write(180); 
       servo3.write(90); servo4.write(90);       
       flag=2;}  

      else if(Data == KEY_2) flag = 0; 
      
      else if(Data == KEY_3) 
       { servo1.write(45); servo2.write(135); 
        servo3.write(90); servo4.write(90); }
        
      else if(Data == KEY_4)  
       { servo1.write(0); servo2.write(180); 
        servo3.write(90); servo4.write(135); }
      
      if(flag == 0)
      {servo1.write(120); servo2.write(60); 
      servo3.write(120); servo4.write(60); 
      delay(300);  flag=1;}  
      
      if(flag == 1)
      {servo1.write(60); servo2.write(120); 
      servo3.write(60); servo4.write(120); 
      delay(300);  flag=0;}  
      }
  }
  
}

