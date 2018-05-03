/*
  ServoModule.h - UnityRobot Module library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/

#ifndef ServoModule_h
#define ServoModule_h

#include "Arduino.h"


class ServoModule
{
public:
	ServoModule(int id, int pin, float min, float max);

	void reset();
	void update(int id);
	boolean updated();

	int getPin();
	float getAngle();
	int getValue(int center, float ratio);

private:
	int _id;
	int _pin;
	short _angle;
	short _minAngle;
	short _maxAngle;
	boolean _updated;
};

#endif /*ServoModule_h */

