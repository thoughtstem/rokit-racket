/*
  RokitFlying.cpp - RokitFlying library
  Copyright (C) 2014 RoboLink.  All rights reserved.
*/

#include "RokitFlying.h"
//#include "Arduino.h"


void RokitFlyingClass::WiredRemoconUse() //control command
{
	
  key1 = 27; 
  key3 = 28; 
  key4 = 30;
  key5 = 31;
  key6 = 29; 

  pinMode(key1, INPUT_PULLUP);
  pinMode(key3, INPUT_PULLUP);
  pinMode(key4, INPUT_PULLUP);
  pinMode(key5, INPUT_PULLUP);
  pinMode(key6, OUTPUT);

  digitalWrite(key6, LOW);
  
  remoconUseWired = true;
}

int RokitFlyingClass::WiredRemocon() //control command
{	
	int sensorVal = 0;
	int sensorVal1 = 0;
	int sensorVal2 = 0;
	int sensorVal3 = 0;
	
	if (digitalRead(key1) == LOW)     sensorVal = 0x01;
	if (digitalRead(key3) == LOW)     sensorVal1 = 0x02;	
	if (digitalRead(key4) == LOW)
	{
		digitalWrite(key6, HIGH);
		
		if (digitalRead(key4) == LOW)   sensorVal2 = 0x20;
		else                            sensorVal2 = 0x04;
		
		digitalWrite(key6, LOW);
	}
	
	if (digitalRead(key5) == LOW)
	{
		digitalWrite(key6, HIGH);
		
		if (digitalRead(key5) == LOW)   sensorVal3 = 0x10;
		else                            sensorVal3 = 0x08;
		
		digitalWrite(key6, LOW);
	}
	
	RokitFlying.RemoconSetChannel(); 
	return (sensorVal + sensorVal1 + sensorVal2 + sensorVal3);
}

void RokitFlyingClass::WiredRemoconClose() //control command
{	
	remoconUseWired = false;
}


void RokitFlyingClass::TVRemoconUse() //control command
{
	remoconUseTV = 1;
		
	irPIN = 26;
	ChannelSW1 = 4;
	ChannelSW2 = 5;

	//64분주 - 100us 타이머
	//ir receiver
	pinMode(irPIN, INPUT);
	//DDRB &= ~0b10000;
	
	//dip sw - id set
	pinMode(ChannelSW1, INPUT);
	pinMode(ChannelSW2, INPUT);
	//DDRB  &= ~1100000;
	//PORTB |=  1100000;
			  
	Timer2Set();
}





void RokitFlyingClass::TVRemoconClose() //control command
{
	remoconUseTV = 0;
	if(dcUse == 0 || remoconUseTV == 0 || remoconUseRF == 0) TIMSK |= (0<<TOIE2);  
}
int RokitFlyingClass::TVRemoconData()
{
	RokitFlying.RemoconSetChannel(); 
	return dataCode;
}

