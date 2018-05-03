#include <Servo.h> 

Servo servo1;
Servo servo2;
Servo servo3;

int angle1 = 0;
int angle2 = 0;
int angle3 = 0;



void setup() {
    servo1.attach(16);  // attaches the servo on pin 16 to the servo object
    servo2.attach(17);  // attaches the servo on pin 17 to the servo object
    servo3.attach(18);  // attaches the servo on pin 18 to the servo object
}

void loop() {

    angle1 = analogRead(A0);     
    angle2 = analogRead(A1);     
    angle3 = analogRead(A2);     
    
    angle1 = map(angle1, 0, 1023, 0, 180); 
    angle2 = map(angle2, 0, 1023, 50, 180);
    angle3 = map(angle3, 0, 1023, 50, 180);

    servo1.write(angle1); 
    servo2.write(angle2); 
    servo3.write(angle3); 
   
    }
