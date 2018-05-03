
#include<Servo.h>
#include <EEPROM.h>

#define SERVO_ORIGIN  90

void ServoAngleTuner()
{
  Servo servo[4];

  int deg[4] = {SERVO_ORIGIN, SERVO_ORIGIN, SERVO_ORIGIN, SERVO_ORIGIN};
  int delta[4] = {0, 0, 0, 0};
  int servoSelect;

  servo[0].attach(27);
  servo[1].attach(28);
  servo[2].attach(29);
  servo[3].attach(30);

  servo[0].write(deg[0]);
  servo[1].write(deg[1]);
  servo[2].write(deg[2]);
  servo[3].write(deg[3]);

  SmartInventor.TVRemoconUse();
  //  SmartInventor.LedArray(0b00000001);
  PORTC = 0b00000001;

  //Serial.begin(9600);

  Serial.println("Servo0");

  while (1)
  {
    int keyData = SmartInventor.TVRemoconData();

    if (keyData == KEY_F1)
    {
      PORTC = 0b00000001;
      servoSelect = 0;

      Serial.println("Servo0");

      delay(500);
    }
    else if (keyData == KEY_F2)
    {
      PORTC = 0b00000010;
      servoSelect = 1;

      Serial.println("Servo1");

      delay(500);
    }
    else if (keyData == KEY_F3)
    {
      PORTC = 0b00000100;
      servoSelect = 2;

      Serial.println("Servo3");

      delay(500);
    }
    else if (keyData == KEY_F4)
    {
      PORTC = 0b00001000;
      servoSelect = 3;

      Serial.println("Servo4");

      delay(500);
    }

    if (keyData == KEY_U)
    {
      delta[servoSelect]++;

      if ( (deg[servoSelect] + delta[servoSelect]) >= 179) delta[servoSelect]--;

      servo[servoSelect].write(deg[servoSelect] + delta[servoSelect]);

      Serial.print(servoSelect);
      Serial.print("\t");
      Serial.println(deg[servoSelect] + delta[servoSelect]);

      delay(20);
    }

    else if (keyData == KEY_D)
    {
      delta[servoSelect]--;

      if ( (deg[servoSelect] + delta[servoSelect]) <= 0) delta[servoSelect]++;

      servo[servoSelect].write(deg[servoSelect] + delta[servoSelect]);


      Serial.print(servoSelect);
      Serial.print("\t");
      Serial.println(deg[servoSelect] + delta[servoSelect]);

      delay(20);
    }
    else if ((keyData == KEY_L) || (keyData == KEY_R))
    {
      Serial.println("Reset Angle");

      for (int j = 0; j < 4; j++)
      {
        delta[j] = 0;
        servo[j].write(deg[j] + delta[j]);

        Serial.print(j);
        Serial.print("\t");
        Serial.println(deg[j] + delta[j]);

        delay(200);
      }
    }

    if (keyData == KEY_C)
    {
      PORTC = 0b11111111;
      delay(200);
      PORTC = 0b00000000;
      delay(200);
      PORTC = 0b11111111;
      delay(200);
      PORTC = 0b00000000;
      delay(200);

      if (servoSelect == 0) PORTC = 0b00000001;       //SmartInventor.LedArray(0b00000001);
      else if (servoSelect == 1) PORTC = 0b00000010;  //SmartInventor.LedArray(0b00000010);
      else if (servoSelect == 2) PORTC = 0b00000100;  //SmartInventor.LedArray(0b00000100);
      else if (servoSelect == 3) PORTC = 0b00001000;  //SmartInventor.LedArray(0b00001000);

      Serial.println("Save Angle");

      for (int j = 10; j < 14; j++)
      {
        int val = deg[j - 10] + delta[j - 10];

        EEPROM.write(j, val);

        Serial.print(j - 10);
        Serial.print("\t");
        /*
        Serial.print( deg[j]);
        Serial.print("\t");
        Serial.print( delta[j]);
        Serial.print("\t");
        */
        Serial.println(val);

      }
      Serial.println();
    }
  }
}
