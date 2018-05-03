/*****************************
//Servo AngleTuner Example
//2015-06-04 RoboLink
******************************/
#include <EEPROM.h>
#include <SmartInventor.h>
#include<Servo.h>
  
#define SERVO_ORIGIN  90

Servo servo[4];

int deg[4] = {SERVO_ORIGIN, SERVO_ORIGIN, SERVO_ORIGIN, SERVO_ORIGIN};
int delta[4] = {0,0,0,0};
int servoSelect = 0;

void setup()
{
    servo[0].attach(27);
    servo[1].attach(28);
    servo[2].attach(29);
    servo[3].attach(30);
  
    servo[0].write(deg[0]);
    servo[1].write(deg[1]);
    servo[2].write(deg[2]);
    servo[3].write(deg[3]);
    SmartInventor.TVRemoconUse();
    SmartInventor.LedArray(0b00000001);
   // Serial.begin(9600);
}

void loop()
{
  int keyData = SmartInventor.TVRemoconData();
  
  if(keyData == KEY_F1)
  {
      SmartInventor.LedArray(0b00000001);
      servoSelect = 0;
      delay(500);   
  }
  else if(keyData == KEY_F2)
  {
      SmartInventor.LedArray(0b00000010);
      servoSelect = 1;
      delay(500); 
  }
  else if(keyData == KEY_F3)
  {
      SmartInventor.LedArray(0b00000100);
      servoSelect = 2; 
      delay(500);
  }
  else if(keyData == KEY_F4)
  {
      SmartInventor.LedArray(0b00001000);
      servoSelect = 3; 
      delay(500);
  }
  
  if(keyData == KEY_U)
   {
     delta[servoSelect]++;
     if( (deg[servoSelect] + delta[servoSelect]) >= 179) delta[servoSelect]--;
     servo[servoSelect].write(deg[servoSelect] + delta[servoSelect]);
     delay(20);     
   }
   else if(keyData == KEY_D)
   {
     delta[servoSelect]--;
     if( (deg[servoSelect] + delta[servoSelect]) <= 0) delta[servoSelect]++;
     servo[servoSelect].write(deg[servoSelect] + delta[servoSelect]);
     delay(20);     
   }
   else if((keyData == KEY_L)||(keyData == KEY_R))
   {     
      for(int j = 0; j < 4; j++)
      {
        delta[j] = 0;
        servo[j].write(deg[j] + delta[j]);
      }          
   }
     
   if(keyData == KEY_C)
   {
      SmartInventor.LedArray(0b11111111);
      delay(200);
      SmartInventor.LedArray(0b00000000);
      delay(200);
      SmartInventor.LedArray(0b11111111);
      delay(200);
      SmartInventor.LedArray(0b00000000);
      delay(200);
      
      if(servoSelect == 0) SmartInventor.LedArray(0b00000001);
      else if(servoSelect == 1) SmartInventor.LedArray(0b00000010);
      else if(servoSelect == 2) SmartInventor.LedArray(0b00000100);
      else if(servoSelect == 3) SmartInventor.LedArray(0b00001000);
     
      for(int j = 0; j < 4; j++)
      {
         int val = deg[j] + delta[j]; 
         EEPROM.write(j,val);
       //  Serial.print(val);
        // Serial.print(" ");
      }
     // Serial.println("");
   }  
}

