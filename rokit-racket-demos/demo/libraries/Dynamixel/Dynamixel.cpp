/*
  Dynamixel.cpp - Dynamixel library
  Copyright (C) 2014 RoboLink.  All rights reserved.
*/

//******************************************************************************
//* Includes
//******************************************************************************
#include "Dynamixel.h"
#include "HardwareSerial.h"


#define ID				2
#define LENGTH			3
#define INSTRUCTION		4
#define ERRBIT			4
#define PARAMETER		5


//******************************************************************************
//* Constructors
//******************************************************************************

DynamixelClass::DynamixelClass(HardwareSerial* s) : DynamixelSerial(s)
{
}

//******************************************************************************
//* Public Methods
//******************************************************************************

void DynamixelClass::attachPins(byte dir_pin, byte dir_tx, byte dir_rx)
{
	_dir_pin = dir_pin;
	_dir_tx = dir_tx;
	_dir_rx = dir_rx;
	pinMode(_dir_pin, OUTPUT);
	digitalWrite(_dir_pin, _dir_tx);
}

void DynamixelClass::attachSerial(HardwareSerial* s)
{
	DynamixelSerial = s;
}

long DynamixelClass::baudnumToSpeed(byte baudnum)
{
	float baudrate = 2000000.0f / (float)(baudnum + 1);
	return (long)baudrate;
}

void DynamixelClass::begin(long speed)
{
	DynamixelSerial->begin(speed);
}

void DynamixelClass::beginInstruction(byte id, byte instruction)
{
	_packet[ID] = id;
	_packet[INSTRUCTION] = instruction;
	_paramIndex = PARAMETER;
}

void DynamixelClass::pushParam(byte value)
{
	_packet[_paramIndex++] = value;
}

void DynamixelClass::pushParam(word value)
{
	_packet[_paramIndex++] = (byte)(value & 0xFF);
	_packet[_paramIndex++] = (byte)((value >> 8) & 0xFF);
}

byte DynamixelClass::endInstruction()
{
	word checksum;
	byte id;
	int num;

	// TX packet
	_packet[0] = 0xff;
	_packet[1] = 0xff;
	_packet[LENGTH] = (_paramIndex - PARAMETER) + 2;
	checksum = 0;
	for(int i=0; i<(_packet[LENGTH] + 1); i++)
		checksum += _packet[ID + i];
	_packet[LENGTH + _packet[LENGTH]] = (byte)(~checksum);

	if( (_packet[LENGTH] < 2) || (_packet[LENGTH] > (MAX_LENGTH - 4)) )
		return COMMERROR_LENGTH;
		
	id = _packet[ID];
	_paramIndex = PARAMETER;
	
	// Clear rx buffer
	num = DynamixelSerial->available();
	for(int i=0; i<num; i++)
		DynamixelSerial->read();
	
	for(int i=0; i<(_packet[LENGTH] + 4); i++)
		DynamixelSerial->write(_packet[i]);
	digitalWrite(_dir_pin, _dir_rx);

	// RX packet
	if(id == BROADCAST_ID)
	{
		digitalWrite(_dir_pin, _dir_tx);
		return COMMERROR_NONE;
	}

	num = waitPacket(0, 4);
	if(num == 0)
	{
		digitalWrite(_dir_pin, _dir_tx);
		return COMMERROR_TIMEOUT;
	}
	else if(num < 4)
	{
		digitalWrite(_dir_pin, _dir_tx);
		return COMMERROR_LOST;
	}

	if(_packet[0] != 0xFF || _packet[1] != 0xFF)
	{
		digitalWrite(_dir_pin, _dir_tx);
		return COMMERROR_CORRUPT;
	}

	if(id != _packet[ID])
	{
		digitalWrite(_dir_pin, _dir_tx);
		return COMMERROR_MISMATCH;
	}

	if( (_packet[LENGTH] < 2) || (_packet[LENGTH] > (MAX_LENGTH - 4)) )
	{
		digitalWrite(_dir_pin, _dir_tx);
		return COMMERROR_CORRUPT;
	}

	num = waitPacket(ERRBIT, _packet[LENGTH]);
	digitalWrite(_dir_pin, _dir_tx);
	if(num < _packet[LENGTH])
		return COMMERROR_LOST;

	checksum = 0;
	for(int i=0; i<(_packet[LENGTH] + 1); i++ )
		checksum += _packet[ID + i];
	if( _packet[LENGTH + _packet[LENGTH]] != (byte)(~checksum) )
		return COMMERROR_LENGTH;

	return COMMERROR_NONE;
}

byte DynamixelClass::getError()
{
	return _packet[ERRBIT];
}

void DynamixelClass::popParam(byte* value)
{
	*value = _packet[_paramIndex++];
}

void DynamixelClass::popParam(word* value)
{
	*value = _packet[_paramIndex++];
	*value |= (_packet[_paramIndex++] << 8) & 0xFF00;
}

