/*
  CLCD.cpp - CLCD library
  Copyright (C) 2014 RoboLink.  All rights reserved.
*/

#include "CLCD.h"
#include "Arduino.h"

 void CLCDClass::write595(unsigned int data)
{
	
  unsigned char i=7;

  digitalWrite(_si, LOW);
  digitalWrite(_sck, LOW);
  digitalWrite(_rck, LOW);
  
  while(i<=7)
  {
    if((data>> i) & 0x01) digitalWrite(_si,HIGH);  
    else digitalWrite(_si, LOW);
    digitalWrite(_sck, HIGH);
    digitalWrite(_sck, LOW);
    i--;
  }
  digitalWrite(_rck, HIGH);
  digitalWrite(_rck, LOW);

}
 
void CLCDClass::Control(unsigned char command) //control command
{
	delay(1);
	write595(RS_0);     // Select Data_bit
	write595(RW_0 );     // Write Mode
	write595(ClcdBuffer = (ClcdBuffer & 0x07) | ((command>>1) & 0x78)); 
	delayMicroseconds(1);
	write595(E_1);      // Enable Signal
	delayMicroseconds(1);
	write595(E_0);     // Disable Signal
	write595(ClcdBuffer = (ClcdBuffer & 0x07)  | ((command & 0x0f)<<3));
	delayMicroseconds(1);
	write595(E_1);      // Enable Signal
	delayMicroseconds(1);
	write595(E_0);     // Disable Signal
	delayMicroseconds(100);
}

void CLCDClass::Data(unsigned char command) //one byte output
{
	delay(1);
	write595(RS_1);     // Select Data_bit
	write595(RW_0);	// Write Mode
	write595(ClcdBuffer = (ClcdBuffer & 0x07) | ((command>> 1) & 0x78)); 
	delayMicroseconds(1);
	write595(E_1);      // Enable Signal
	delayMicroseconds(1);
	write595(E_0 );     // Disable Signal
	write595(ClcdBuffer = (ClcdBuffer & 0x07)  | ((command & 0x0f)<<3));
	delayMicroseconds(1);
	write595(E_1);      // Enable Signal
	delayMicroseconds(1);
	write595(E_0 );     // Disable Signal
	delayMicroseconds(100);
}

void CLCDClass::begin(int pin1 ,int pin2,int pin3) //LCD initialize
{
	_si   = pin1;	//data
	_rck  = pin2;	//latch
	_sck  = pin3;	//shift
	
	pinMode(_si,OUTPUT); 
	pinMode(_rck,OUTPUT); 
	pinMode(_sck,OUTPUT); 
	
	delayMicroseconds(50000); 
	
	digitalWrite(_si, LOW);
	digitalWrite(_rck, LOW);
	digitalWrite(_sck, LOW);
	
	write595(E_0);
	write595(RS_0);
	write595(RW_0);
	
	///////////////////////////
	Control(0x03);
	delayMicroseconds(4500); // wait min 4.1ms
	
	// second try
	Control(0x03);
	delayMicroseconds(4500); // wait min 4.1ms
	
	// third go!
	Control(0x03); 
	delayMicroseconds(150);
	
	// finally, set to 4-bit interface
	Control(0x02); 
	
	///////////////////////////
	
	Control(FUNCTIONSET | LCD_4bit| LCD_2lineType | LCD_5x7Dot );
	delayMicroseconds(40);
	
	DisplayBuffer = DISPLAYCONTROL | LCD_DISPLAYON ;  
	Control(DisplayBuffer);
	delayMicroseconds(40);
	
	Control(CLEAR);
	delayMicroseconds(2000);  // this command takes a long time!
	
	EntryBuffer = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	Control(ENTRYMODESET | EntryBuffer);
	delayMicroseconds(40);
}

void CLCDClass::clearAll(void) //clcd all line clear
{
	Control(CLEAR);
	delayMicroseconds(2000);
}
void CLCDClass::clearLine1(void) //clcd first line clear
{
	Control(LINE1);
	print("                ");
	Control(LINE1);
}
void CLCDClass::clearLine2(void) //clcd second line clear
{
	Control(LINE2);
	print("                ");
	Control(LINE2);
}

void CLCDClass::setCursor(unsigned char line, unsigned char position)
{
	if (line == 2)	line = 0xC0;
	else		line = 0x80;
	Control(line|position);
}

void CLCDClass::scrollLeft(void)	{Control(CURSORSHIFT | DISPLAYCONTROL | MOVELEFT);}
void CLCDClass::scrollRight(void)	{Control(CURSORSHIFT | DISPLAYCONTROL | MOVERIGHT);}


void CLCDClass::display(void) 
{
	DisplayBuffer |= LCD_DISPLAYON;
	Control(DISPLAYCONTROL|DisplayBuffer);
}
void CLCDClass::noDisplay(void) 
{	
	DisplayBuffer &= ~LCD_DISPLAYON;
	Control(DISPLAYCONTROL|DisplayBuffer);
}

void CLCDClass::cursor(void) 
{
	DisplayBuffer |= LCD_CURSORON;
	Control(DISPLAYCONTROL|DisplayBuffer);
	delayMicroseconds(39);
}
void CLCDClass::noCursor(void) 
{
	DisplayBuffer &= ~LCD_CURSORON;
	Control(DISPLAYCONTROL|DisplayBuffer);
	delayMicroseconds(39);
}

void CLCDClass::blink(void)
{
	DisplayBuffer |= LCD_BLINKON;
	Control(DISPLAYCONTROL|DisplayBuffer);
}
void CLCDClass::noBlink(void)
{
	DisplayBuffer &= ~LCD_BLINKON;
	Control(DISPLAYCONTROL|DisplayBuffer);
}

void CLCDClass::autoscroll(void) 
{
	EntryBuffer |= LCD_ENTRYSHIFTINCREMENT;
	Control(ENTRYMODESET|EntryBuffer);
}

void CLCDClass::noAutoscroll(void) 
{
	EntryBuffer  &= ~LCD_ENTRYSHIFTINCREMENT;
	Control(ENTRYMODESET|EntryBuffer);
}

void CLCDClass::makeCharacter(unsigned char location, unsigned char charmap[]) //LCD initialize
{
	location &= 0x7; // we only have 8 locations 0-7
	Control(SETCGRAMADDR | (location << 3));
	for (int i=0; i<8; i++) 
	{
		Data(charmap[i]);	
	}
}

inline size_t CLCDClass::write(uint8_t value) {
	Data(value);
}

CLCDClass CLCD;