/*
  RokitFlying.h - RokitFlying library
  Copyright (C) 2014 RoboLink.  All rights reserved.
  
  TIMER2 USE
  TVREMOCON FOLLING
  
*/

#ifndef RokitFlying_h
#define RokitFlying_h
#include "Arduino.h"
#include <avr/interrupt.h>
/***********************************************************************/

//TVRemocon
#define customCodeTVremocon 0b1110000011100000

#define  CH1_KEY_U   0x80
#define  CH1_KEY_D   0x40
#define  CH1_KEY_L   0x20
#define  CH1_KEY_R   0x10
#define  CH1_KEY_C   0xF0
#define  CH1_KEY_F1  0x08
#define  CH1_KEY_F2  0x88
#define  CH1_KEY_F3  0x48
#define  CH1_KEY_F4  0xC8

#define  CH1_KEY_CH1  0x14
#define  CH1_KEY_CH2  0x15
#define  CH1_KEY_CH3  0x16 
#define  CH1_KEY_CH4  0x17

#define  CH2_KEY_U   0x8D
#define  CH2_KEY_D   0x4D
#define  CH2_KEY_L   0x2D
#define  CH2_KEY_R   0x1D
#define  CH2_KEY_C   0xFD
#define  CH2_KEY_F1  0x04
#define  CH2_KEY_F2  0x84
#define  CH2_KEY_F3  0x44
#define  CH2_KEY_F4  0xC4

#define  CH2_KEY_CH1  0xE4
#define  CH2_KEY_CH2  0xE5
#define  CH2_KEY_CH3  0xE6 
#define  CH2_KEY_CH4  0xE7

#define  CH3_KEY_U   0x83
#define  CH3_KEY_D   0x43
#define  CH3_KEY_L   0x23
#define  CH3_KEY_R   0x13
#define  CH3_KEY_C   0xF3
#define  CH3_KEY_F1  0x0C
#define  CH3_KEY_F2  0x8C
#define  CH3_KEY_F3  0x4C
#define  CH3_KEY_F4  0xCC

#define  CH3_KEY_CH1  0x64
#define  CH3_KEY_CH2  0x65
#define  CH3_KEY_CH3  0x66 
#define  CH3_KEY_CH4  0x67

#define  CH4_KEY_U   0x8B
#define  CH4_KEY_D   0x4B
#define  CH4_KEY_L   0x2B
#define  CH4_KEY_R   0x1B
#define  CH4_KEY_C   0xFB
#define  CH4_KEY_F1  0x02
#define  CH4_KEY_F2  0x82
#define  CH4_KEY_F3  0x42
#define  CH4_KEY_F4  0xC2
	
#define  CH4_KEY_CH1  0xA4
#define  CH4_KEY_CH2  0xA5
#define  CH4_KEY_CH3  0xA6 
#define  CH4_KEY_CH4  0xA7

#define  Rf_KEY_UP	0x00
#define  Rf_KEY_U	0x01
#define  Rf_KEY_D	0x02
#define  Rf_KEY_L	0x04
#define  Rf_KEY_R	0x08

#define  Rf_KEY_1	0x10
#define  Rf_KEY_2	0x20
#define  Rf_KEY_3	0x40
#define  Rf_KEY_4	0x80
#define  Rf_KEY_5	0x100
#define  Rf_KEY_6	0x200


#define  Wired_KEY_U	0x01
#define  Wired_KEY_D	0x02
#define  Wired_KEY_L	0x04
#define  Wired_KEY_R	0x08

#define  Wired_KEY_1	0x10
#define  Wired_KEY_2	0x20

	
#define  KEY_U       RokitFlying.Button_up
#define  KEY_D       RokitFlying.Button_down
#define  KEY_L       RokitFlying.Button_left
#define  KEY_R       RokitFlying.Button_right
#define  KEY_C       RokitFlying.Button_center
#define  KEY_F1      RokitFlying.Button_func1
#define  KEY_F2      RokitFlying.Button_func2
#define  KEY_F3      RokitFlying.Button_func3
#define  KEY_F4      RokitFlying.Button_func4
#define  KEY_CH1     RokitFlying.Button_ch1
#define  KEY_CH2     RokitFlying.Button_ch2
#define  KEY_CH3     RokitFlying.Button_ch3
#define  KEY_CH4     RokitFlying.Button_ch4
//zig-100,rokit-rc
#define  KEY_FL      RokitFlying.Button_funcl	
#define  KEY_FR      RokitFlying.Button_funcr
/***********************************************************************/
#define  RFdata	     RokitFlying.RFdataCode


//dc

#define CW		1
#define CCW		2
#define STOP		3
#define LOOSE		4

#define FORWARD		1	
#define BACKWARD	2
#define LEFT 		5
#define RIGHT 		6
#define	LEFT_TURN 	7
#define	RIGHT_TURN	8

#define forward		FORWARD 	
#define backward	BACKWARD	
#define stop		STOP 		
#define loose		LOOSE 		
#define left		LEFT 		
#define right		RIGHT 	

#define left_turn		LEFT_TURN 		
#define right_turn		RIGHT_TURN
	

#define M1	1
#define M2	2
#define M3	3
#define M4	4

