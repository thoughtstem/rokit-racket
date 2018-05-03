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

#define NUM_DIGITAL_PINS            53
#define NUM_ANALOG_INPUTS           8

#define analogInputToDigitalPin(p)  ((p < 8) ? (p) + 24 : -1)

#if defined(__AVR_ATmega128__)
#define digitalPinHasPWM(p) ((p)==10 || (p)==11 || (p)==16 || (p)==18 || (p)==20 || (p)==22)
#endif

#define TIMER0  46 // available on ATMega32/644

const static uint8_t SS   = 12;
const static uint8_t MOSI = 13;
const static uint8_t MISO = 14;
const static uint8_t SCK  = 15;

const static uint8_t SCL = 8;
const static uint8_t SDA = 9;

//static const uint8_t LED_BUILTIN = 31;

// Analog inputs definition
const static uint8_t A0 = 24;     
const static uint8_t A1 = 25;
const static uint8_t A2 = 26;
const static uint8_t A3 = 27;
const static uint8_t A4 = 28;
const static uint8_t A5 = 29;
const static uint8_t A6 = 30;
const static uint8_t A7 = 31;
/////////////////////

#ifdef ARDUINO_MAIN

const uint16_t PROGMEM port_to_mode_PGM[] = {
    NOT_A_PORT,
    (uint16_t) &DDRA,
    (uint16_t) &DDRB,
    (uint16_t) &DDRC,
    (uint16_t) &DDRD,
    (uint16_t) &DDRE,
    (uint16_t) &DDRF,
    (uint16_t) &DDRG,
};

const uint16_t PROGMEM port_to_output_PGM[] = {
    NOT_A_PORT,
    (uint16_t) &PORTA,
    (uint16_t) &PORTB,
    (uint16_t) &PORTC,
    (uint16_t) &PORTD,
    (uint16_t) &PORTE,
    (uint16_t) &PORTF,
    (uint16_t) &PORTG,
};

