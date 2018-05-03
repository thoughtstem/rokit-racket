/*
  SmartDroneControl.h - SmartDroneControl library
  Copyright (C) 2014 RoboLink.  All rights reserved.
  LastUpdate : 2015-08-07
*/

#ifndef SmartDroneControl_h
#define SmartDroneControl_h
#include "Arduino.h"
#include <avr/interrupt.h>

//////////////////////////////////////////////////////////////////////////////////

//START CODE
#define START1          	0x0A
#define START2          	0x55

//HEADER TYPE
#define CONTROL          	0x20
#define STATE            	0x21

#define LENGTH           	0x05

//EVENT
#define  NONE			0x00
#define  MISSILE		0x10
#define  SHIELD			0x11
#define  DEMON			0x12
#define  WATERBOMB		0x13
#define  BOOSTER		0x14
#define  HEADINGLOCK		0x15

#define  TRIM_RESET		0x80
#define  TRIM_PITCH_INCREASE	0x81
#define  TRIM_PITCH_DECREASE	0x82
#define  TRIM_YAW_INCREASE	0x83
#define  TRIM_YAW_DECREASE	0x84
#define  TRIM_ROLL_INCREASE	0x85
#define  TRIM_ROLL_DECREASE	0x86

#define  TAKE_OFF		0xA0
#define  STOP			0xA1  //Landing

#define  GYROBIAS		0xB0
#define  RESET_YAW		0xB1
#define  PAIRING		0xB2

#define  TEAM_RED		0xC0
#define  TEAM_BLUE		0xC1

#define  LEVEL_BEGINNER		0xD0
#define  LEVEL_EXPERT		0xD1

#define  ABSOLUTE		0xE0
#define  RC			0xE1

#define  OFF			0x00
#define  ON			0x01
	
	
#define READY			0x00
#define FLY			0x01
#define TRIM			0x02

#define DOWN                    0x00
#define UP                      0x01


#define PACKET_LENGTH 		10
#define MAX_CMD_LENGTH 		11
/////////////////////////////////////////////

#define ROLL		SmartDroneControl.roll
#define PITCH		SmartDroneControl.pitch
#define YAW		SmartDroneControl.yaw
#define THROTTLE	SmartDroneControl.throttle
#define EVENT		SmartDroneControl.event
#define STATE		SmartDroneControl.state
#define SEND_INTERVAL	SmartDroneControl.SendInterval
#define SUCESS_RECEIVE	SmartDroneControl.SuccessReceive
#define ANALOG_OFFSET	SmartDroneControl.analogOffset

#define Team		SmartDroneControl.team
#define FlightStatus	SmartDroneControl.flightStatus
#define Energy		SmartDroneControl.energy
#define Battery		SmartDroneControl.battery
#define MissileQuantity	SmartDroneControl.missileQuantity

/***********************************************************************/

class SmartDroneControlClass
{
public:

	void begin(void);
	
	void Send(void);	
	void IntervalSend(int interval);
		
	void ButtonPreesHoldWait(int button);
	void ButtonPreesHoldWait(int button1, int button2);
	
	/////////////////////////////////
	void Pairing(void);	
	void ResetYaw(void);
	void Stop(void);	
	void MissileFire(void);
	void TeamSelect(byte team);
	
	void TrimReset(void);	
	void TrimPitch(int value);
	void TrimYaw(int value);
	void TrimRoll(int value);		
	//////////////////////////////////
	void ReadSensor(void);
	void PrintSensor(void);
	int AnalogScaleChange(int analogValue);			
	//////////////////////////////////
	void LED(int command);
	void Blink(int time, int count);	
	boolean TimeCheck(word interval); //milliseconds
	boolean TimeOutConnetionCheck(word interval); //milliseconds	
	//////////////////////////////////
	int roll;
	int pitch;
	int yaw;
	int throttle;
	int event;		
	int type;
	int SendInterval; //millis seconds	
	int state;	
	int analogOffset;
	
	//////////////////////////////////
	void Receive(void);
	byte cmdBuff[MAX_CMD_LENGTH];
	int cmdIndex;
	boolean checkHeader;

	boolean SuccessReceive;
	int team;
	int flightStatus;
	int energy;
	int battery;
	int missileQuantity;

private:
	byte packet[9];
	long PreviousMillis;
	long timeOutConnectionPreviousMillis;
};

extern SmartDroneControlClass SmartDroneControl;

#endif 