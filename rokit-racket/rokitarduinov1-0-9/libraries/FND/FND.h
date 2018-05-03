/*
  FND.h - FND library
  Copyright (C) 2014 RoboLink.  All rights reserved.
*/

#ifndef FND_h
#define FND_h

#define RS_1 		Clcd_buf |=  0x01 	//RS_ON  ��> PB0�� ����,set
#define RS_0 		Clcd_buf &= ~0x01 	//RS_OFF ��> PB0�� ����,clear
#define RW_1 		Clcd_buf |=  0x02 	//RW_ON  ��> PB1�� ����,set
#define RW_0 		Clcd_buf &= ~0x02 	//RW_OFF ��> PB1�� ����,clear
#define E_1 		Clcd_buf |=  0x04 	//E_ON   ��> PB2�� ����,set
#define E_0 		Clcd_buf &= ~0x04 	//E_OFF  ��> PB2�� ����,clear


/***********************************************************************/

class FNDClass //: public Print
{
public:

	void begin(int pin1,int pin2,int pin3); 	//FND initialize
	void setNumber(unsigned int value);
	void dynamicDisplay(void);
	void leftShift();
	void rightShift();

private:
	int _si;
	int _rck;
	int _sck;

	unsigned char FND_data[4];
	unsigned char FND_Count;	//fnd ��� �ڸ��� ��Ʈ��
	void write595(unsigned int data);
};


extern FNDClass FND;


#endif 