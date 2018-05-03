#include <SmartInventor.h>

void AutoCrossBar()
{

int melody[] = {
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4 };
  
  SmartInventor.DCMotorUse();

  //□ □ □ □ □ □ □ □
  //11,12,13,14,15,16,17,18
  //BOTTOM SENSOR USE

  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  pinMode(17, INPUT);

  byte speed = 20;

  word interval = 5000;

  SmartInventor.DCMove(forward, speed);

  unsigned long oldTime =  millis();

  while (1)
  {
    SmartInventor.DCMotor(M1, CCW, speed);
    SmartInventor.DCMotor(M2, CW, speed);

    // unsigned long nowTime = millis();

    if (oldTime + interval > millis())
    {
      if (digitalRead(12) || digitalRead(13) || digitalRead(14) || digitalRead(15) || digitalRead(16) || digitalRead(17))
      {
        SmartInventor.DCMotor(M1, stop, speed);
        SmartInventor.DCMotor(M2, stop, speed);

        speed += 10;

        for (int i = 0; i < speed/10 -2; i++)
        {
            SmartInventor.Buzz(melody[i], 8);
        }

        //□ □ □ □ □ □ □ □
        //11,12,13,14,15,16,17,18
        int ledPins[] = {
          11, 12, 13, 14, 15, 16, 17, 18
        };
        int pinCount = 8;
        for (int thisPin = 0; thisPin < pinCount; thisPin++)  {
          pinMode(ledPins[thisPin], OUTPUT);
        }

        for (int thisPin = 0; thisPin < pinCount; thisPin++) {
          digitalWrite(ledPins[thisPin], HIGH);
          delay(50);
        }

        for (int thisPin = pinCount - 1; thisPin >= 0; thisPin--) {
          delay(50);
          digitalWrite(ledPins[thisPin], LOW);
        }

        pinMode(12, INPUT);
        pinMode(13, INPUT);
        pinMode(14, INPUT);
        pinMode(15, INPUT);
        pinMode(16, INPUT);
        pinMode(17, INPUT);

        if (speed > 100)
        {
          speed = 20;
        }

        while (digitalRead(12) || digitalRead(13) || digitalRead(14) || digitalRead(15) || digitalRead(16) || digitalRead(17))
          delay(1500);

        oldTime =  millis();
      }
    }
    else
    {
      SmartInventor.Buzz(2315, 8);
      SmartInventor.Buzz(1981, 12);
      speed = 20;
      oldTime =  millis();
    }

  }
}


