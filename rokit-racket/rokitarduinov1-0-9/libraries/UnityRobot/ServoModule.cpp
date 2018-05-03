/*
  ServoModule.h - UnityRobot Module library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/


//******************************************************************************
//* Includes
//******************************************************************************
#include "UnityRobot.h"
#include "ServoModule.h"


//******************************************************************************
//* Constructors
//******************************************************************************

ServoModule::ServoModule(int id, int pin, float min, float max)
{	
	_id = id;
	_pin = pin;
	_minAngle = (short)(min * 10);
	_maxAngle = (short)(max * 10);
}

//******************************************************************************
//* Public Methods
//******************************************************************************

void ServoModule::reset()
{
	_updated = false;
	_angle = 0;
}

void ServoModule::update(int id)
{
	if(id == _id)
	{
		UnityRobot.pop(&_angle);
		if(_angle < _minAngle)
			_angle = _minAngle;
		else if(_angle > _maxAngle)
			_angle = _maxAngle;
		_updated = true;
	}
}

boolean ServoModule::updated()
{
	boolean res = _updated;
	_updated = false;
	return res;
}

int ServoModule::getPin()
{	
	return _pin;
}

float ServoModule::getAngle()
{	
	return (float)_angle / 10;
}

int ServoModule::getValue(int center, float ratio)
{
	float offset = (float)_angle / 10 * ratio;
	return center + (int)offset;
}

//******************************************************************************
//* Private Methods
//******************************************************************************