void RokitFlyingClass::RemoconSetChannel()
{	
	remoconChannel  = digitalRead(ChannelSW1);
	remoconChannel |= (digitalRead(ChannelSW2)<<1);
	remoconChannel = 0b11 - remoconChannel;
	
//	remoconChannel = (((~PINB) >> 5) & 0b011);
	
	if((remoconUseRF == 1) && (RFdataCode != 0))
	{
	  	Button_up = Rf_KEY_U;
		Button_down = Rf_KEY_D;
		Button_left = Rf_KEY_L;
		Button_right= Rf_KEY_R;
//		Button_center = 512;
		Button_func1 = Rf_KEY_1;
		Button_func2 = Rf_KEY_2;
		Button_func3 = Rf_KEY_3;
		Button_func4 = Rf_KEY_4;
		Button_funcr = Rf_KEY_5;
		Button_funcl = Rf_KEY_6;
	}
		
	else if(remoconUseWired == 1)
	{
	  	Button_up = Wired_KEY_U;
		Button_down = Wired_KEY_D;
		Button_left = Wired_KEY_L;
		Button_right= Wired_KEY_R;
		Button_func1 = Wired_KEY_1;
		Button_func2 = Wired_KEY_2;
	}		
		
	//ch1
	else if(remoconChannel == 0b00)
	{
	  	Button_up = CH1_KEY_U;
		Button_down = CH1_KEY_D;
		Button_left = CH1_KEY_L;
		Button_right= CH1_KEY_R;
		Button_center = CH1_KEY_C;
		Button_func1 = CH1_KEY_F1;
		Button_func2 = CH1_KEY_F2;
		Button_func3 = CH1_KEY_F3;
		Button_func4 = CH1_KEY_F4;
		Button_ch1 = CH1_KEY_CH1;
		Button_ch2 = CH1_KEY_CH2;
		Button_ch3 = CH1_KEY_CH3;
		Button_ch4 = CH1_KEY_CH4;
	}
	
	//ch2
	else if(remoconChannel == 0b01)
	{
	  	Button_up = CH2_KEY_U;
		Button_down = CH2_KEY_D;
		Button_left = CH2_KEY_L;
		Button_right= CH2_KEY_R;
		Button_center = CH2_KEY_C;
		Button_func1 = CH2_KEY_F1;
		Button_func2 = CH2_KEY_F2;
		Button_func3 = CH2_KEY_F3;
		Button_func4 = CH2_KEY_F4;
		Button_ch1 = CH2_KEY_CH1;
		Button_ch2 = CH2_KEY_CH2;
		Button_ch3 = CH2_KEY_CH3;
		Button_ch4 = CH2_KEY_CH4;
	}
	
	//ch3
	else if(remoconChannel == 0b10)
	{
	  	Button_up = CH3_KEY_U;
		Button_down = CH3_KEY_D;
		Button_left = CH3_KEY_L;
		Button_right= CH3_KEY_R;
		Button_center = CH3_KEY_C;
		Button_func1 = CH3_KEY_F1;
		Button_func2 = CH3_KEY_F2;
		Button_func3 = CH3_KEY_F3;
		Button_func4 = CH3_KEY_F4;
		Button_ch1 = CH3_KEY_CH1;
		Button_ch2 = CH3_KEY_CH2;
		Button_ch3 = CH3_KEY_CH3;
		Button_ch4 = CH3_KEY_CH4;
	}
	
	//ch4
	else if(remoconChannel == 0b11)
	{
	  	Button_up = CH4_KEY_U;
		Button_down = CH4_KEY_D;
		Button_left = CH4_KEY_L;
		Button_right= CH4_KEY_R;
		Button_center = CH4_KEY_C;
		Button_func1 = CH4_KEY_F1;
		Button_func2 = CH4_KEY_F2;
		Button_func3 = CH4_KEY_F3;
		Button_func4 = CH4_KEY_F4;
		Button_ch1 = CH4_KEY_CH1;
		Button_ch2 = CH4_KEY_CH2;
		Button_ch3 = CH4_KEY_CH3;
		Button_ch4 = CH4_KEY_CH4;
	}
}

void RokitFlyingClass::TVRemocon()
{
 if (TimeOutCheckEnd(150))
   {
	   dataCode = 0;
	   codeBuffer = 0;
	   dataCount = 0;
	   stateTVReceive = 0;
   }

 // IR_in = !(((~PIND) >> 2) & 0b1); 
  IR_in = digitalRead(irPIN);

  if(stateTVReceive == startReadCode)	  	//3step - DataCode check
  {  
    CheckDataCode();
  }
  
  else if(stateTVReceive == findLeadCode)	//2step - CustomCodeStart
  {
    CheckCustomCode();
  }
  
  else if(stateTVReceive == 0)	  		//1step - Lead code check
  {
    CheckLeadCode();
  }  
}

void RokitFlyingClass::CheckLeadCode()
{
  if(!inputStatus)
  {
    if(IR_in == LOW)
    {
      inputStatus = 1;
      LeadPreviousMillis = millis();
    }
  }
  else
  {
    if(IR_in == HIGH)
    {
      inputStatus = 0;
      if(TimeCheckLeadcode(LeadCodetime))
      {
    	stateTVReceive = findLeadCode;    
        CodePreviousMicros = micros();
      }
    }
  }
}