#define DC1A_ON 	PORTC |=  0b1000
#define DC1A_OFF 	PORTC &= ~0b1000

#define DC1B_ON 	PORTC |=  0b100
#define DC1B_OFF 	PORTC &= ~0b100

#define DC2A_ON 	PORTB |=  0b1000
#define DC2A_OFF 	PORTB &= ~0b1000

#define DC2B_ON 	PORTB |=  0b10000
#define DC2B_OFF 	PORTB &= ~0b10000

#define DC3A_ON 	PORTC |=  0b10000
#define DC3A_OFF 	PORTC &= ~0b10000

#define DC3B_ON 	PORTC |=  0b100000
#define DC3B_OFF 	PORTC &= ~0b100000

#define DC4A_ON 	PORTB |=  0b1
#define DC4A_OFF 	PORTB &= ~0b1

#define DC4B_ON 	PORTB |=  0b10
#define DC4B_OFF 	PORTB &= ~0b10


// Switch on LED on pin 13 each second 


#define	 LeadCodetime  	8
#define	 TimeChecktime  3000
#define	 EndChecktime  	7
#define	 TimeCheckdatatime  1500

#define  findLeadCode 1
#define  startReadCode 2


/***********************************************************************/

class RokitFlyingClass
{
public:
	//WiredRemocon
	void WiredRemoconUse();
	int WiredRemocon();
	void WiredRemoconClose();
	unsigned char key1;
	unsigned char key3;
	unsigned char key4;
	unsigned char key5;
	unsigned char key6;
	volatile unsigned char remoconUseWired;
		
	//TVRemocon
	void TVRemoconUse();  	//control command
	void TVRemocon();
	int TVRemoconData();
	void RemoconSetChannel();
	
	volatile unsigned char remoconUseTV;
	unsigned char dataCode;
	unsigned char remoconChannel;
			
	unsigned char Button_up;
	unsigned char Button_down;
	unsigned char Button_left;
	unsigned char Button_right;
	unsigned char Button_center;
	unsigned char Button_func1;
	unsigned char Button_func2;
	unsigned char Button_func3;
	unsigned char Button_func4;
	unsigned char Button_ch1;
	unsigned char Button_ch2;
	unsigned char Button_ch3;
	unsigned char Button_ch4;
	
	unsigned char Button_funcl;	
	unsigned char Button_funcr;
	
	void DCMotorUse();
	void DCMove(byte direction, byte speed);
	void DCMotor(char SelectMotor, char direction, char speed);
	void DCControl();
				
	volatile unsigned char dcExUse;		
	volatile unsigned char dcUse;
	volatile unsigned char  DCPWMCount;	
	
	//basic timer
	boolean TimeCheckMicros(word interval); //micros seconds
	boolean TimeCheckMillis(word interval);  //milliseconds
 	unsigned long PreviousMillis;
 	unsigned long PreviousMicros;
 	
 	//adc sensor
	unsigned int SensorCalibration(byte pin);
	
	//led
	void LedPerformance(unsigned char mode, unsigned char time);
	
	//bluetooth
	void RFRemoconUse(long speed);
	int RFRemoconData();
	void RFreceive();
	int RFdataCode;
	volatile unsigned char remoconUseRF;
	
	//off
	void RFRemoconClose();
	void TVRemoconClose();
	void DCMotorClose();
	
	//model util
	byte SpeedDisplay(byte speed, byte state);
	
	
private:
	//TVRemocon
	void CheckLeadCode();
	void CheckCustomCode();
	void CheckDataCode();
	
	boolean TimeCheckCode(word interval); //micros seconds
	boolean TimeCheckLeadcode(word interval);  //milliseconds
	boolean TimeCheckEnd(word interval);  //milliseconds
	boolean TimeOutCheckEnd(word interval);  //milliseconds
	
	unsigned char irPIN;
	unsigned char IR_in;
	
	long CodePreviousMicros;
	long EndPreviousMillis;
	long LeadPreviousMillis; 
	long TimeOutPreviousMillis;

	unsigned char inputStatus;
	unsigned char stateTVReceive;
	unsigned char dataCount;
	unsigned char codeBuffer;
	
	unsigned char ChannelSW1;
	unsigned char ChannelSW2;
	
	//dc	
	unsigned char dcPin1A;
	unsigned char dcPin1B;
	
	unsigned char dcPin2A;
	unsigned char dcPin2B;	
	
	unsigned char dcPin3A;
	unsigned char dcPin3B;
	
	unsigned char dcPin4A;
	unsigned char dcPin4B;
		
	unsigned char dcDirection1;
	unsigned char dcDirection2;
	unsigned char dcDirection3;
	unsigned char dcDirection4;
		
	unsigned char dcSpeed1;
	unsigned char dcSpeed2;
	unsigned char dcSpeed3;
	unsigned char dcSpeed4;
	
	unsigned char StatePinA;
	unsigned char StatePinB;
	unsigned char StatePinC;
	unsigned char StatePinD;

 	/*********************************/
 	 	
 	//bluetooth
 	byte _packet[6];
	byte _count;
	byte _header;
	
	//timer2 set
	void Timer2Set();
	
};

extern RokitFlyingClass RokitFlying;

#endif 