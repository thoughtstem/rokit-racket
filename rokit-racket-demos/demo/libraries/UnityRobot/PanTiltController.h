/*
  PanTiltController.h - UnityRobot Module library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/

#ifndef PanTiltController_h
#define PanTiltController_h
#include "Arduino.h"


class PanTiltController
{
public:
	PanTiltController(int id);
	
	void reset();
	void update(int id);
	boolean updated();

	float panAngle(float scale, float dir);
	float tiltAngle(float scale, float dir);

private:
	int _id;
	boolean _updated;

	short _panAngle;
	short _tiltAngle;	
};

#endif /*PanTiltController_h */

