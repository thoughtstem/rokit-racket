/*
  CLCD.h - CLCD library
  Copyright (C) 2014 RoboLink.  All rights reserved.
*/

#ifndef CLCD_h
#define CLCD_h

#include "Print.h"
//////////////////////////////////////////////////////////////////////////////////

#define RS_1 	ClcdBuffer |=  0x01
#define RS_0 	ClcdBuffer &= ~0x01
#define RW_1 	ClcdBuffer |=  0x02
#define RW_0 	ClcdBuffer &= ~0x02
#define E_1 	ClcdBuffer |=  0x04
#define E_0 	ClcdBuffer &= ~0x04

//////////////////////////////////////////////////////////////////////////////////

#define CLEAR 			0x01 //0b00000001	 // Clear Display_Line1
#define RETURNHOME 		0x02 //0b00000010	 // Clear Display_Line1
#define ENTRYMODESET 		0x04 //0b00000100	 // Clear Display_Line1
#define DISPLAYCONTROL 		0x08 //0b00001000	 // Clear Display_Line1

#define CURSORSHIFT 		0x10 //0b00010000	 // Clear Display_Line1
#define FUNCTIONSET 		0x20 //0b00100000	 // Clear Display_Line1
#define SETCGRAMADDR 		0x40 //0b01000000	 // Clear Display_Line1
#define SETDDRAMADDR 		0x80 //0b10000000	 // Clear Display_Line1

//////////////////////////////////////////////////////////////////////////////////

//for lcd FUNCTIONSET
#define LCD_5x7Dot 		0x00
#define LCD_4x10Dot  		0x04
#define LCD_1lineType		0x00
#define LCD_2lineType		0x08
#define LCD_4bit 		0x00
#define LCD_8bit 		0x10

//for Display control
#define LCD_BLINKON 		0x01
#define LCD_CURSORON 		0x02
#define LCD_DISPLAYON 		0x04

//for lcd entry mode
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00
#define LCD_ENTRYRIGHT 		0x00
#define LCD_ENTRYLEFT 		0x02

// for display/cursor shift
#define MOVERIGHT 		0x04
#define MOVELEFT 		0x00

//for select line
#define LINE1 			0x80 			// first Line
#define LINE2 			0xC0 			// Second Line

/***********************************************************************/

class CLCDClass  : public Print 
{
public:

	void Control(unsigned char command);  	//control command
	void Data(unsigned char command); 	//one byte output

	void begin(int pin1,int pin2,int pin3); //LCD initialize ( si, rck, sck)
	void clearAll(void);
	void clearLine1(void);
	void clearLine2(void);
	
	virtual size_t write(uint8_t);
	
	void setCursor(unsigned char line, unsigned char position);	
	
	void scrollLeft(void);
	void scrollRight(void);

	void display(void);
	void noDisplay(void);
	
	void cursor(void);
	void noCursor(void);

	void blink(void);
	void noBlink(void);

	void autoscroll(void);
	void noAutoscroll(void);

	void makeCharacter(unsigned char location, unsigned char charmap[]);

private:
	int _si;
	int _rck;
	int _sck;

	int EntryBuffer;	//Entry buffer
	int DisplayBuffer;	//Command buffer
	int ClcdBuffer;		//clcd buffer
	void write595(unsigned int data);
	
};

extern CLCDClass CLCD;

#endif 