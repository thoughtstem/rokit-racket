/*
  MotorModule.h - UnityRobot Module library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/


//******************************************************************************
//* Includes
//******************************************************************************
#include "UnityRobot.h"
#include "MotorModule.h"


//******************************************************************************
//* Constructors
//******************************************************************************

MotorModule::MotorModule(int id)
{	
	_id = id;
	reset();
}

//******************************************************************************
//* Public Methods
//******************************************************************************

void MotorModule::reset()
{
	_speed = 0;
	_updated = false;
}

void MotorModule::update(int id)
{
	if(id == _id)
	{
		UnityRobot.pop(&_speed);
		if(_speed < -100)
			_speed = -100;
		else if(_speed > 100)
			_speed = 100;
		_updated = true;
	}
}

boolean MotorModule::updated()
{
	boolean res = _updated;
	_updated = false;
	return res;
}

float MotorModule::getSpeed(float scale)
{
	return (float)_speed * scale;
}

//******************************************************************************
//* Private Methods
//******************************************************************************

