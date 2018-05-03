/*
  PWMModule.h - UnityRobot Module library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/


//******************************************************************************
//* Includes
//******************************************************************************
#include "UnityRobot.h"
#include "PWMModule.h"


//******************************************************************************
//* Constructors
//******************************************************************************

PWMModule::PWMModule(int id, int pin)
{
	_id = id;
	_pin = pin;
	_value = 0;
}

//******************************************************************************
//* Public Methods
//******************************************************************************

void PWMModule::begin()
{
	pinMode(_pin, OUTPUT);
	reset();
}

void PWMModule::reset()
{
	_value = 0;
	action();
}

void PWMModule::update(int id)
{
	if(id == _id)
	{
		UnityRobot.pop(&_value);		
	}
}

void PWMModule::action()
{
	analogWrite(_pin, _value);
}

//******************************************************************************
//* Private Methods
//******************************************************************************

