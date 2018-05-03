/*
  FND.h - FND library
  Copyright (C) 2014 RoboLink.  All rights reserved.
*/

#ifndef FND_h
#define FND_h

#define RS_1 		Clcd_buf |=  0x01 	//RS_ON  ㅡ> PB0에 연결,set
#define RS_0 		Clcd_buf &= ~0x01 	//RS_OFF ㅡ> PB0에 연결,clear
#define RW_1 		Clcd_buf |=  0x02 	//RW_ON  ㅡ> PB1에 연결,set
#define RW_0 		Clcd_buf &= ~0x02 	//RW_OFF ㅡ> PB1에 연결,clear
#define E_1 		Clcd_buf |=  0x04 	//E_ON   ㅡ> PB2에 연결,set
#define E_0 		Clcd_buf &= ~0x04 	//E_OFF  ㅡ> PB2에 연결,clear


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
	unsigned char FND_Count;	//fnd 출력 자릿수 컨트롤
	void write595(unsigned int data);
};


extern FNDClass FND;


#endif 