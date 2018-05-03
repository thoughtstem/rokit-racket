#include <Servo.h> 

Servo servo1;
Servo servo2;
Servo servo3;

int angleX = 0;
int angleY = 0;

void setup() {
  servo1.attach(16);  // attaches the servo on pin 16 to the servo object
  servo2.attach(17);  // attaches the servo on pin 17 to the servo object
  servo3.attach(18);  // attaches the servo on pin 18 to the servo object
  
  pinMode(26, INPUT_PULLUP);
  pinMode(8, OUTPUT); 
  
  servo3.write(45);
}

void loop() {

  angleX = analogRead(A0);     
  angleY = analogRead(A1);     
  
  angleX = map(angleX, 0, 1023, 0, 180); 
  angleY = map(angleY, 0, 1023, 0, 110);
  
  if (digitalRead(26) == LOW)
  {
    digitalWrite(8, HIGH);
    servo3.write(125); 
    delay(500);
    digitalWrite(8, LOW);
  }
  
  servo1.write(angleX); 
  servo2.write(angleY); 
  servo3.write(45); 
  
}
