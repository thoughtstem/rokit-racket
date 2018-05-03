/*
  DigitalModule.h - UnityRobot Module library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/

#ifndef DigitalModule_h
#define DigitalModule_h

#include "Arduino.h"


class DigitalModule
{
public:
	DigitalModule(int id, int pin);

	void begin();
	void reset();
	void update(int id);
	void action();
	void flush();

private:
	int _id;
    int _pin;
	byte _mode;
	byte _state;

	void setPinMode();
};

#endif /*DigitalModule_h */

