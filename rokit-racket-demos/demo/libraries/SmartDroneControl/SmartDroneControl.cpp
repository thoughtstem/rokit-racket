/*
  SmartDroneControl.cpp - SmartDroneControl library
  Copyright (C) 2014 RoboLink.  All rights reserved.
  LastUpdate : 2015-08-07
*/

#include "SmartDroneControl.h"
#include "Arduino.h"

void SmartDroneControlClass::begin(void)
{
	SendInterval = 100; //millis seconds		
	
	state = READY;	
	analogOffset = 10; // analog sensor offset
	
	SuccessReceive = false;
	
	pinMode(8, INPUT_PULLUP);
	pinMode(9, INPUT_PULLUP);
	pinMode(10, INPUT_PULLUP);
	
	pinMode(11, INPUT);
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);
	pinMode(14, INPUT);
	pinMode(15, INPUT);
	pinMode(16, OUTPUT);
	pinMode(17, OUTPUT);
	pinMode(18, INPUT);
}

void SmartDroneControlClass::Send(void)
{
  byte checkSum = 0x00;
  type = CONTROL;

  //START CODE
  packet[0] = START1;
  packet[1] = START2;

  //header
  packet[2] = type;
  packet[3] = LENGTH;

  //data
  packet[4] = roll;
  packet[5] = pitch;
  packet[6] = yaw;
  packet[7] = throttle;
  packet[8] = event;

  for (int i = 2; i < 9; i++)
  {
    checkSum = checkSum + packet[i];
  }
  packet[9] = checkSum;

  Serial.write(packet, PACKET_LENGTH); //smart
//Serial1.write(packet, PACKET_LENGTH); //ardu-x200
  roll = 0x00;
  pitch = 0x00;
  yaw = 0x00;
  throttle = 0x00;
  event = 0x00;
}


void SmartDroneControlClass::IntervalSend(int interval)
{
    if (TimeCheck(interval))  //delay
    {
      Send();
      PreviousMillis = millis();
    }
}


void SmartDroneControlClass::ButtonPreesHoldWait(int button)
{
  do {
    delay(10);
  }    while (digitalRead(button));
}


void SmartDroneControlClass::ButtonPreesHoldWait(int button1, int button2)
{
  do {
    delay(10);
  }    while (digitalRead(button1) && digitalRead(button2));
}


boolean SmartDroneControlClass::TimeCheck(word interval) //milliseconds
{
  boolean time = false;
  unsigned long currentMillis = millis();
  if (currentMillis - PreviousMillis > interval)
  {
    PreviousMillis = currentMillis;
    time = true;
  }
  return time;
}


boolean SmartDroneControlClass::TimeOutConnetionCheck(word interval) //milliseconds
{
  boolean time = false;
  unsigned long currentMillis = millis();
  if (currentMillis - timeOutConnectionPreviousMillis > interval)
  {
    timeOutConnectionPreviousMillis = currentMillis;
    time = true;
  }
  return time;
}


void SmartDroneControlClass::LED(int command)
{
  if (command == ON)
  {
    digitalWrite(12, HIGH);	
 //   digitalWrite(13, HIGH);    
 //   digitalWrite(16, HIGH);
    digitalWrite(17, HIGH);
  }
  else if (command == OFF)
  {
      digitalWrite(12, LOW);
   //   digitalWrite(13, LOW);      
   //   digitalWrite(16, LOW);
      digitalWrite(17, LOW);
  }
}

void SmartDroneControlClass::Blink(int time, int count)
{
    for (int i = 0; i < count; i++)
    {
   //   digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
      digitalWrite(16, HIGH);
  //    digitalWrite(17, HIGH);    
        
      delay(time);      

   //   digitalWrite(12, LOW);
      digitalWrite(13, LOW);      
      digitalWrite(16, LOW);
   //   digitalWrite(17, LOW);
      
      delay(time);
    }
}

/*
void SmartDroneControlClass::PrintSensor()
{

	int analogValue3 = analogRead(A3);  //throttle
	int analogValue4 = analogRead(A4);  //yaw
	int analogValue5 = analogRead(A5);  //pitch
	int analogValue6 = analogRead(A6);  //roll
	
	THROTTLE  = AnalogScaleChange(analogValue3);
	YAW = AnalogScaleChange(analogValue4);
	PITCH = AnalogScaleChange(analogValue5);
	ROLL = AnalogScaleChange(analogValue6);
	Serial.print(throttle);
	Serial.print("\t");
	Serial.print(yaw);
	Serial.print("\t");
	Serial.print(pitch);
	Serial.print("\t");
	Serial.println(roll);
}

/*********************************************************/
/*
void SmartDroneControlClass::ReadSensor(void)
{
  bt1 = digitalRead(11);
  bt2 = digitalRead(12);
  //  bt3 = digitalRead(13);
  bt4 = digitalRead(14);
  //  bt6 = digitalRead(16);
  bt7 = digitalRead(17);
  bt8 = digitalRead(18);
      
  analogValue0 = analogRead(A0);
  analogValue1 = analogRead(A1);
  analogValue2 = analogRead(A2);
  analogValue3 = analogRead(A3);  //throttle
  analogValue4 = analogRead(A4);  //yaw
  analogValue5 = analogRead(A5);  //pitch
  analogValue6 = analogRead(A6);  //roll
  analogValue7 = analogRead(A7);
}
*/

