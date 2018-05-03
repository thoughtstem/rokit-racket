#include <SmartInventor.h>
#include <Servo.h> 

#define Grip_SERVO1_ORIGIN  90
#define Grip_SERVO2_ORIGIN  90

#define Grip_SERVO1_MIN     50
#define Grip_SERVO1_MAX    110

#define Grip_SERVO2_MIN     40
#define Grip_SERVO2_MAX    130


Servo servo1;
Servo servo2;

int sp = 50;
int keyData = 0;
boolean toggle = false;

//  int deg1 = SERVO1_ORIGIN;
int deg2 = Grip_SERVO2_ORIGIN;

byte speedMeterL = 13;
byte speedMeterR = 16;


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

  servo1.write(Grip_SERVO1_ORIGIN);
  servo2.write(90);

}

void loop()
{
  keyData = SmartInventor.TVRemoconData();

  if(keyData == KEY_F4)
  {
    deg2++;                                                                                                                                     

    if(deg2 >= Grip_SERVO1_MAX ) deg2 = Grip_SERVO2_MAX;
    servo2.write(deg2);
    delay(10);
  }
  else if(keyData == KEY_F3)
  {
    deg2--;

    if( deg2 <= Grip_SERVO2_MIN ) deg2 = Grip_SERVO2_MIN;
    servo2.write(deg2);
    delay(10);
  }
  else if(keyData == KEY_C)
  {
    if( toggle == true) {
      servo1.write(Grip_SERVO1_MAX); 
      toggle = false;
    }
    else if(toggle == false) {
      servo1.write(Grip_SERVO1_MIN); 
      toggle = true;
    }
    delay(500);
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

        SmartInventor.Buzz(NOTE_C5,12); 
      }
    }
  }
  else if (keyData == KEY_F2)
  {
    if(SmartInventor.TimeCheckMillis(500) == true)
    {	
      if(sp > 30)
      {
        sp = sp - 20;

        digitalWrite(speedMeterL,LOW);
        digitalWrite(speedMeterR,LOW);
        speedMeterL = speedMeterL +1;
        speedMeterR = speedMeterR -1;  

        SmartInventor.Buzz(NOTE_E5,12); 
      }
    }
  }
}
