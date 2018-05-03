/*
  PWMModule.h - UnityRobot Module library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/

#ifndef PWMModule_h
#define PWMModule_h

#include "Arduino.h"


class PWMModule
{
public:
	PWMModule(int id, int pin);

	void begin();
	void reset();
	void update(int id);
	void action();

private:
	int _id;
	int _pin;
	byte _value;
};

#endif /*PWMModule_h */

