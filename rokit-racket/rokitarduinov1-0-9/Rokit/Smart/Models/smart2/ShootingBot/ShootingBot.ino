#include <SmartInventor.h>
#include <Servo.h> 

#define Shooting_SERVO1_MIN     40

#define Shooting_SERVO1_ORIGIN  80
#define Shooting_SERVO2_ORIGIN  90

#define Shooting_SERVO1_WAIT   115
#define Shooting_SERVO1_MAX    140

#define Shooting_SERVO2_MAX    150
#define Shooting_SERVO2_MIN     80

byte speedMeterL = 13;
byte speedMeterR = 16;

Servo servo1;
Servo servo2;

int sp = 50;
int keyData = 0;

// int deg1 = 90;
int deg2 = 90;

void setup()
{
  SmartInventor.TVRemoconUse();
  SmartInventor.DCMotorUse();

  //□ □ □ □ □ □ □ □
  //11,12,13,14,15,16,17,18

  //Led Output
  for (int thisPin = 11; thisPin <= 18; thisPin++)   {   
    pinMode(thisPin, OUTPUT);  
  } 
  digitalWrite(13,HIGH);
  digitalWrite(14,HIGH);
  digitalWrite(15,HIGH);
  digitalWrite(16,HIGH);

  servo1.attach(27);
  servo2.attach(28);
  servo1.write(Shooting_SERVO1_ORIGIN);
  servo2.write(Shooting_SERVO2_ORIGIN);
}
void  loop()
{
  keyData = SmartInventor.TVRemoconData();

  if(keyData == KEY_F4)
  {
    deg2++;

    if(deg2 >= Shooting_SERVO1_MAX ) deg2 = Shooting_SERVO1_MAX;
    servo2.write(deg2);
    delay(20);
  }
  else if(keyData == KEY_F3)
  {
    deg2--;

    if(deg2 <= Shooting_SERVO1_MIN ) deg2 = Shooting_SERVO1_MIN;
    servo2.write(deg2);
    delay(20);
  }
  else if(keyData == KEY_C)
  {
    for (int j = Shooting_SERVO1_ORIGIN; j < Shooting_SERVO1_WAIT; j++)
    {
      servo1.write(j);
      delay(10);
    }
    delay(500);
    servo1.write(Shooting_SERVO1_MAX);
    delay(1000);
    servo1.write(Shooting_SERVO1_MIN);
    delay(1000);
    servo1.write(Shooting_SERVO1_ORIGIN);
  }
  else if(keyData == KEY_U)
  {
    SmartInventor.DCMove(forward,sp);
  }
  else if(keyData == KEY_D)
  { 
    SmartInventor.DCMove(backward,sp);
  } 
  else if(keyData == KEY_L)
  {
    SmartInventor.DCMove(left, sp);
  }
  else if(keyData == KEY_R)
  {
    SmartInventor.DCMove(right,sp);
  }

  else SmartInventor.DCMove(stop,sp);

  if (keyData == KEY_F1)
  {
    if(SmartInventor.TimeCheckMillis(500) == true)	
    {		
      if(sp < 90)
      {
        sp = sp + 20;

        speedMeterL = speedMeterL -1;
        speedMeterR = speedMeterR +1;  

        digitalWrite(speedMeterL,HIGH);
        digitalWrite(speedMeterR,HIGH);

        SmartInventor.Buzz(1160,12); 
      }
    }
  }
  else if (keyData == KEY_F2)
  {
    //  Serial.println("speed down");
    if(SmartInventor.TimeCheckMillis(500) == true)
    {	
      if(sp > 30)
      {
        sp = sp - 20;

        digitalWrite(speedMeterL,LOW);
        digitalWrite(speedMeterR,LOW);
        speedMeterL = speedMeterL +1;
        speedMeterR = speedMeterR -1;  

        SmartInventor.Buzz(1160,12); 
      }
    }
  }
}






