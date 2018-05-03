/*
  SineGait.h - Sinusoidal motion control library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/

#ifndef SineGait_h
#define SineGait_h

#include "Arduino.h"

#define MAX_SINEGAIT_JOINT	8

class SineGait
{
public:
	SineGait(int jointNum);

	void setPeriod(float time);	//unit: sec
	void setJoint(int index, float amplitude, float balance, float phase, float speed);
	float getAngle(int index);
	int getValue(int index, int center, float scale, int dir);
	void start();
	void stop();
	void process();

private:
	float _periodTime;
	int _jointNum;
	boolean _run;
	unsigned long _preMillis;
	float _time[MAX_SINEGAIT_JOINT];
	float _angle[MAX_SINEGAIT_JOINT];
	float _amplitude[MAX_SINEGAIT_JOINT];
	float _balance[MAX_SINEGAIT_JOINT];
	float _phase[MAX_SINEGAIT_JOINT];
	float _speed[MAX_SINEGAIT_JOINT];
};

#endif /*SineGait_h */

