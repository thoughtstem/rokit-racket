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
#define NUM_ANALOG_INPUTS           8
#define analogInputToDigitalPin(p)  ((p < 8) ? (p) + 24 : -1)
#define digitalPinHasPWM(p)         ((p) == 6 || (p) == 11 || (p) == 16 || (p) == 19)
#define TIMER0  8 // available on ATMega32/644

const static uint8_t SS   = 12;
const static uint8_t MOSI = 13;
const static uint8_t MISO = 14;
const static uint8_t SCK  = 15;

const static uint8_t SCL = 8;
const static uint8_t SDA = 9;

const static uint8_t A0 = 24;     
const static uint8_t A1 = 25;
const static uint8_t A2 = 26;
const static uint8_t A3 = 27;
const static uint8_t A4 = 28;
const static uint8_t A5 = 29;
const static uint8_t A6 = 30;
const static uint8_t A7 = 31;

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
	
	PD  , // Digital 0 ** 	PD 0 **	DIP 14 ** USART_RX		- UART, USB
	PD  , // Digital 1 ** 	PD 1 **	DIP 15 ** USART_TX		- UART, USB
	PD  , // Digital 2 ** 	PD 6 **	DIP 20 ** ICP1			- UART DIRECTION	
	PB  , // Digital 3 ** 	PB 0 **	DIP 1  ** XCK			- Dip s/w1
	PB  , // Digital 4 ** 	PB 1 **	DIP 2  ** T1			- Dip s/w2	
	PC  , // Digital 5 ** 	PC 6 **	DIP 28 **		USABLE	- LED 
	PB  , // Digital 6 ** 	PB 3 **	DIP 4  ** OC0/AIN1  	USABLE	- start button 
	PC  , // Digital 7 ** 	PC 7 **	DIP 29 **		USABLE	- BUZZER
	
	PC  , // Digital 8 ** 	PC 0 **	DIP 22 ** SCL		USABLE 	-I2C
	PC  , // Digital 9 ** 	PC 1 **	DIP 23 ** SDA		USABLE 	-I2C
	PB  , // Digital 10 ** 	PB 2 **	DIP 3  ** INT2/AIN0	USABLE	-INTERRUPT
	PD  , // Digital 11 ** 	PD 7 **	DIP 21 ** OC2		USABLE 	-PWM
	PB  , // Digital 12 ** 	PB 4 **	DIP 5  ** SS		USABLE	-SPI
	PB  , // Digital 13 ** 	PB 5 **	DIP 6  ** MOSI		USABLE  -SPI
	PB  , // Digital 14 ** 	PB 6 **	DIP 7  ** MISO		USABLE	-SPI
	PB  , // Digital 15 ** 	PB 7 **	DIP 8  ** SCK		USABLE	-SPI
	
	PD  , // Digital 16 ** 	PD 5 **	DIP 19 ** OC1A		USABLE	-PWM
	PC  , // Digital 17 ** 	PC 2 **	DIP 24 **		USABLE 
	PC  , // Digital 18 ** 	PC 3 **	DIP 25 **		USABLE 
	PD  , // Digital 19 ** 	PD 4 **	DIP 18 ** OC1B		USABLE	-PWM
	PC  , // Digital 20 ** 	PC 4 **	DIP 26 **		USABLE 
	PC  , // Digital 21 ** 	PC 5 **	DIP 27 **		USABLE 
	PD  , // Digital 22 ** 	PD 2 **	DIP 16 ** INT0 		USABLE	-INTERRUPT
	PD  , // Digital 23 ** 	PD 3 **	DIP 17 ** INT1		USABLE	-INTERRUPT

	PA  , // Digital 24 ** 	PA 0 **	DIP 40 **		USABLE 
	PA  , // Digital 25 ** 	PA 1 **	DIP 39 **		USABLE 
	PA  , // Digital 26 ** 	PA 2 **	DIP 38 **		USABLE 
	PA  , // Digital 27 ** 	PA 3 **	DIP 37 **		USABLE 
	PA  , // Digital 28 ** 	PA 4 **	DIP 36 **		USABLE 
	PA  , // Digital 29 ** 	PA 5 **	DIP 35 **		USABLE 
	PA  , // Digital 30 ** 	PA 6 **	DIP 34 **		USABLE 
	PA  , // Digital 31 ** 	PA 7 **	DIP 33 **		USABLE 
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
/**********************************************************************/	
	_BV(0), /* 8, SYSTEM */
	_BV(1),
	_BV(6),
	_BV(0),
	_BV(1),
	_BV(6),
	_BV(3),
	_BV(7),
/**********************************************************************/	
	_BV(0), /* 8, UP PORT */
	_BV(1),
	_BV(2),
	_BV(7),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
/**********************************************************************/	
	_BV(5), /* 16, DOWN PORT */
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(4),
	_BV(5),
	_BV(2),
	_BV(3),
/**********************************************************************/	
	_BV(0), /* 24, RIGHT PORT */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
/**********************************************************************/		
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {
	NOT_ON_TIMER,	/* 0 - PD0 */
	NOT_ON_TIMER,	/* 1 - PD1 */
	NOT_ON_TIMER,	/* 2 - PD6 */
	NOT_ON_TIMER,	/* 3 - PB0 */
	NOT_ON_TIMER,	/* 4 - PB1 */
	NOT_ON_TIMER,	/* 5 - PC6 */
	TIMER0,		/* 6 - PB3 */
	NOT_ON_TIMER,	/* 7 - PC7 */	
	
	NOT_ON_TIMER,	/* 8 - PC0 */
	NOT_ON_TIMER,	/* 9 - PC1 */
    	NOT_ON_TIMER,	/* 10 - PB2 */
	TIMER2,		/* 11 - PD7 */
	NOT_ON_TIMER,	/* 12 - PB4 */
	NOT_ON_TIMER,	/* 13 - PB5 */
	NOT_ON_TIMER,	/* 14 - PB6 */
	NOT_ON_TIMER,	/* 15 - PB7 */
	
	TIMER1A,	/* 16 - PD5 */
	NOT_ON_TIMER,	/* 17 - PC2 */
	NOT_ON_TIMER,	/* 18 - PC3 */
	TIMER1B,	/* 19 - PD4 */
	NOT_ON_TIMER,	/* 20 - PC4 */
	NOT_ON_TIMER,	/* 21 - PC5 */
	NOT_ON_TIMER,	/* 22 - PD2 */
	NOT_ON_TIMER,	/* 23 - PD3 */
	
	NOT_ON_TIMER,	/* 24,- PA0 */
	NOT_ON_TIMER,	/* 25 - PA1 */
	NOT_ON_TIMER,	/* 26 - PA2 */
	NOT_ON_TIMER,	/* 27 - PA3 */
	NOT_ON_TIMER,	/* 28 - PA4 */
	NOT_ON_TIMER,	/* 29 - PA5 */
	NOT_ON_TIMER,	/* 30 - PA6 */
	NOT_ON_TIMER,	/* 31 - PA7 */
};

#endif
#endif
