/*
  Dynamixel.h - Dynamixel library
  Copyright (C) 2014 RoboLink.  All rights reserved.
*/

#ifndef Dynamixel_h
#define Dynamixel_h

#include "Arduino.h"


#define MAX_LENGTH			150
#define BROADCAST_ID		254

#define INST_PING			1
#define INST_READ			2
#define INST_WRITE			3
#define INST_REG_WRITE		4
#define INST_ACTION			5
#define INST_RESET			6
#define INST_SYNC_WRITE		131

#define ERRBIT_VOLTAGE		1
#define ERRBIT_ANGLE		2
#define ERRBIT_OVERHEAT		4
#define ERRBIT_RANGE		8
#define ERRBIT_CHECKSUM		16
#define ERRBIT_OVERLOAD		32
#define ERRBIT_INSTRUCTION	64

#define COMMERROR_NONE			0
#define COMMERROR_LENGTH		1
#define COMMERROR_TIMEOUT		2
#define COMMERROR_LOST			3
#define COMMERROR_CORRUPT		4
#define COMMERROR_MISMATCH		5

#define POSE_POS				0
#define POSE_SPEED				1
#define POSE_POS_SPEED			2
#define POSE_SLOPE_POS			3
#define POSE_SLOPE_POS_SPEED	4


class DynamixelClass
{
public:
	DynamixelClass(HardwareSerial* s);

	void attachPins(byte dir_pin, byte dir_tx, byte dir_rx);
	void attachSerial(HardwareSerial* s);
	long baudnumToSpeed(byte baudnum);
	void begin(long speed);
	void beginInstruction(byte id, byte instruction);
	void pushParam(byte value);
	void pushParam(word value);	
	byte endInstruction();
	byte getError();
	void popParam(byte* value);
	void popParam(word* value);

	byte write(byte id, byte address, byte value);
	byte write(byte id, byte address, word value);
	byte write(byte id, byte address, byte* values, byte count);
	byte read(byte id, byte address, byte* value);
	byte read(byte id, byte address, word* value);

	byte ping(byte id);
	byte joint(byte id, word pos);
	byte joint(byte id, word pos, word speed);
	byte wheel(byte id, short speed);
	void beginPose(byte type);
	void addPose(byte id, word pos);
	void addPose(byte id, short speed);
	void addPose(byte id, word pos, word speed);
	void addPose(byte id, byte cw_slope, byte ccw_slope, word pos);
	void addPose(byte id, byte cw_slope, byte ccw_slope, word pos, word speed);
	byte endPose();

private:
	HardwareSerial* DynamixelSerial;
	unsigned char _packet[MAX_LENGTH];
	byte _dir_pin;
	byte _dir_tx;
	byte _dir_rx;
	byte _paramIndex;
	byte _numRx;

	byte waitPacket(byte index, byte length);
};

extern DynamixelClass Dynamixel;

#endif
