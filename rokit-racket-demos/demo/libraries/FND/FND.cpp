/*
  CLCD.cpp - CLCD library
  Copyright (C) 2014 RoboLink.  All rights reserved.
*/

#include "FND.h"
#include "Arduino.h"

// FND
unsigned char FND_Count = 0;	//fnd 출력 자릿수 컨트롤
unsigned char FND_data[4] = {0,0,0,0};

void FNDClass::write595(unsigned int data)
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

void FNDClass::begin(int pin1,int pin2,int pin3) //LCD initialize
{
	_si   = pin1;	//data
	_rck  = pin2;	//latch
	_sck  = pin3;	//shift
	
	pinMode(_si,OUTPUT); 
	pinMode(_rck,OUTPUT); 
	pinMode(_sck,OUTPUT); 
	
	digitalWrite(_si, LOW);
	digitalWrite(_rck, LOW);
	digitalWrite(_sck, LOW);
}

void FNDClass::setNumber(unsigned int value)
{	
	FND_data[3] =(value/1000);
	FND_data[2] =(value%1000)/100; 
	FND_data[1] =(value%100)/10;
	FND_data[0] =(value%10);
}

void FNDClass::dynamicDisplay(void)
{
	write595((0b00010000 << FND_Count ) | FND_data[FND_Count]);
	FND_Count = FND_Count + 1;
	if (FND_Count == 4) FND_Count = 0;
}

void FNDClass::leftShift()
{	
  char temp = 0;
  temp = FND_data[0];
  FND_data[0] = FND_data[1];
  FND_data[1] = FND_data[2];
  FND_data[2] = FND_data[3]; 
  FND_data[3] = temp;
}

void FNDClass::rightShift()
{	
  char temp = 0;
  temp = FND_data[3];
  FND_data[3] = FND_data[2];
  FND_data[2] = FND_data[1]; 
  FND_data[1] = FND_data[0];
  FND_data[0] = temp;
}

FNDClass FND;