int SmartDroneControlClass::AnalogScaleChange(int analogValue)
{	
    int ScaleChange = map(analogValue, 0, 1023, -100, 100);
    if ((ScaleChange > -1 * analogOffset) && (ScaleChange < analogOffset)) ScaleChange = 0;        
    return ScaleChange;
}

/*********************************************************/
void SmartDroneControlClass::TrimPitch(int value)
{
	if(value == UP)
	{
		event = TRIM_PITCH_INCREASE;		
	}	
	else if(value == DOWN)
	{
		event = TRIM_PITCH_DECREASE;	
	}
	IntervalSend(SendInterval);
}
void SmartDroneControlClass::TrimYaw(int value)
{
	if(value == UP)
	{
		event = TRIM_YAW_INCREASE;		
	}	
	else if(value == DOWN)
	{
		event = TRIM_YAW_DECREASE;	
	}
	IntervalSend(SendInterval);
}

void SmartDroneControlClass::TrimRoll(int value)
{
	if(value == UP)
	{
		event = TRIM_ROLL_INCREASE;		
	}	
	else if(value == DOWN)
	{
		event = TRIM_ROLL_DECREASE;	
	}	
	IntervalSend(SendInterval);
}
/*********************************************************/

void SmartDroneControlClass::Pairing(void)
{
    event = PAIRING;
    
    IntervalSend(SendInterval);
}

void SmartDroneControlClass::Stop(void)
{
    event = STOP;
    
    IntervalSend(SendInterval);
}

void SmartDroneControlClass::ResetYaw(void)
{
    event = RESET_YAW;
    
    IntervalSend(SendInterval);
}

void SmartDroneControlClass::TrimReset(void)
{
    event = TRIM_RESET;
    
    IntervalSend(SendInterval);
}

void SmartDroneControlClass::MissileFire(void)
{	
    event = MISSILE;
    
    IntervalSend(SendInterval);
}

void SmartDroneControlClass::TeamSelect(byte team)
{	
    event = team;
    
    IntervalSend(SendInterval);
}



void SmartDroneControlClass::Receive(void)
{	
 SuccessReceive = false;
 team = -1;
 flightStatus = -1;
 energy = -1;
 battery = -1;
 missileQuantity  = -1;
        	
  if (Serial.available() > 0)
  {
    int input = Serial.read();
    cmdBuff[cmdIndex++] = (char)input;
    if (cmdIndex >= MAX_CMD_LENGTH)
    {
      checkHeader = 0;
      cmdIndex = 0;
    }
    else
    {
      if (cmdIndex == 2)
      {
        if ((cmdBuff[0] == 0x0A) && (cmdBuff[1] == 0x55))
        {
          checkHeader = 1;
        }
        else
        {
          checkHeader = 0;
          cmdIndex = 0;
        }
      }
      
      if (checkHeader == 1)
      {
        if (cmdIndex == 3)
        {
          if (cmdBuff[2] == 0x21)
          {
            int type = cmdBuff[2];
            checkHeader = 2;
          }
          else
          {
            checkHeader = 0;
            cmdIndex = 0;
          }
        }
      }

      if (checkHeader == 2)
      {
        if (cmdIndex == 4)
        {
          int length = cmdBuff[3];
        }

        else if (cmdIndex == 10)
        {
          int cs = cmdBuff[9];

          byte  checkSum = 0;
          for (int i = 2; i < 9; i++)
          {
            checkSum += cmdBuff[i];
          }
          
          if (cs == checkSum)
          {
            SuccessReceive = true;
            
            team = cmdBuff[4];
            flightStatus = cmdBuff[5];
            energy = cmdBuff[6];
            battery = cmdBuff[7];
            missileQuantity = cmdBuff[8];       
          }
   
          checkHeader = 0;
          cmdIndex = 0;
        }
      }
    }
  }
}





/*********************************************************/

SmartDroneControlClass SmartDroneControl;