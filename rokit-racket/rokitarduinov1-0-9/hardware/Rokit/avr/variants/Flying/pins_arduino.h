/* ------------------------------------------------------*
*                                                        *
* Copyright (c) 2013, Jarek Zok <jarek.zok@fwioo.pl>     *
* All rights reserved.                                   *
*                                                        *
* This program is free software; you can redistribute it *
* and/or modify it under the terms of the GNU General    *
* Public License as published by the Free Software       *
* Foundation; either version 2 of the License, or        *
* (at your option) any later version.                    *
*                                                        *
* This program is distributed in the hope that it will   *
* be useful, but WITHOUT ANY WARRANTY; without even the  *
* implied warranty of MERCHANTABILITY or FITNESS FOR A   *
* PARTICULAR PURPOSE.  See the GNU General Public        *
* License for more details.                              *
*                                                        *
* You should have received a copy of the GNU General     *
* Public License along with this program; if not, write  *
* to the Free Software Foundation, Inc.,                 *
* 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA *
*                                                        *
* Licence can be viewed at                               *
* http://www.fsf.org/licenses/gpl.txt                    *
*                                                        *
*                                                        *
**********************************************************/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>

#define NUM_DIGITAL_PINS            32
#define NUM_ANALOG_INPUTS           3
#define analogInputToDigitalPin(p)  ((p < 3) ? (p) + 10 : -1)

#define digitalPinHasPWM(p)         ((p) == 5 || (p) == 8 || (p) == 9 || (p) == 24)

#define TIMER0  24 // available on ATMega32/644

#define BOARD_TYPE  1 // rokitboard type(same mcu)

const static uint8_t SS   = 25;
const static uint8_t MOSI = 15;
const static uint8_t MISO = 13;
const static uint8_t SCK  = 14;

static const uint8_t SCL = 6;  
static const uint8_t SDA = 7;  
static const uint8_t LED_BUILTIN = 9;  

const static uint8_t A0 = 10;     
const static uint8_t A1 = 11;
const static uint8_t A2 = 12;

#ifdef ARDUINO_MAIN

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint16_t PROGMEM port_to_mode_PGM[] = {
	NOT_A_PORT,
	(uint16_t) &DDRA,
	(uint16_t) &DDRB,
	(uint16_t) &DDRC,
	(uint16_t) &DDRD,
};

const uint16_t PROGMEM port_to_output_PGM[] = {
	NOT_A_PORT,
	(uint16_t) &PORTA,
	(uint16_t) &PORTB,
	(uint16_t) &PORTC,
	(uint16_t) &PORTD,
};

