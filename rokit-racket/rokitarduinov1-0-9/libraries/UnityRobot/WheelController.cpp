/*
  WheelController.h - UnityRobot Module library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/


//******************************************************************************
//* Includes
//******************************************************************************
#include "UnityRobot.h"
#include "WheelController.h"


//******************************************************************************
//* Constructors
//******************************************************************************

WheelController::WheelController(int id)
{
	_id = id;
	reset();
}

//******************************************************************************
//* Public Methods
//******************************************************************************

void WheelController::reset()
{
	_updated = false;
	_rSpeed = 0;
	_lSpeed = 0;
}

void WheelController::update(int id)
{
	if(id == _id)
	{
		UnityRobot.pop(&_rSpeed);
		UnityRobot.pop(&_lSpeed);
		_updated = true;
	}
}

boolean WheelController::updated()
{
	boolean res = _updated;
	_updated = false;
	return res;
}

float WheelController::rSpeed(float scale, float dir)
{
	return (float)_rSpeed * dir * (scale / 200);
}

float WheelController::lSpeed(float scale, float dir)
{
	return (float)_lSpeed * dir * (scale / 200);
}

//******************************************************************************
//* Private Methods
//******************************************************************************