byte DynamixelClass::write(byte id, byte address, byte value)
{
	beginInstruction(id, INST_WRITE);
	pushParam(address);
	pushParam(value);
	return endInstruction();
}

byte DynamixelClass::write(byte id, byte address, word value)
{
	beginInstruction(id, INST_WRITE);
	pushParam(address);
	pushParam(value);
	return endInstruction();
}

byte DynamixelClass::write(byte id, byte address, byte* values, byte count)
{
	beginInstruction(id, INST_WRITE);
	pushParam(address);
	for(int i=0; i<count; i++)
		pushParam((byte)*(values + i));
	return endInstruction();
}

byte DynamixelClass::read(byte id, byte address, byte* value)
{
	beginInstruction(id, INST_READ);
	pushParam(address);
	pushParam((byte)1);
	byte error = endInstruction();
	if(error != COMMERROR_NONE)
		return error;
	popParam(value);
	return COMMERROR_NONE;
}

byte DynamixelClass::read(byte id, byte address, word* value)
{
	beginInstruction(id, INST_READ);
	pushParam(address);
	pushParam((byte)2);
	byte error = endInstruction();
	if(error != COMMERROR_NONE)
		return error;
	popParam(value);
	return COMMERROR_NONE;
}

byte DynamixelClass::ping(byte id)
{
	beginInstruction(id, INST_PING);
	return endInstruction();
}

byte DynamixelClass::joint(byte id, word pos)
{
	beginInstruction(id, INST_WRITE);
	pushParam((byte)30); // Goal Position address
	pushParam(pos);
	return endInstruction();
}

byte DynamixelClass::joint(byte id, word pos, word speed)
{
	beginInstruction(id, INST_WRITE);
	pushParam((byte)30); // Goal Position address
	pushParam(pos);
	pushParam(speed);
	return endInstruction();
}

byte DynamixelClass::wheel(byte id, short speed)
{
	word binary = 0;
	if(speed < 0)
	{
		speed *= -1;
		binary = 0x400;
	}
	binary |= ((word)speed & 0x3FF);

	beginInstruction(id, INST_WRITE);
	pushParam((byte)32); // Goal Speed address
	pushParam(binary);
	return endInstruction();
}

void DynamixelClass::beginPose(byte type)
{
	beginInstruction(BROADCAST_ID, INST_SYNC_WRITE);
	switch(type)
	{
	case POSE_POS:
		pushParam((byte)30);
		pushParam((byte)2);
		break;

	case POSE_SPEED:
		pushParam((byte)32);
		pushParam((byte)2);
		break;

	case POSE_POS_SPEED:
		pushParam((byte)30);
		pushParam((byte)4);
		break;

	case POSE_SLOPE_POS:
		pushParam((byte)28);
		pushParam((byte)4);
		break;

	case POSE_SLOPE_POS_SPEED:
		pushParam((byte)28);
		pushParam((byte)6);
		break;
	}	
}

void DynamixelClass::addPose(byte id, word pos)
{
	pushParam(id);
	pushParam(pos);
}

void DynamixelClass::addPose(byte id, short speed)
{
	word binary = 0;
	if(speed < 0)
	{
		speed *= -1;
		binary = 0x400;
	}
	binary |= ((word)speed & 0x3FF);

	pushParam(id);
	pushParam(binary);
}

void DynamixelClass::addPose(byte id, word pos, word speed)
{
	pushParam(id);
	pushParam(pos);
	pushParam(speed);
}

void DynamixelClass::addPose(byte id, byte cw_slope, byte ccw_slope, word pos)
{
	pushParam(id);
	pushParam(cw_slope);
	pushParam(ccw_slope);
	pushParam(pos);
}

void DynamixelClass::addPose(byte id, byte cw_slope, byte ccw_slope, word pos, word speed)
{
	pushParam(id);
	pushParam(cw_slope);
	pushParam(ccw_slope);
	pushParam(pos);
	pushParam(speed);
}

byte DynamixelClass::endPose()
{
	return endInstruction();
}


//******************************************************************************
//* Private Methods
//******************************************************************************

byte DynamixelClass::waitPacket(byte index, byte length)
{
	int num;
	byte count = 0;
	unsigned long preTime = millis();
	unsigned long currentTime;

	while(count < length)
	{
		num = DynamixelSerial->available();
		for(int i=0; i<num; i++)
		{
			_packet[index + count] = (byte)DynamixelSerial->read();
			count++;
			if(count == length)
				break;
		}

		if(num > 0)
			preTime = millis();
		else
		{
			currentTime = millis();
			if(currentTime < preTime)
				preTime = millis();
			else if(currentTime - preTime > 2)
				return count; 
		}
	}

	return count;
}

DynamixelClass Dynamixel(&Serial);