/////////////////////////////////////////////////////////////////////
void RokitFlyingClass::CheckCustomCode()
{
  if(IR_in == LOW)
  {
    if(TimeCheckCode(TimeChecktime))
    {
      stateTVReceive = startReadCode;
      CodePreviousMicros = micros();
      EndPreviousMillis = millis();
      inputStatus = 1;
    }
    else
    {
    	stateTVReceive = 0;
    }
  }
}
/////////////////////////////////////////////////////////////////////
void RokitFlyingClass::CheckDataCode()
{
  if(TimeCheckEnd(EndChecktime))
  {
    TimeOutPreviousMillis = millis();
    codeBuffer = 0;
    dataCount = 0;
    stateTVReceive = 0;
  }
    
  else if(inputStatus)
  {
    if(IR_in == HIGH)
    {
      CodePreviousMicros = micros();
      EndPreviousMillis = millis();
      inputStatus = 0;
    }
  }
  
  else	//!inputStatus
  {
      if(IR_in == LOW)
      { 
	if(dataCount > 15 && dataCount < 24)
	{
		codeBuffer = codeBuffer << 1;
		
	        if(TimeCheckCode(TimeCheckdatatime))	
	        {
	        	codeBuffer |= 0x01;	//data 1
		}
	        else	
	        {
	       		codeBuffer &= ~0x01;	//data 0
		}
	}
	
        dataCount++;
        inputStatus = 1;
        
        if (dataCount == 24) 
        {
        	dataCode = codeBuffer;
        }        
     }
  }
}

/////////////////////////////////////////////////////////////////////

boolean RokitFlyingClass::TimeCheckCode(word interval) //micros seconds
{
  boolean time = false; 
  unsigned long currentTimes = micros();
  if(currentTimes - CodePreviousMicros > interval) 
  {
    CodePreviousMicros = currentTimes;
    time = true;
  }
  return time;
}

boolean RokitFlyingClass::TimeCheckLeadcode(word interval)  //milliseconds
{
  boolean time = false; 
  unsigned long currentTimes = millis();
  if(currentTimes - LeadPreviousMillis > interval) 
  {
    LeadPreviousMillis = currentTimes;
    time = true;
  }
  return time;
}

boolean RokitFlyingClass::TimeCheckEnd(word interval)  //milliseconds
{
  boolean time = false; 
  unsigned long currentTimes = millis();
  if(currentTimes - EndPreviousMillis > interval) 
  {
    EndPreviousMillis = currentTimes;
    time = true;
  }
  return time;
}

boolean RokitFlyingClass::TimeOutCheckEnd(word interval)  //milliseconds
{
  boolean time = false; 
  unsigned long currentTimes = millis();
  if(currentTimes - TimeOutPreviousMillis > interval) 
  {
    TimeOutPreviousMillis = currentTimes;
    time = true;
  }
  return time;
}

ISR(TIMER2_OVF_vect)
{
 TCNT2 = 0xE7;
 if(RokitFlying.remoconUseTV == 1)	RokitFlying.TVRemocon();
 if(RokitFlying.dcUse == 1)  		RokitFlying.DCControl(); 
 if(RokitFlying.remoconUseRF == 1)	RokitFlying.RFreceive(); 
RokitFlying.DCPWMCount++;
 if(RokitFlying.DCPWMCount >= 100) {RokitFlying.DCPWMCount = 0;}
}

