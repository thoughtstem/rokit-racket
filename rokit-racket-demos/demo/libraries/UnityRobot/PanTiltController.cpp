/*
  WheelController.h - UnityRobot Module library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/


//******************************************************************************
//* Includes
//******************************************************************************
#include "UnityRobot.h"
#include "PanTiltController.h"


//******************************************************************************
//* Constructors
//******************************************************************************

PanTiltController::PanTiltController(int id)
{
	_id = id;
	reset();	
}

//******************************************************************************
//* Public Methods
//******************************************************************************

void PanTiltController::reset()
{
	_panAngle = 0;
	_tiltAngle = 0;
	_updated = false;
}

void PanTiltController::update(int id)
{
	if(id == _id)
	{
		UnityRobot.pop(&_panAngle);
		UnityRobot.pop(&_tiltAngle);
		_updated = true;
	}
}

boolean PanTiltController::updated()
{
	boolean res = _updated;
	_updated = false;
	return res;
}

float PanTiltController::panAngle(float scale, float dir)
{
	return (float)_panAngle * dir * (scale / 1800);
}

float PanTiltController::tiltAngle(float scale, float dir)
{
	return (float)_tiltAngle * dir * (scale / 1800);
}

//******************************************************************************
//* Private Methods
//******************************************************************************