const uint16_t PROGMEM port_to_input_PGM[] = {
    NOT_A_PORT,
    (uint16_t) &PINA,
    (uint16_t) &PINB,
    (uint16_t) &PINC,
    (uint16_t) &PIND,
    (uint16_t) &PINE,
    (uint16_t) &PINF,
    (uint16_t) &PING,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = {

    // -- UART0 --
    PE, //** 0 ** PE0 - RXD0
    PE, //** 1 ** PE1 - TXD0
    
    PC, //** 2 ** PC5 - DIRECTION
    
    // -- UART1 --
    PD, //** 3 ** PD2 - RXD1
    PD, //** 4 ** PD3 - TXD1


    PC, //** 5 ** PC3 - STATUS LED
    PC, //** 6 ** PC4 - BUTTON
    PC, //** 7 ** PC6 - BUZZER
    
    PD, //** 8 ** PD0 - SCL,INT0
    PD, //** 9 ** PD1 - SDA,INT1
    PB, //** 10 ** PB7 - OC2,TIMER1C,PWM
    PE, //** 11 ** PE5 - TIMER3C
    PB, //** 12 ** PB0 - SS
    PB, //** 13 ** PB2 - MOSI
    PB, //** 14 ** PB3 - MISO
    PB, //** 15 ** PB1 - SCK
    
    PB, //** 16 ** PB5 - TIMER1A,PWM
    PD, //** 17 ** PD7 - T2
    PB, //** 18 ** PB6 - TIMER1B,PWM
    PD, //** 19 ** PD6 - T1
    PE, //** 20 ** PE3 - TIMER3A,PWM
    PD, //** 21 ** PD5 - XCK1
    PE, //** 22 ** PE4 - TIMER3B,PWM
    PD, //** 23 ** PD4 - ICP1

    PF, //** 24 ** PF0 - ADC0
    PF, //** 25 ** PF1 - ADC1
    PF, //** 26 ** PF2 - ADC2
    PF, //** 27 ** PF3 - ADC3
    PF, //** 28 ** PF4 - ADC4
    PF, //** 29 ** PF5 - ADC5
    PF, //** 30 ** PF6 - ADC6
    PF, //** 31 ** PF7 - ADC7
    
    PA, //** 32 ** PA0
    PA, //** 33 ** PA1 
    PA, //** 34 ** PA2 
    PA, //** 35 ** PA3 
    PA, //** 36 ** PA4
    
    PA, //** 37 ** PA5 - NOT USE
    PA, //** 38 ** PA6 - NOT USE
    PA, //** 39 ** PA7 - NOT USE
    
    PE, //** 40 ** PE6 - INT6
    PE, //** 41 ** PE7 - INT7
    PE, //** 42 ** PE2 - OXCK
    
    PC, //** 43 ** PC0 - DIPSW1
    PC, //** 44 ** PC1 - DIPSW2
    PC, //** 45 ** PC2 - DIPSW3
    
    PB, //** 46 ** PB4 - NOT USE(OC0)
    PC, //** 47 ** PC7 - NOT USE
    PG, //** 48 ** PG0 - NOT USE
    PG, //** 49 ** PG1 - NOT USE
    PG, //** 50 ** PG2 - NOT USE
    PG, //** 51 ** PG3 - NOT USE
    PG, //** 52 ** PG4 - NOT USE
    
};


const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {

    // -- UART0 --
    _BV(0), //** 0 ** PE0 - RXD0
    _BV(1), //** 1 ** PE1 - TXD0
    
    _BV(5), //** 2 ** PC5 - DIRECTION
        
    // -- UART1 --
    _BV(2), //** 3 ** PD2 - RXD1
    _BV(3), //** 4 ** PD3 - TXD1


    _BV(3), //** 5 ** PC3 - STATUS LED
    _BV(4), //** 6 ** PC4 - BUTTON
    _BV(6), //** 7 ** PC6 - BUZZER
    
    _BV(0), //** 8 ** PD0 - SCL,INT0
    _BV(1), //** 9 ** PD1 - SDA,INT1
    _BV(7), //** 10 ** PB7 - OC2,TIMER1C,PWM
    _BV(5), //** 11 ** PE5 - TIMER3C
    _BV(0), //** 12 ** PB0 - SS
    _BV(2), //** 13 ** PB2 - MOSI
    _BV(3), //** 14 ** PB3 - MISO
    _BV(1), //** 15 ** PB1 - SCK
    
    _BV(5), //** 16 ** PB5 - TIMER1A,PWM
    _BV(7), //** 17 ** PD7 - T2
    _BV(6), //** 18 ** PB6 - TIMER1B,PWM
    _BV(6), //** 19 ** PD6 - T1
    _BV(3), //** 20 ** PE3 - TIMER3A,PWM
    _BV(5), //** 21 ** PD5 - XCK1
    _BV(4), //** 22 ** PE4 - TIMER3B,PWM
    _BV(4), //** 23 ** PD4 - ICP1
    
    _BV(0), //** 24 ** PF0 - ADC0
    _BV(1), //** 25 ** PF1 - ADC1
    _BV(2), //** 26 ** PF2 - ADC2
    _BV(3), //** 27 ** PF3 - ADC3
    _BV(4), //** 28 ** PF4 - ADC4
    _BV(5), //** 29 ** PF5 - ADC5
    _BV(6), //** 30 ** PF6 - ADC6
    _BV(7), //** 31 ** PF7 - ADC7
    
    _BV(0), //** 32 ** PA0
    _BV(1), //** 33 ** PA1 
    _BV(2), //** 34 ** PA2 
    _BV(3), //** 35 ** PA3 
    _BV(4), //** 36 ** PA4
    
    _BV(5), //** 37 ** PA5 - NOT USE
    _BV(6), //** 38 ** PA6 - NOT USE
    _BV(7), //** 39 ** PA7 - NOT USE
    
    _BV(6), //** 40 ** PE6 - INT6
    _BV(7), //** 41 ** PE7 - INT7
    _BV(2), //** 42 ** PE2 - OXCK
    
    _BV(0), //** 43 ** PC0 - DIPSW1
    _BV(1), //** 44 ** PC1 - DIPSW2
    _BV(2), //** 45 ** PC2 - DIPSW3
    
    _BV(4), //** 46 ** PB4 - NOT USE(OC0)
    _BV(7), //** 47 ** PC7 - NOT USE
    _BV(0), //** 48 ** PG0 - NOT USE
    _BV(1), //** 49 ** PG1 - NOT USE
    _BV(2), //** 50 ** PG2 - NOT USE
    _BV(3), //** 51 ** PG3 - NOT USE
    _BV(4), //** 52 ** PG4 - NOT USE 
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {

    // -- UART0 --
    NOT_ON_TIMER, //** 0 ** PE0 - RXD0
    NOT_ON_TIMER, //** 1 ** PE1 - TXD0
    
    
    NOT_ON_TIMER, //** 2 ** PC5 - DIRECTION
    
    // -- UART1 --
    NOT_ON_TIMER, //** 3 ** PD2 - RXD1
    NOT_ON_TIMER, //** 4 ** PD3 - TXD1


    NOT_ON_TIMER, //** 5 ** PC3 - STATUS LED
    NOT_ON_TIMER, //** 6 ** PC4 - BUTTON
    NOT_ON_TIMER, //** 7 ** PC6 - BUZZER
    
    NOT_ON_TIMER, //** 8 ** PD0 - SCL,INT0
    NOT_ON_TIMER, //** 9 ** PD1 - SDA,INT1
    TIMER2, ///** 10 ** PB7 - OC2,TIMER1C,PWM
    TIMER3C, //** 11 ** PE5 - TIMER3C
    NOT_ON_TIMER, //** 12 ** PB0 - SS
    NOT_ON_TIMER, //** 13 ** PB2 - MOSI
    NOT_ON_TIMER, //** 14 ** PB3 - MISO
    NOT_ON_TIMER, //** 15 ** PB1 - SCK
    
    TIMER1A, //** 16 ** PB5 - TIMER1A,PWM
    NOT_ON_TIMER, //** 17 ** PD7 - T2
    TIMER1B, //** 18 ** PB6 - TIMER1B,PWM
    NOT_ON_TIMER, //** 19 ** PD6 - T1
    TIMER3A, //** 20 ** PE3 - TIMER3A,PWM
    NOT_ON_TIMER, //** 21 ** PD5 - XCK1
    TIMER3B, //** 22 ** PE4 - TIMER3B,PWM
    NOT_ON_TIMER, //** 23 ** PD4 - ICP1
    
    NOT_ON_TIMER, //** 24 ** PF0 - ADC0
    NOT_ON_TIMER, //** 25 ** PF1 - ADC1
    NOT_ON_TIMER, //** 26 ** PF2 - ADC2
    NOT_ON_TIMER, //** 27 ** PF3 - ADC3
    NOT_ON_TIMER, //** 28 ** PF4 - ADC4
    NOT_ON_TIMER, //** 29 ** PF5 - ADC5
    NOT_ON_TIMER, //** 30 ** PF6 - ADC6
    NOT_ON_TIMER, //** 31 ** PF7 - ADC7
    
    NOT_ON_TIMER, //** 32 ** PA0
    NOT_ON_TIMER, //** 33 ** PA1 
    NOT_ON_TIMER, //** 34 ** PA2 
    NOT_ON_TIMER, //** 35 ** PA3 
    NOT_ON_TIMER, //** 36 ** PA4
    
    NOT_ON_TIMER, //** 37 ** PA5 - NOT USE
    NOT_ON_TIMER, //** 38 ** PA6 - NOT USE
    NOT_ON_TIMER, //** 39 ** PA7 - NOT USE
    
    NOT_ON_TIMER, //** 40 ** PE6 - INT6
    NOT_ON_TIMER, //** 41 ** PE7 - INT7
    NOT_ON_TIMER, //** 42 ** PE2 - OXCK
    
    NOT_ON_TIMER, //** 43 ** PC0 - DIPSW1
    NOT_ON_TIMER, //** 44 ** PC1 - DIPSW2
    NOT_ON_TIMER, //** 45 ** PC2 - DIPSW3
    
    TIMER0, 	//** 46 ** PB4 - NOT USE(OC0)
    NOT_ON_TIMER, //** 47 ** PC7 - NOT USE
    NOT_ON_TIMER, //** 48 ** PG0 - NOT USE
    NOT_ON_TIMER, //** 49 ** PG1 - NOT USE
    NOT_ON_TIMER, //** 50 ** PG2 - NOT USE
    NOT_ON_TIMER, //** 51 ** PG3 - NOT USE
    NOT_ON_TIMER, //** 52 ** PG4 - NOT USE
    
};

#endif
#endif