/////////////////////////////////////////////////////
//dc
void RokitFlyingClass::DCMove(byte direction, byte speed)
{
	if(direction == forward)
	{
		RokitFlying.DCMotor(M1,CCW,speed);
		RokitFlying.DCMotor(M2,CW,speed); 
		RokitFlying.DCMotor(M3,CCW,speed);
		RokitFlying.DCMotor(M4,CW,speed); 
	}
	else if(direction == backward)
	{
		RokitFlying.DCMotor(M1,CW,speed);
		RokitFlying.DCMotor(M2,CCW,speed); 
		RokitFlying.DCMotor(M3,CW,speed);
		RokitFlying.DCMotor(M4,CCW,speed);		
	}
	else if(direction == left_turn)
	{
		RokitFlying.DCMotor(M1,CW,speed);
		RokitFlying.DCMotor(M2,CW,speed); 
		RokitFlying.DCMotor(M3,CW,speed);
		RokitFlying.DCMotor(M4,CW,speed); 
	}
	else if(direction == right_turn)
	{
		RokitFlying.DCMotor(M1,CCW,speed);
		RokitFlying.DCMotor(M2,CCW,speed); 
		RokitFlying.DCMotor(M3,CCW,speed);
		RokitFlying.DCMotor(M4,CCW,speed); 
	}
	
	
	else if(direction == left)
	{
		RokitFlying.DCMotor(M1,STOP,speed);
		RokitFlying.DCMotor(M2,CW,speed); 
		RokitFlying.DCMotor(M3,STOP,speed);
		RokitFlying.DCMotor(M4,CW,speed); 
	}
	else if(direction == right)
	{
		RokitFlying.DCMotor(M1,CCW,speed);
		RokitFlying.DCMotor(M2,STOP,speed); 
		RokitFlying.DCMotor(M3,CCW,speed);
		RokitFlying.DCMotor(M4,STOP,speed); 
	}
		
	else if(direction == stop)
	{
		RokitFlying.DCMotor(M1,STOP,0);
		RokitFlying.DCMotor(M2,STOP,0); 
		RokitFlying.DCMotor(M3,STOP,0);
		RokitFlying.DCMotor(M4,STOP,0); 	
		
	}
	else if(direction == loose)
	{
		RokitFlying.DCMotor(M1,LOOSE,0);
		RokitFlying.DCMotor(M2,LOOSE,0); 
		RokitFlying.DCMotor(M3,LOOSE,0);
		RokitFlying.DCMotor(M4,LOOSE,0); 
	}
}



void RokitFlyingClass::DCControl()
{
	//M1	
	if((dcDirection1 == STOP) || (dcDirection1 == LOOSE))
	{
		if(dcDirection1 == STOP)	//STop	
		{
			//PORTB |= 0b11;
			DC1A_ON;
			DC1B_ON;
		}
		else				//loose
		{
			//PORTB &=~ 0b11;
			DC1A_OFF;
			DC1B_OFF;
		}
	}
	else
	{	if(DCPWMCount <= dcSpeed1 )
		{
			if(StatePinA == HIGH)
			{
				
				//PORTB |= 0b01;
				DC1A_ON;
				DC1B_OFF;
				
			}
			else
			{				
				//PORTB |= 0b10;
				DC1A_OFF;
				DC1B_ON;
				
			}			
		}
		else
		{
			//PORTB &=~ 0b11;
			DC1A_OFF;
			DC1B_OFF;
		}
	}
	
	//M2	
	if((dcDirection2 == STOP) || (dcDirection2 == LOOSE))
	{
		if(dcDirection2 == STOP)	//STop		
		{
			//PORTB |= 0b1100;
			DC2A_ON;
			DC2B_ON;
		}
		else 				//loose
		{
			//PORTB &=~0b1100;
			DC2A_OFF;
			DC2B_OFF;
		}
	}
	else
	{
		if(DCPWMCount <= dcSpeed2 )
		{				
			if(StatePinB == HIGH)
			{
				//PORTB |= 0b0100;
				DC2A_ON;
				DC2B_OFF;
			}
			else
			{
				//PORTB |= 0b1000;
				DC2A_OFF;
				DC2B_ON;
			}				
		}
		else
		{
			//PORTB &=~0b1100;
			DC2A_OFF;
			DC2B_OFF;
		}
	}
		
	if((dcDirection3 == STOP) || (dcDirection3 == LOOSE))
	{
		if(dcDirection3 == STOP)	
		{
			//PORTD |= 0b11000;
			DC3A_ON;
			DC3B_ON;
		}
		else
		{
			//PORTD &=~0b11000;
			DC3A_OFF;
			DC3B_OFF;
		}
	}
	else
	{
		if(DCPWMCount <= dcSpeed3 )
		{				
			if(StatePinC == HIGH)
			{
				//PORTD |=0b01000;
				DC3A_ON;
				DC3B_OFF;
			}
			else
			{
				//PORTD |=0b10000;
				DC3A_OFF;
				DC3B_ON;
			}				
		}
		else
		{
			//PORTD &=~0b11000;
			DC3A_OFF;
			DC3B_OFF;
		}
	}		
	
	
	if((dcDirection4 == STOP) || (dcDirection4 == LOOSE))
	{
		if(dcDirection4 == STOP)	
		{
			//PORTD |= 0b1100000;
			DC4A_ON;
			DC4B_ON;
			
		}
		else
		{
			//PORTD &=~0b1100000;
			DC4A_OFF;
			DC4B_OFF;
		}
	}
	else
	{
		if(DCPWMCount <= dcSpeed4 )
		{				
			if(StatePinD == HIGH)
			{
				//PORTD |=0b1000000;
				DC4A_ON;
				DC4B_OFF;
			}
			else
			{
				//PORTD |=0b0100000;
				DC4A_OFF;
				DC4B_ON;
			}				
		}
		else
		{
			//PORTD &=~0b1100000;
			DC4A_OFF;
			DC4B_OFF;
		}
	}
	
}