const uint16_t PROGMEM port_to_input_PGM[] = {
	NOT_A_PORT,
	(uint16_t) &PINA,
	(uint16_t) &PINB,
	(uint16_t) &PINC,
	(uint16_t) &PIND,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
	
	// Uart
	PD  , // Digital 0 ** PD 0 ** DIP 14 ** USART0_RX	
	PD  , // Digital 1 ** PD 1 ** DIP 15 ** USART0_TX	
	
	// Select, Start Button	
	PC  , // Digital 2 ** PC 6 ** DIP 25  ** TOSC1          USABLE 
	PB  , // Digital 3 ** PB 2 ** DIP 42  ** INT2/AIN0      USABLE 
	
	// Dip S/W 1,2
	PD  , // Digital 4 ** PD 6 ** DIP 15  ** 		USABLE
	PD  , // Digital 5 ** PD 7 ** DIP 16  ** OC2		USABLE
	
	// SERVO
	PC  , // Digital 6 ** PC 0 ** DIP 19 ** SCL               USABLE 
	PC  , // Digital 7 ** PC 1 ** DIP 20 ** SDA               USABLE 
	PD  , // Digital 8 ** PD 5 ** DIP 14 ** OC1A              USABLE 
		
	// State LED
	PD  , // Digital 9 ** PD 4 ** DIP 13 ** OC1B            USABLE 
		
	// ADC0, ADC1, ADC2
	PA  , // Digital 10 ** PA 0 ** DIP 37 ** ADC0             USABLE 
	PA  , // Digital 11 ** PA 1 ** DIP 36 ** ADC1             USABLE 
	PA  , // Digital 12 ** PA 2 ** DIP 35 ** ADC2             USABLE 
		
	//Display LED	
	PB  , // Digital 13 ** PB 6 ** DIP 2 ** MISO                USABLE 
	PB  , // Digital 14 ** PB 7 ** DIP 3 ** SCK            USABLE 
	PB  , // Digital 15 ** PB 5 ** DIP 1 ** MOSI               USABLE 	
	PA  , // Digital 16 ** PA 3 ** DIP 34 **               USABLE 
	PD  , // Digital 17 ** PD 3 ** DIP 12 **               USABLE 
		
	//dc motor - 1,2,3,4
	PC  , // Digital 18 ** PC 2 ** DIP 21  **              
	PC  , // Digital 19 ** PC 3 ** DIP 22  **               
			
	PB  , // Digital 20 ** PB 1 ** DIP 41  **          
	PB  , // Digital 21 ** PB 0 ** DIP 40  **   
	            
	PC  , // Digital 22 ** PC 4 ** DIP 23  ** 
	PC  , // Digital 23 ** PC 5 ** DIP 24  ** 
	
	PB  , // Digital 24 ** PB 3 ** DIP 43  ** OC0
	PB  , // Digital 25 ** PB 4 ** DIP 44  ** SS
			
	//IR Receiver
	PD  , // Digital 26 ** PD 2 ** DIP 11  ** INT0
				
	//Wired Controller
	PA  , // Digital27 ** PA 7 ** DIP 30 **  
	PA  , // Digital28 ** PA 6 ** DIP 31 ** 
	PC  , // Digital29 ** PC 7 ** DIP 26 **             
	PA  , // Digital30 ** PA 4 ** DIP 33 **             
	PA  , // Digital31 ** PA 5 ** DIP 32 **             

};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
	//uart
	_BV(0), // Digital 0 ** PD 0 ** DIP 14 ** USART0_RX	
	_BV(1),	// Digital 1 ** PD 1 ** DIP 15 ** USART0_TX	
	
	// Select, Start Button	
	_BV(6)  , // Digital 2 ** PC 6 ** DIP 25  ** TOSC1          USABLE 
	_BV(2)  , // Digital 3 ** PB 2 ** DIP 42  ** INT2/AIN0      USABLE 
	
	// Dip S/W 1,2
	_BV(6)  , // Digital 4 ** PD 6 ** DIP 15  ** 		USABLE
	_BV(7)  , // Digital 5 ** PD 7 ** DIP 16  ** OC2	USABLE
	
	// SERVO
	_BV(0)  , // Digital 6 ** PC 0 ** DIP 19 ** SCL              USABLE 
	_BV(1)  , // Digital 7 ** PC 1 ** DIP 20 ** SDA               USABLE 
	_BV(5)  , // Digital 8 ** PD 5 ** DIP 14 ** OC1A              USABLE 
		
	// State LED
	_BV(4)  , // Digital 9 ** PD 4 ** DIP 13 ** OC1B            USABLE 
		
	// ADC0, ADC1, ADC2
	_BV(0)  , // Digital 10 ** PA 0 ** DIP 37 ** ADC0             USABLE 
	_BV(1)  , // Digital 11 ** PA 1 ** DIP 36 ** ADC1             USABLE 
	_BV(2)  , // Digital 12 ** PA 2 ** DIP 35 ** ADC2             USABLE 
		
	//Display LED	
	_BV(6)  , // Digital 13 ** PB 6 ** DIP 2 ** MISO               USABLE 
	_BV(7)  , // Digital 14 ** PB 7 ** DIP 3 ** SCK               USABLE 
	_BV(5)  , // Digital 15 ** PB 5 ** DIP 1 ** MOSI                USABLE 	
	_BV(3)  , // Digital 16 ** PA 3 ** DIP 34 **               USABLE 
	_BV(3)  , // Digital 17 ** PD 3 ** DIP 12 **               USABLE 
		
	//dc motor - A , B
	_BV(2)  , // Digital 18 ** PC 2 ** DIP 21  **              
	_BV(3)  , // Digital 19 ** PC 3 ** DIP 22  **               
	

	_BV(1)  , // Digital 20 ** PB 1 ** DIP 41  **          
	_BV(0)  , // Digital 21 ** PB 0 ** DIP 40  **    
	           
	_BV(4)  , // Digital 22 ** PC 4 ** DIP 23  ** 
	_BV(5)  , // Digital 23 ** PC 5 ** DIP 24  ** 		
		
	_BV(3)  , // Digital 24 ** PB 3 ** DIP 43  ** OC0
	_BV(4)  , // Digital 25 ** PB 4 ** DIP 44  ** SS
		
	
	//IR Receiver
	_BV(2)  , // Digital 26 ** PD 2 ** DIP 11  ** INT0
				
	
	//Wired Controller
	_BV(7)  , // Digital27 ** PA 7 ** DIP 30 **  
	_BV(6)  , // Digital28 ** PA 6 ** DIP 31 ** 
	_BV(7)  , // Digital29 ** PC 7 ** DIP 26 **             
	_BV(4)  , // Digital30 ** PA 4 ** DIP 33 **             
	_BV(5)  , // Digital31 ** PA 5 ** DIP 32 **     
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {
	NOT_ON_TIMER,    /* 0 - PD0 */
	NOT_ON_TIMER,	 /* 1 - PD1 */
	NOT_ON_TIMER,	 /* 2 - PC6 */
	NOT_ON_TIMER,    /* 3 - PB2 */
	NOT_ON_TIMER,    /* 4 - PD6 */
	
	TIMER2,     	/* 5 - PD7 */
	NOT_ON_TIMER,   /* 6 - PC0 */
	NOT_ON_TIMER,   /* 7 - PC1 */	
	TIMER1A,    	/* 8 - PD5 */
	TIMER1B,    	/* 9 - PD4 */
   	NOT_ON_TIMER,   /* 10 - PA0 */
   	 
	NOT_ON_TIMER,   /* 11 - PA1 */
	NOT_ON_TIMER, 	/* 12 - PA2 */
	NOT_ON_TIMER, 	/* 13 - PB6 */
	NOT_ON_TIMER, 	/* 14 - PB7 */
	NOT_ON_TIMER, 	/* 15 - PB5 */
	
	NOT_ON_TIMER, 	/* 16 - PA3 */	
	NOT_ON_TIMER, 	/* 17 - PD3 */
	NOT_ON_TIMER, 	/* 18 - PC2 */
	NOT_ON_TIMER, 	/* 19 - PC3 */
	NOT_ON_TIMER, 	/* 20 - PC4 */
	
	NOT_ON_TIMER, 	/* 21 - PC5 */
	NOT_ON_TIMER, 	/* 22 - PB1 */
	NOT_ON_TIMER, 	/* 23 - PB0 */
	TIMER0, 	/* 24 - PB3 */
	NOT_ON_TIMER, 	/* 25 - PB4 */
	
	NOT_ON_TIMER, 	/* 26 - PD2 */
	NOT_ON_TIMER, 	/* 27 - PA7 */
	NOT_ON_TIMER, 	/* 28 - PA6 */
	NOT_ON_TIMER, 	/* 29 - PC7 */
	NOT_ON_TIMER, 	/* 30 - PA4 */
	NOT_ON_TIMER, 	/* 31 - PA5 */
};

#endif
#endif
