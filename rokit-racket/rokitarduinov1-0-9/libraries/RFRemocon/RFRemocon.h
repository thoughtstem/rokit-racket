/*
  RFRemocon.h - RF Remocon library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/

#ifndef RFRemocon_h
#define RFRemocon_h

#include "Arduino.h"


#define KEY_UP	0
#define KEY_U	1
#define KEY_D	2
#define KEY_L	4
#define KEY_R	8
#define KEY_1	16
#define KEY_2	32
#define KEY_3	64
#define KEY_4	128
#define KEY_5	256
#define KEY_6	512


class RFRemoconClass
{
public:
	RFRemoconClass(HardwareSerial *s);

	void attachSerial(HardwareSerial *s);
	void begin(long speed);
	void flush();
	void send(word data);
	int receive();
	
private:
    HardwareSerial* RFRemoconSerial;

	byte _packet[6];
	byte _count;
	byte _header;
};

extern RFRemoconClass RFRemocon;

#endif /*RFRemocon_h */