void RokitFlyingClass::DCMotorUse()
{
	dcUse = 1;
						
	dcPin1A = 18;
	dcPin1B = 19;
	
	dcPin2A = 20;
	dcPin2B = 21;
	
	dcPin3A = 22;
	dcPin3B = 23;
	
	dcPin4A = 24;
	dcPin4B = 25;
				
	pinMode(dcPin1A, OUTPUT);
	pinMode(dcPin1B, OUTPUT);
	
	pinMode(dcPin2A, OUTPUT);
	pinMode(dcPin2B, OUTPUT);
	
	pinMode(dcPin3A, OUTPUT);
	pinMode(dcPin3B, OUTPUT);
	
	pinMode(dcPin4A, OUTPUT);
	pinMode(dcPin4B, OUTPUT);
	
	/*
	digitalWrite(dcPin1A,LOW);
	digitalWrite(dcPin1B,LOW);
	
	digitalWrite(dcPin2A,LOW);
	digitalWrite(dcPin2B,LOW);
		
	digitalWrite(dcPin3A,LOW);
	digitalWrite(dcPin3B,LOW);
	
	digitalWrite(dcPin4A,LOW);
	digitalWrite(dcPin4B,LOW);
	
	*/
	//DDRB |= 0b1111;
		
	Timer2Set();
}
void RokitFlyingClass::DCMotorClose()
{
	//PORTB &=~0b1100;
	//PORTB &=~0b11;
	
	digitalWrite(dcPin1A,LOW);
	digitalWrite(dcPin1B,LOW);
	
	digitalWrite(dcPin2A,LOW);
	digitalWrite(dcPin2B,LOW);
		
	digitalWrite(dcPin3A,LOW);
	digitalWrite(dcPin3B,LOW);
	
	digitalWrite(dcPin4A,LOW);
	digitalWrite(dcPin4B,LOW);
	
	dcUse = 0;	
	
	if(dcUse == 0 || remoconUseTV == 0 || remoconUseRF == 0) TIMSK |= (0<<TOIE2);  
	 
}
void RokitFlyingClass::DCMotor(char SelectMotor, char direction, char speed)
{
	if (SelectMotor == M1)
	{
		dcDirection1 = direction;
		dcSpeed1 = speed;
		
		if(direction == CW)
		{
			StatePinA = HIGH;
		}
		else if(direction == CCW)
		{
			StatePinA = LOW;
		}
	}
	
	else if (SelectMotor == M2)
	{
		dcDirection2 = direction;
		dcSpeed2 = speed;
		
		if(direction == CW)
		{
			StatePinB = HIGH;
		}
		else if(direction == CCW)
		{
			StatePinB = LOW;
		}
	}	
	
	else if (SelectMotor == M3)
	{
		dcDirection3 = direction;
		dcSpeed3 = speed;
		
		if(direction == CW)
		{
			StatePinC = HIGH;
		}
		else if(direction == CCW)
		{
			StatePinC = LOW;
		}
	}
	
	else if (SelectMotor == M4)
	{
		dcDirection4 = direction;
		dcSpeed4 = speed;
		
		if(direction == CW)
		{
			StatePinD = HIGH;
		}
		else if(direction == CCW)
		{
			StatePinD = LOW;
		}
	}
}

