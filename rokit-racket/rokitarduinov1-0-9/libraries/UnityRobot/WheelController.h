/*
  WheelController.h - UnityRobot Module library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/

#ifndef WheelController_h
#define WheelController_h
#include "Arduino.h"


class WheelController
{
public:
	WheelController(int id);
	
	void reset();
	void update(int id);
	boolean updated();

	float rSpeed(float scale, float dir);
	float lSpeed(float scale, float dir);

private:
	int _id;
	boolean _updated;

	short _rSpeed;
	short _lSpeed;	
};

#endif /*WheelController_h */

