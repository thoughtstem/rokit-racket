
void RiceBarleyBot()
{
  SmartInventor.DCMotorUse();
  
  DDRC = 0xff;
  PORTC = 0;
  
  byte sensorOffset = 50;
  byte findTime = 0;

  delay(500);

  while (1)
  {
    word selectLevelA1 = SmartInventor.SensorCalibration(A1) - sensorOffset;
    word centerSensorValue = analogRead(A1);
    PORTC = 0;
    byte sensor = analogRead(A1) / 200;
    byte speedMeterL = 14 - sensor;
    byte speedMeterR = 15 + sensor;
    
    digitalWrite(speedMeterL, HIGH);
    digitalWrite(speedMeterR, HIGH);
    
    byte actionTime = random(50, 254);
    
    if (centerSensorValue < selectLevelA1)
    {
      findTime++;
      
      if (findTime > actionTime)
      {
        findTime = 0;
        
        SmartInventor.Buzz(1160, 8);
        SmartInventor.DCMotor(M1, CW, 100);
        SmartInventor.DCMotor(M2, CW, 100);
        delay(1000);

        SmartInventor.DCMotor(M1, CW, 60);
        SmartInventor.DCMotor(M2, CW, 60);
        delay(2000);
        SmartInventor.DCMotor(M1, CCW, 100);
        SmartInventor.DCMotor(M2, CCW, 100);
        delay(100);
        SmartInventor.DCMotor(M1, LOOSE, 100);
        SmartInventor.DCMotor(M2, LOOSE, 100);
        
        SmartInventor.Buzz(1160, 12);
        SmartInventor.Buzz(740, 8);
      }
    }
  }
}