/////////////////////////////////////
//basic milli ,micro timer;

boolean RokitFlyingClass::TimeCheckMillis(word interval)  //milliseconds
{
  boolean time = false; 
  unsigned long currentTimes = millis();
  if(currentTimes - PreviousMillis >= interval) 
  {
    PreviousMillis = currentTimes;
    time = true;
  }
  return time;
}

boolean RokitFlyingClass::TimeCheckMicros(word interval) //micros seconds
{
  boolean time = false; 
  unsigned long currentTimes = micros();
  if(currentTimes - PreviousMicros >= interval) 
  {
    PreviousMicros = currentTimes;
    time = true;
  }
  return time;
}

/////////////////////////////////////
//led preformance
void RokitFlyingClass::LedPerformance(unsigned char mode, unsigned char time)
{	
  byte displayLed[] = {13, 14, 15, 16, 17};
  
  for (int i = 0; i <= 4 ; i++)
  {
    pinMode(displayLed[i], OUTPUT);
    digitalWrite(displayLed[i], LOW);
  }

  if(mode == 0)
  {
	for (int i = 0; i <= 4 ; i++)
	{
	digitalWrite(displayLed[i], HIGH);
	delay(time);
	}
	for (int i = 0; i <= 4 ; i++)
	{
	digitalWrite(displayLed[i], LOW);
	delay(time);
	}
   }
   
  else if(mode == 1)
  {
    for (int i = 0; i <= 2 ; i++)
    {
      digitalWrite(displayLed[i], HIGH);
      digitalWrite(displayLed[4 - i], HIGH);
      delay(time);
    }

    for (int i = 2; i >= 0 ; i--)
    {
      digitalWrite(displayLed[i], LOW);
      digitalWrite(displayLed[4 - i], LOW);
      delay(time);
    }
  }
   
   
   
}

//Bluetooth
void RokitFlyingClass::RFRemoconUse(long speed)
{
	remoconUseRF = 1;
	_count = 0;
	Serial.begin(speed);
	Timer2Set();
}


void RokitFlyingClass::RFRemoconClose()
{
	remoconUseRF = 0;	
	if(dcUse == 0 || remoconUseTV == 0 || remoconUseRF == 0) TIMSK |= (0<<TOIE2);  
}


void RokitFlyingClass::RFreceive()
{
	word data = 0xFFFF;
	int num = Serial.available();	
	
	for(int i=0; i<num; i++)
	{		
		int input = Serial.read();	 // this is 'int' to handle -1 when no data		
	
		if(input >= 0)
		{
			_packet[_count++] = (byte)input;
			
			if(_count > 6)
			{
				_header = 0;
				_count = 0;
			}
			
			else 
			{
				if(_count == 2)
				{
					if(_packet[0] == 0xFF && _packet[1] == 0x55)
					{
						_header = 1;
					}	
				}
				
			}
						
			if(_header == 1)
			{	
				if(_count == 6)
				{
					_header = 0;
					_count = 0;
								
					if(_packet[2] == (byte)(~_packet[3]) && _packet[4] == (byte)(~_packet[5]))
					{
						data = _packet[2];
						data |= (_packet[4] << 8) & 0xFF00;
					}
				}
			}
		}
	}

	if(data == 0xFFFF)	RFdataCode -1;
	else			RFdataCode = data;	
}

int RokitFlyingClass::RFRemoconData()
{
	RokitFlying.RemoconSetChannel(); 
	return RFdataCode;
}


void RokitFlyingClass::Timer2Set()
{
	//timer2 set
	TIMSK &= ~(1<<TOIE2);    
	TCCR2 &= ~((1<<WGM21) | (1<<WGM20));  
	ASSR &= ~(1<<AS2);
	TIMSK &= ~(1<<OCIE2);
	//64 - 100us
	TCCR2 |= (1<<CS22);                                  
	TCCR2 &= ~((1<<CS21) | (1<<CS20));
	//timer2 on
	TIMSK |= (1<<TOIE2);  
}
/////////////////////////////////////////////////////
RokitFlyingClass RokitFlying;