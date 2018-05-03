/*
  MotorModule.h - UnityRobot Module library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/

#ifndef MotorModule_h
#define MotorModule_h

#include "Arduino.h"


class MotorModule
{
public:
	MotorModule(int id);

	void reset();
	void update(int id);
	boolean updated();

	float getSpeed(float scale);

private:
	int _id;
	short _speed;
	boolean _updated;
};

#endif /*MotorModule_h */

