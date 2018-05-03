/*
  ToneModule.h - UnityRobot Module library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/


//******************************************************************************
//* Includes
//******************************************************************************
#include "UnityRobot.h"
#include "ToneModule.h"


//******************************************************************************
//* Constructors
//******************************************************************************
ToneModule::ToneModule(int id)
{	
	_id = id;
	reset();
}

//******************************************************************************
//* Public Methods
//******************************************************************************
void ToneModule::attach(callbackToneChanged newFunction)
{
	currentCallbackToneChanged = newFunction;
}

void ToneModule::detach()
{
	currentCallbackToneChanged = NULL;
}

void ToneModule::reset()
{
	_note = NOTE_MUTE;
	_newNote = _note;
	if(currentCallbackToneChanged)
		(*currentCallbackToneChanged)(_id, _note);
}

void ToneModule::update(int id)
{
	if(id == _id)
	{
		UnityRobot.pop(&_newNote);		
	}
}

void ToneModule::action()
{
	if(_note != _newNote)
	{
		_note = _newNote;
		if(currentCallbackToneChanged)
			(*currentCallbackToneChanged)(_id, _note);
	}
}

int ToneModule::getNote()
{	
	return (int)_note;
}

//******************************************************************************
//* Private Methods
//******************************************************************************

