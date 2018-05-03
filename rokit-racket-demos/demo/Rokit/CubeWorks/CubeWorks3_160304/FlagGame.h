#include <SmartInventor.h>
#include <Servo.h>

void FlagGame()
{
  delay(500);

  byte speed = 50;
  boolean sucess = 0;

  byte count = 0;

  word sensorOffset = 50;
  word  selectLevelA0 = 0;
  word  selectLevelA2 = 0;

  SmartInventor.DCMotorUse();

  selectLevelA0 = SmartInventor.SensorCalibration(A0) - sensorOffset;
  selectLevelA2 = SmartInventor.SensorCalibration(A2) - sensorOffset;

  while (1)
  {
    if ( SmartInventor.TimeCheckMillis(3000))
    {
      byte mode = random(1, 4);

      if (mode == 1)
      {
        SmartInventor.DCMotor(M1, CW, speed);
        delay(500);
        SmartInventor.DCMotor(M1, STOP, speed);
      }
      else if (mode == 2)
      {
        SmartInventor.DCMotor(M2, CCW, speed);
        delay(500);
        SmartInventor.DCMotor(M2, STOP, speed);
      }
      else if (mode == 3)
      {
        SmartInventor.DCMotor(M1, CW, speed);
        SmartInventor.DCMotor(M2, CCW, speed);
        delay(500);
        SmartInventor.DCMotor(M1, STOP, speed);
        SmartInventor.DCMotor(M2, STOP, speed);
      }


      while (!SmartInventor.TimeCheckMillis(1000) && sucess == false)
      {
        word leftSensorValue = analogRead(A0);
        word rightSensorValue = analogRead(A2);

        if (leftSensorValue < selectLevelA0 && rightSensorValue < selectLevelA2)
        {
          if (mode == 3)
          {
            SmartInventor.Buzz(1981, 12);
            SmartInventor.Buzz(2132, 12);
            sucess = true;
          }
        }

        if (leftSensorValue < selectLevelA0)
        {
          if (mode == 1)
          {
            SmartInventor.Buzz(1981, 12);
            SmartInventor.Buzz(2132, 12);
            sucess = true;
          }
        }

        else if (rightSensorValue < selectLevelA2)
        {
          if (mode == 2)
          {
            SmartInventor.Buzz(1981, 12);
            SmartInventor.Buzz(2132, 12);
            sucess = true;
          }
        }
      }

      if (mode == 1)
      {
        SmartInventor.DCMotor(M1, CCW, speed);
        delay(350);
        SmartInventor.DCMotor(M1, STOP, speed);
      }
      else if (mode == 2)
      {
        SmartInventor.DCMotor(M2, CW, speed);
        delay(350);
        SmartInventor.DCMotor(M2, STOP, speed);
      }
      else if (mode == 3)
      {
        SmartInventor.DCMotor(M1, CCW, speed);
        SmartInventor.DCMotor(M2, CW, speed);
        delay(350);
        SmartInventor.DCMotor(M1, STOP, speed);
        SmartInventor.DCMotor(M2, STOP, speed);
      }
      sucess = false;
    }
  }

}






