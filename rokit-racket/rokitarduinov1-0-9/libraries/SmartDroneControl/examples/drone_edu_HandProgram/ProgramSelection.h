#include <SmartInventor.h>

int ProgramSelection(byte mode);
void LedProgramStart();
void SelectSound(int direction);

int leftSensor = 0;
int centerSensor = 1;
int rightSensor = 2;

int ProgramSelection(byte mode)
{
  SmartInventor.TVRemoconUse();

  for (int thisPin = 11; thisPin <= 18; thisPin++)   {
    pinMode(thisPin, OUTPUT);
  }

  digitalWrite(11, HIGH);

  byte selectMode = 1;
  byte selectModeEnd = 0;

  byte modeMax = 27;
  word sensorOffsetA0 = 300;
  word sensorOffsetA1 = 300;
  word sensorOffsetA2 = 300;

  int inputMode = mode;
  int keyData = 0;

  boolean nearSensorMode = false;

  if (SmartInventor.SensorCalibration(A1) <= 300) nearSensorMode = true;

  delay(100);

  int note = 1000;
  int length = 4;
  
//  Serial.begin(57600);

  while (selectModeEnd == 0)
  {
    word  selectLevelA0 = SmartInventor.SensorCalibration(A0);
    word  selectLevelA1 = SmartInventor.SensorCalibration(A1);
    word  selectLevelA2 = SmartInventor.SensorCalibration(A2);

    //**********************************************//
    if (nearSensorMode) sensorOffsetA1 = 0;
    //**********************************************//

    selectLevelA0 = selectLevelA0 - sensorOffsetA0;
    selectLevelA1 = selectLevelA1 - sensorOffsetA1;
    selectLevelA2 = selectLevelA2 - sensorOffsetA2;

    keyData = SmartInventor.TVRemoconData();

    SmartInventor.PreviousMillis = millis();
    while (!SmartInventor.TimeCheckMillis(100));

    if (inputMode == 1)
    {
      if ((keyData == CH1_KEY_L) || (keyData == CH2_KEY_L) || (keyData == CH3_KEY_L) || (keyData == CH4_KEY_L))
      {
        selectMode--;
        if (selectMode == 0) selectMode = modeMax;
        SmartInventor.LedPerformanceNumber(selectMode - 1);
        SelectSound(leftSensor);
      }

      else if ((keyData == CH1_KEY_R) || (keyData == CH2_KEY_R) || (keyData == CH3_KEY_R) || (keyData == CH4_KEY_R))
      {
        selectMode++;
        if (selectMode > modeMax) selectMode = 1;
        SmartInventor.LedPerformanceNumber(selectMode - 1);
        SelectSound(rightSensor);
      }

      else if ((keyData == CH1_KEY_C) || (keyData == CH2_KEY_C) || (keyData == CH3_KEY_C) || (keyData == CH4_KEY_C))
      {
        SmartInventor.LedPerformanceNumber((selectMode - 1));
        SelectSound(centerSensor);
        LedProgramStart();
        selectModeEnd = 1;
      }
    }
    
    /*************Remocon & Sensor**********************************************************/
    else
    {
      word leftSensorValue = analogRead(A0);
      word centerSensorValue = analogRead(A1);
      word rightSensorValue = analogRead(A2);

      if ((leftSensorValue < selectLevelA0) || (keyData == CH1_KEY_L) || (keyData == CH2_KEY_L) || (keyData == CH3_KEY_L) || (keyData == CH4_KEY_L))
      {
        selectMode--;
        if (selectMode == 0) selectMode = modeMax;
        SmartInventor.LedPerformanceNumber(selectMode - 1);

        SelectSound(leftSensor);
      }

      else if ((rightSensorValue < selectLevelA2) || (keyData == CH1_KEY_R) || (keyData == CH2_KEY_R) || (keyData == CH3_KEY_R) || (keyData == CH4_KEY_R))
      {
        selectMode++;
        if (selectMode > modeMax) selectMode = 1;
        SmartInventor.LedPerformanceNumber(selectMode - 1);

        SelectSound(rightSensor);
      }

      else if ((centerSensorValue < selectLevelA1) || (keyData == CH1_KEY_C) || (keyData == CH2_KEY_C) || (keyData == CH3_KEY_C) || (keyData == CH4_KEY_C))
      {
        SmartInventor.LedPerformanceNumber((selectMode - 1));

        SelectSound(centerSensor);

        LedProgramStart();
        selectModeEnd = 1;
      }
    }
  }

  SmartInventor.TVRemoconClose();
  return selectMode;
}

void LedProgramStart()
{
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
    delay(100);
  }

  for (int thisPin = pinCount - 1; thisPin >= 0; thisPin--) {
    delay(100);
    digitalWrite(ledPins[thisPin], LOW);
  }
}


void SelectSound(int direction)
{
  SmartInventor.TVRemoconClose();
  if (direction == leftSensor)
  {
       SmartInventor.Buzz(1542, 20);
       SmartInventor.Buzz(2315, 16);
 //   SmartInventor.Buzz(NOTE_F6, 20);
 //   SmartInventor.Buzz(NOTE_D7, 16);
  }
  else if (direction == rightSensor)
  {
       SmartInventor.Buzz(1542, 20);
       SmartInventor.Buzz(2315, 16);
 //   SmartInventor.Buzz(NOTE_F6, 20);
 //   SmartInventor.Buzz(NOTE_D7, 16);
  }
  else if (direction == centerSensor)
  {
       SmartInventor.Buzz(1981, 12);
       SmartInventor.Buzz(2132, 12);
       SmartInventor.Buzz(2315, 8);

  //  SmartInventor.Buzz(NOTE_C7, 12);
  //  SmartInventor.Buzz(NOTE_D7, 12);
  //  SmartInventor.Buzz(NOTE_E7, 8);
  }
  SmartInventor.TVRemoconUse();
}




