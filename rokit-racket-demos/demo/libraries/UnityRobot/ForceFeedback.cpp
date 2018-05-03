/*
  ForceFeedback.h - UnityRobot Module library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/


//******************************************************************************
//* Includes
//******************************************************************************
#include "UnityRobot.h"
#include "ForceFeedback.h"


//******************************************************************************
//* Constructors
//******************************************************************************

ForceFeedback::ForceFeedback(int id)
{	
	_id = id;
	reset();
}

//******************************************************************************
//* Public Methods
//******************************************************************************

void ForceFeedback::reset()
{
	_updated = false;
	_forceLimit = 100;
}

void ForceFeedback::update(int id)
{
	if(id == _id)
	{
		UnityRobot.pop(&_forceLimit);
		_updated = true;
	}
}

boolean ForceFeedback::updated()
{
	boolean res = _updated;
	_updated = false;
	return res;
}

void ForceFeedback::flush(short force)
{
	UnityRobot.select(_id);
	UnityRobot.push(force);
	UnityRobot.flush();
}

int ForceFeedback::getForceLimit(float scale)
{
	float forceLimit = (float)_forceLimit;
	forceLimit *= scale;
	return (int)forceLimit;
}

//******************************************************************************
//* Private Methods
//******************************************************************************

