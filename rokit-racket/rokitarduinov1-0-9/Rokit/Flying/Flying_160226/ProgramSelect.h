#include <RokitFlying.h>

int ProgramSelect()
{
  byte displayLed[] = {13, 14, 15, 16, 17};
  byte ledIndex = 0;
  byte ledSign = 0;
  int selectSw = 2;
  int startSw = 3;
  boolean selectModeEnd = false;
  
  for (int i = 0; i <= 4 ; i++)
  {
    pinMode(displayLed[i], OUTPUT);
    digitalWrite(displayLed[i], LOW);
  }

  pinMode(selectSw, INPUT);
  pinMode(startSw, INPUT);

  digitalWrite(displayLed[ledIndex], HIGH);

  while (selectModeEnd == false)
  {
    if (!digitalRead(selectSw))
    {
      ledSign++;
      if (ledSign == 15)
      {
        ledSign = 0;
      }

      for (int i = 0; i <= 4 ; i++)
      {
        digitalWrite(displayLed[i], LOW);
      }

      if (ledSign >= 13)
      {
        digitalWrite(displayLed[1], HIGH);
        digitalWrite(displayLed[2], HIGH);
        digitalWrite(displayLed[3], HIGH);
        digitalWrite(displayLed[4], HIGH);
        ledIndex = ledSign - 14;
      }

      else  if (ledSign >= 11)
      {
        digitalWrite(displayLed[2], HIGH);
        digitalWrite(displayLed[3], HIGH);
        digitalWrite(displayLed[4], HIGH);
        ledIndex = ledSign - 12;
      }

      else  if (ledSign >= 8)
      {
        digitalWrite(displayLed[3], HIGH);
        digitalWrite(displayLed[4], HIGH);
        ledIndex = ledSign - 9;
      }

      else if (ledSign >= 4)
      {
        digitalWrite(displayLed[4], HIGH);
        ledIndex = ledSign - 5;
      }
      else
      {
        ledIndex = ledSign;
      }

      switch (ledIndex)
      {
        case 0 : digitalWrite(displayLed[ledIndex], HIGH); break;
        case 1 : digitalWrite(displayLed[ledIndex], HIGH); break;
        case 2 : digitalWrite(displayLed[ledIndex], HIGH); break;
        case 3 : digitalWrite(displayLed[ledIndex], HIGH); break;
      }

      do
      {
        delay(10);
      } while (!digitalRead(selectSw));
    }

    if (!digitalRead(startSw))
    {
      selectModeEnd = true;
      do
      {
        delay(10);
      } while (!digitalRead(startSw));
    }
  }


  for (int j = 0; j <= 1 ; j++)
  {
    RokitFlying.LedPerformance(1, 100);
  }


  return ledSign + 1;
}

