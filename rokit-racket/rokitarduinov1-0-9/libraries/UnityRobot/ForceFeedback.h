/*
  ForceFeedback.h - UnityRobot Module library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/

#ifndef ForceFeedback_h
#define ForceFeedback_h

#include "Arduino.h"


class ForceFeedback
{
public:
	ForceFeedback(int id);

	void reset();
	void update(int id);
	boolean updated();
	void flush(short force);

	int getForceLimit(float scale);

private:
	int _id;
	byte _forceLimit;
	boolean _updated;
};

#endif /*ForceFeedback_h */

