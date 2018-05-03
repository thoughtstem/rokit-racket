#include <SmartInventor.h>
#include <Servo.h>

int analogInPin0 = A0;
int analogInPin1 = A1;
int analogInPin2 = A2;

byte speed = 40;

Servo myservo1;
byte angle1 = 90;

byte displayL = 11;
byte displayR = 18;

void setup()
{
  //□ □ □ □ □ □ □ □
  //11,12,13,14,15,16,17,18

  //Led Output
  for (int thisPin = 11; thisPin <= 18; thisPin++)   {
    pinMode(thisPin, OUTPUT);
  }

  SmartInventor.DCMotorUse();

  Serial.begin(57600);
  myservo1.attach(27);
  myservo1.write(90);
  delay(500);
}

void loop()
{
  int leftSensorValue = analogRead(analogInPin0);
  int centerSensorValue = analogRead(analogInPin1);
  int rightSensorValue = analogRead(analogInPin2);

  if (leftSensorValue < 400 || centerSensorValue < 400 || rightSensorValue < 400 )
  {
    SmartInventor.DCMove(stop, speed);

    myservo1.write(60);
    delay(500);

    if (leftSensorValue < 400)
    {
      myservo1.write(120);
      delay(500);

      if (rightSensorValue < 400)
      {
        SmartInventor.DCMove(backward, speed);
        myservo1.write(90);
        delay(1000);
        SmartInventor.DCMove(left, speed);
        delay(500);
      }
      else
      {
        SmartInventor.DCMove(right, speed);
        myservo1.write(90);
        delay(300);
      }
    }
    else
    {
      SmartInventor.DCMove(left, speed);
      myservo1.write(90);
      delay(300);
    }
  }
  else
  {
    SmartInventor.DCMove(forward, speed);

    if (SmartInventor.TimeCheckMillis(300))
    {
      SmartInventor.Buzz(1160, 12);

      digitalWrite(displayL, LOW);
      digitalWrite(displayR, LOW);

      displayL++;
      displayR--;

      if (displayL == 15) displayL = 11;
      if (displayR == 14) displayR = 18;

      digitalWrite(displayL, HIGH);
      digitalWrite(displayR, HIGH);

    }
  }
}




















