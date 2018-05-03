#include <SmartInventor.h>
#include <Servo.h> 

#define Handball_SERVO1_ORIGIN  90
#define Handball_SERVO2_ORIGIN  80

#define Handball_SERVO1_INIT   120
#define Handball_SERVO2_INIT    50              
#define Handball_SERVO1_MAX    165
#define Handball_SERVO2_MIN      5 

Servo servo1;
Servo servo2;

byte speedMeterL = 13;
byte speedMeterR = 16;

int sp = 50;
int keyData = 0;
int deg1 = Handball_SERVO1_ORIGIN;
int deg2 = Handball_SERVO2_ORIGIN;

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

  servo1.write(deg1);
  servo2.write(deg2);
  delay(1000);
}
void loop()
{
  keyData = SmartInventor.TVRemoconData();

  if(keyData == KEY_F3)
  {
    servo1.attach(27);
    servo2.attach(28);     
    servo1.write(Handball_SERVO1_ORIGIN);
    servo2.write(Handball_SERVO2_ORIGIN);
    delay(1000);

    servo1.detach();
    servo2.detach();  
  }
  else if(keyData == KEY_F4)
  {
    servo1.attach(27);
    servo2.attach(28);
    servo1.write(Handball_SERVO1_MAX);
    servo2.write(Handball_SERVO2_MIN);
    delay(1000);

    servo1.detach();
    servo2.detach(); 
  }
  else if(keyData == KEY_C)
  {
    servo1.attach(27);
    servo2.attach(28);
    servo1.write(Handball_SERVO1_INIT);
    servo2.write(Handball_SERVO2_INIT);
    delay(1000);

    servo1.detach();
    servo2.detach(); 
  }

  if(keyData == KEY_U)
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

        SmartInventor.Buzz(NOTE_E5,12); 
      }
    }
  }
}






