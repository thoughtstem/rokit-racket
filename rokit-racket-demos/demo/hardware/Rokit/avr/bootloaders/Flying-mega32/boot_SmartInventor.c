
/* some includes */
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <avr/eeprom.h>

/* Use the F_CPU defined in Makefile */
/* set the waiting time for the bootloader */
/* get this from the Makefile instead */

#define MAX_TIME_COUNT (F_CPU>>4)
#define NUM_LED_FLASHES   1
#define MAX_ERROR_COUNT 5
#define BAUD_RATE   115200

/* SW_MAJOR and MINOR needs to be updated from time to time to avoid warning message from AVR Studio */
/* never allow AVR Studio to do an update !!!! */
#define HW_VER	 0x02
#define SW_MAJOR 0x01
#define SW_MINOR 0x10

/* onboard LED is used to indicate, that the bootloader was entered (3x flashing) */
/* if monitor functions are included, LED goes on after monitor was entered */

//#define START_SW_ON				(((~PINB) >> 5) & 0b111)	// ONLY smart
//#define START_SW_ON	      (((~PINB) >> 2) & 0b1)
//#define Remote

#define START_SW_ON !(((~PINB) >> 2) & 0b1)

#define DipSw1 	(((~PIND) >> 6) & 0b1)
#define DipSw2 	(((~PIND) >> 7) & 0b1)

/*
//SMART
#define LED_DDR  DDRC
#define LED_PORT PORTC
#define LED_PIN  PINC
#define LED      PINC7
*/


#define LED_DDR  DDRD
#define LED_PORT PORTD
#define LED_PIN  PIND
#define LED      PIND4


/*****************************************************/


//key
#define KEY1 (((~PINA) >> 7) & 0b1)
#define KEY2 (((~PINC) >> 7) & 0b1)
#define KEY3 (((~PINA) >> 3) & 0b1)
#define KEY4 (((~PINA) >> 4) & 0b1)


//ground
#define KEY_COMMON1_ON 		PORTA |=  0b01000000
#define KEY_COMMON1_OFF 	PORTA &= ~0b01000000

#define KEY_COMMON2_ON 		PORTC |=  0b01000000
#define KEY_COMMON2_OFF 	PORTC &= ~0b01000000


//cable remocon

#define  CABLE_KEY_UP   	0x01
#define  CABLE_KEY_DOWN   	0x02
#define  CABLE_KEY_LEFT   	0x04
#define  CABLE_KEY_RIGHT   	0x08
#define  CABLE_KEY_A   		0x16
#define  CABLE_KEY_B  		0x32



#define DC1A_ON 	PORTC |=  0b1000
#define DC1A_OFF 	PORTC &= ~0b1000

#define DC1B_ON 	PORTC |=  0b100
#define DC1B_OFF 	PORTC &= ~0b100

#define DC2A_ON 	PORTB |=  0b1000
#define DC2A_OFF 	PORTB &= ~0b1000

#define DC2B_ON 	PORTB |=  0b10000
#define DC2B_OFF 	PORTB &= ~0b10000

#define DC3A_ON 	PORTC |=  0b10000
#define DC3A_OFF 	PORTC &= ~0b10000

#define DC3B_ON 	PORTC |=  0b100000
#define DC3B_OFF 	PORTC &= ~0b100000

#define DC4A_ON 	PORTB |=  0b1
#define DC4A_OFF 	PORTB &= ~0b1

#define DC4B_ON 	PORTB |=  0b10
#define DC4B_OFF 	PORTB &= ~0b10





/*****************************************************/

/* define various device id's */
/* manufacturer byte is always the same */
#define SIG1	0x1E	// Yep, Atmel is the only manufacturer of AVR micros.  Single source :(

#if defined __AVR_ATmega32__
#define SIG2	0x95
#define SIG3	0x02
#define PAGE_SIZE	0x40U	//64 words

#elif defined __AVR_ATmega16__
#define SIG2	0x94
#define SIG3	0x03
#define PAGE_SIZE	0x40U	//64 words

#endif


/* function prototypes */
void putch(char);
char getch(void);
void getNch(uint8_t);
void byte_response(uint8_t);
void nothing_response(void);
char gethex(void);
void puthex(char);
void flash_led(uint8_t);

/* some variables */
union address_union {
	uint16_t word;
	uint8_t  byte[2];
} address;

union length_union {
	uint16_t word;
	uint8_t  byte[2];
} length;

struct flags_struct {
	unsigned eeprom : 1;
	unsigned rampz  : 1;
} flags;

uint8_t buff[256];
uint8_t address_high;

uint8_t pagesz=0x80;

uint8_t i;
uint8_t bootuart = 0;

uint8_t error_count = 0;

void (*app_start)(void) = 0x0000;


/* main program starts here */
int main(void)
{
	uint8_t ch,ch2;
	uint16_t w;

/*
DDRA = 0xff;
DDRB = 0xff;
DDRC = 0xff;
DDRD = 0xff;

PORTA = 0xff;
PORTB = 0xff;
PORTC = 0xff;
PORTD = 0xff;

while(1);
*/

#ifdef WATCHDOG_MODS
	ch = MCUSR;
	MCUSR = 0;

	WDTCSR |= _BV(WDCE) | _BV(WDE);
	WDTCSR = 0;

	// Check if the WDT was used to reset, in which case we dont bootload and skip straight to the code. woot.
	if (! (ch &  _BV(EXTRF))) // if its a not an external reset...
		app_start();  // skip bootloader
#else
	asm volatile("nop\n\t");
#endif


/* check if flash is programmed already, if not start bootloader anyway */
if(pgm_read_byte_near(0x0000) != 0xFF) {
}


#if defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__)
     /* m16,m32 */
     UCSRA = 0x0;           
     UCSRB = 0b00011000;     // 송수신 모두 가능하게 함, 수신완료 인터럽트 disable
     UCSRC = 0b10000110;     // 비동기 데이타 8bit 모드 
     UBRRH = 0;              // 비동기 일반모드 115200bps
     UBRRL = 3;

     //스마트 보드 다운로드 포함

   //  DDRD |= 0b10000000;    
   //  PORTD |= 0b10000000;

  //   DDRB |=	0b00000000;
  //   PORTB |=	0b11100000;


#endif

	/* set LED pin as output */
	LED_DDR |= _BV(LED);
	flash_led(NUM_LED_FLASHES);

	/* 20050803: by DojoCorp, this is one of the parts provoking the
		 system to stop listening, cancelled from the original */
	//putch('\0');

	/* forever loop */
	for (;;) {	            
 
        //putch('1');
	/* get character from UART */
	ch = getch();

	/* A bunch of if...else if... gives smaller code than switch...case ! */

	/* Hello is anyone home ? */ 
	if(ch=='0') {
		nothing_response();
	}

	/* Request programmer ID */
	/* Not using PROGMEM string due to boot block in m128 being beyond 64kB boundry  */
	/* Would need to selectively manipulate RAMPZ, and it's only 9 characters anyway so who cares.  */
	else if(ch=='1') {
		if (getch() == ' ') {
			putch(0x14);
			putch('A');
			putch('V');
			putch('R');
			putch(' ');
			putch('I');
			putch('S');
			putch('P');
			putch(0x10);
		} else {
			if (++error_count == MAX_ERROR_COUNT)
				app_start();
		}
	}


	/* AVR ISP/STK500 board commands  DON'T CARE so default nothing_response */
	else if(ch=='@') {
		ch2 = getch();
		if (ch2>0x85) getch();
		nothing_response();
	}


	/* AVR ISP/STK500 board requests */
	else if(ch=='A') {
		ch2 = getch();
		if(ch2==0x80) byte_response(HW_VER);		// Hardware version
		else if(ch2==0x81) byte_response(SW_MAJOR);	// Software major version
		else if(ch2==0x82) byte_response(SW_MINOR);	// Software minor version
		else if(ch2==0x98) byte_response(0x03);		// Unknown but seems to be required by avr studio 3.56
		else byte_response(0x00);				// Covers various unnecessary responses we don't care about
	}


	/* Device Parameters  DON'T CARE, DEVICE IS FIXED  */
	else if(ch=='B') {
		getNch(20);
		nothing_response();
	}


	/* Parallel programming stuff  DON'T CARE  */
	else if(ch=='E') {
		getNch(5);
		nothing_response();
	}


	/* P: Enter programming mode  */
	/* R: Erase device, don't care as we will erase one page at a time anyway.  */
	else if(ch=='P' || ch=='R') {
		nothing_response();
	}


	/* Leave programming mode  */
	else if(ch=='Q') {
		nothing_response();
#ifdef WATCHDOG_MODS
		// autoreset via watchdog (sneaky!)
		WDTCSR = _BV(WDE);
		while (1); // 16 ms
#endif
	}

	/* Set address, little endian. EEPROM in bytes, FLASH in words  */
	/* Perhaps extra address bytes may be added in future to support > 128kB FLASH.  */
	/* This might explain why little endian was used here, big endian used everywhere else.  */
	else if(ch=='U') {
		address.byte[0] = getch();
		address.byte[1] = getch();
		nothing_response();
	}


	/* Universal SPI programming command, disabled.  Would be used for fuses and lock bits.  */
	else if(ch=='V') {
		if (getch() == 0x30) {
			getch();
			ch = getch();
			getch();
			if (ch == 0) {
				byte_response(SIG1);
			} else if (ch == 1) {
				byte_response(SIG2); 
			} else {
				byte_response(SIG3);
			} 
		} else {
			getNch(3);
			byte_response(0x00);
		}
	}


	/* Write memory, length is big endian and is in bytes  */
	else if(ch=='d') {
		length.byte[1] = getch();
		length.byte[0] = getch();
		flags.eeprom = 0;
		if (getch() == 'E') flags.eeprom = 1;
		for (w=0;w<length.word;w++) {
			buff[w] = getch();	                        // Store data in buffer, can't keep up with serial data stream whilst programming pages
		}
		if (getch() == ' ') {
			if (flags.eeprom) {		                //Write to EEPROM one byte at a time
				address.word <<= 1;
				for(w=0;w<length.word;w++) {
#if defined(__AVR_ATmega168__)  || defined(__AVR_ATmega328P__)
					while(EECR & (1<<EEPE));
					EEAR = (uint16_t)(void *)address.word;
					EEDR = buff[w];
					EECR |= (1<<EEMPE);
					EECR |= (1<<EEPE);
#else
					eeprom_write_byte((void *)address.word,buff[w]);
#endif
					address.word++;
				}			
			}
			else {					        //Write to FLASH one page at a time
				if (address.byte[1]>127) address_high = 0x01;	//Only possible with m128, m256 will need 3rd address byte. FIXME
				else address_high = 0x00;

				address.word = address.word << 1;	        //address * 2 -> byte location
				/* if ((length.byte[0] & 0x01) == 0x01) length.word++;	//Even up an odd number of bytes */
				if ((length.byte[0] & 0x01)) length.word++;	//Even up an odd number of bytes
				cli();					//Disable interrupts, just to be sure
#if defined(EEPE)
				while(bit_is_set(EECR,EEPE));			//Wait for previous EEPROM writes to complete
#else
				while(bit_is_set(EECR,EEWE));			//Wait for previous EEPROM writes to complete
#endif
				asm volatile(
					 "clr	r17		\n\t"	//page_word_count
					 "lds	r30,address	\n\t"	//Address of FLASH location (in bytes)
					 "lds	r31,address+1	\n\t"
					 "ldi	r28,lo8(buff)	\n\t"	//Start of buffer array in RAM
					 "ldi	r29,hi8(buff)	\n\t"
					 "lds	r24,length	\n\t"	//Length of data to be written (in bytes)
					 "lds	r25,length+1	\n\t"
					 "length_loop:		\n\t"	//Main loop, repeat for number of words in block							 							 
					 "cpi	r17,0x00	\n\t"	//If page_word_count=0 then erase page
					 "brne	no_page_erase	\n\t"						 
					 "wait_spm1:		\n\t"
					 "lds	r16,%0		\n\t"	//Wait for previous spm to complete
					 "andi	r16,1           \n\t"
					 "cpi	r16,1           \n\t"
					 "breq	wait_spm1       \n\t"
					 "ldi	r16,0x03	\n\t"	//Erase page pointed to by Z
					 "sts	%0,r16		\n\t"
					 "spm			\n\t"							 

					 "wait_spm2:		\n\t"
					 "lds	r16,%0		\n\t"	//Wait for previous spm to complete
					 "andi	r16,1           \n\t"
					 "cpi	r16,1           \n\t"
					 "breq	wait_spm2       \n\t"									 

					 "ldi	r16,0x11	\n\t"	//Re-enable RWW section
					 "sts	%0,r16		\n\t"						 			 
					 "spm			\n\t"

					 "no_page_erase:		\n\t"							 
					 "ld	r0,Y+		\n\t"	//Write 2 bytes into page buffer
					 "ld	r1,Y+		\n\t"							 
								 
					 "wait_spm3:		\n\t"
					 "lds	r16,%0		\n\t"	//Wait for previous spm to complete
					 "andi	r16,1           \n\t"
					 "cpi	r16,1           \n\t"
					 "breq	wait_spm3       \n\t"
					 "ldi	r16,0x01	\n\t"	//Load r0,r1 into FLASH page buffer
					 "sts	%0,r16		\n\t"
					 "spm			\n\t"
								 
					 "inc	r17		\n\t"	//page_word_count++
					 "cpi r17,%1	        \n\t"
					 "brlo	same_page	\n\t"	//Still same page in FLASH
					 "write_page:		\n\t"
					 "clr	r17		\n\t"	//New page, write current one first
					 "wait_spm4:		\n\t"
					 "lds	r16,%0		\n\t"	//Wait for previous spm to complete
					 "andi	r16,1           \n\t"
					 "cpi	r16,1           \n\t"
					 "breq	wait_spm4       \n\t"
						 							 
					 "ldi	r16,0x05	\n\t"	//Write page pointed to by Z
					 "sts	%0,r16		\n\t"
					 "spm			\n\t"

					 "wait_spm5:		\n\t"
					 "lds	r16,%0		\n\t"	//Wait for previous spm to complete
					 "andi	r16,1           \n\t"
					 "cpi	r16,1           \n\t"
					 "breq	wait_spm5       \n\t"									 
					 "ldi	r16,0x11	\n\t"	//Re-enable RWW section
					 "sts	%0,r16		\n\t"						 			 
					 "spm			\n\t"					 		 

					 "same_page:		\n\t"							 
					 "adiw	r30,2		\n\t"	//Next word in FLASH
					 "sbiw	r24,2		\n\t"	//length-2
					 "breq	final_write	\n\t"	//Finished
					 "rjmp	length_loop	\n\t"
					 "final_write:		\n\t"
					 "cpi	r17,0		\n\t"
					 "breq	block_done	\n\t"
					 "adiw	r24,2		\n\t"	//length+2, fool above check on length after short page write
					 "rjmp	write_page	\n\t"
					 "block_done:		\n\t"
					 "clr	__zero_reg__	\n\t"	//restore zero register
#if defined(SPMCSR)
					 : "=m" (SPMCSR) : "M" (PAGE_SIZE) : "r0","r16","r17","r24","r25","r28","r29","r30","r31"
#else
					 : "=m" (SPMCR) : "M" (PAGE_SIZE) : "r0","r16","r17","r24","r25","r28","r29","r30","r31"
#endif
					 );
				/* Should really add a wait for RWW section to be enabled, don't actually need it since we never */
				/* exit the bootloader without a power cycle anyhow */
			}
			putch(0x14);
			putch(0x10);
		} else {
			if (++error_count == MAX_ERROR_COUNT)
				app_start();
		}		
	}


	/* Read memory block mode, length is big endian.  */
	else if(ch=='t') {
		length.byte[1] = getch();
		length.byte[0] = getch();

		address.word = address.word << 1;	        // address * 2 -> byte location
		if (getch() == 'E') flags.eeprom = 1;
		else flags.eeprom = 0;
		if (getch() == ' ') {		                // Command terminator
			putch(0x14);
			for (w=0;w < length.word;w++) {		        // Can handle odd and even lengths okay
				if (flags.eeprom) {	                        // Byte access EEPROM read
					putch(eeprom_read_byte((void *)address.word));
					address.word++;
				}
				else {

					if (!flags.rampz) putch(pgm_read_byte_near(address.word));
				
					/*
#if defined(__AVR_ATmega128__) || defined(__AVR_ATmega1280__)
					else putch(pgm_read_byte_far(address.word + 0x10000));
					// Hmmmm, yuck  FIXME when m256 arrvies
#endif
	*/				address.word++;
				}
			}
			putch(0x10);
		}
	}


	/* Get device signature bytes  */
	else if(ch=='u') {
		if (getch() == ' ') {
			putch(0x14);
			putch(SIG1);
			putch(SIG2);
			putch(SIG3);
			putch(0x10);
		} else {
			if (++error_count == MAX_ERROR_COUNT)
				app_start();
		}
	}


	/* Read oscillator calibration byte */
	else if(ch=='v') {
		byte_response(0x00);
	}


#if defined MONITOR 

	/* here come the extended monitor commands by Erik Lins */
	/* check for three times exclamation mark pressed */
	else if(ch=='!') {
		ch = getch();
		if(ch=='!') {
		ch = getch();
		if(ch=='!') {
			PGM_P welcome = "";
			uint8_t addrl, addrh;

			/* turn on LED */
			LED_DDR |= _BV(LED);
			LED_PORT &= ~_BV(LED);

			/* print a welcome message and command overview */
			for(i=0; welcome[i] != '\0'; ++i) {
				putch(welcome[i]);
			}

			/* test for valid commands */
			for(;;) {
				putch('\n');
				putch('\r');
				putch(':');
				putch(' ');

				ch = getch();
				putch(ch);

				/* toggle LED */
				if(ch == 't') {
					if(bit_is_set(LED_PIN,LED)) {
						LED_PORT &= ~_BV(LED);
						putch('1');
					} else {
						LED_PORT |= _BV(LED);
						putch('0');
					}
				} 

				/* read byte from address */
				else if(ch == 'r') {
					ch = getch(); putch(ch);
					addrh = gethex();
					addrl = gethex();
					putch('=');
					ch = *(uint8_t *)((addrh << 8) + addrl);
					puthex(ch);
				}

				/* write a byte to address  */
				else if(ch == 'w') {
					ch = getch(); putch(ch);
					addrh = gethex();
					addrl = gethex();
					ch = getch(); putch(ch);
					ch = gethex();
					*(uint8_t *)((addrh << 8) + addrl) = ch;
				}

				/* read from uart and echo back */
				else if(ch == 'u') {
					for(;;) {
						putch(getch());
					}
				}
#if defined(__AVR_ATmega128__) || defined(__AVR_ATmega1280__)
				/* external bus loop  */
				else if(ch == 'b') {
					putch('b');
					putch('u');
					putch('s');
					MCUCR = 0x80;
					XMCRA = 0;
					XMCRB = 0;
					extaddr = 0x1100;
					for(;;) {
						ch = *(volatile uint8_t *)extaddr;
						if(++extaddr == 0) {
							extaddr = 0x1100;
						}
					}
				}
#endif

				else if(ch == 'j') {
					app_start();
				}

			} /* end of monitor functions */

		}
		}
	}
	/* end of monitor */
#endif
	else if (++error_count == MAX_ERROR_COUNT) {
		app_start();
	}
	} /* end of forever loop */

}


char gethexnib(void) {
	char a;
	a = getch(); putch(a);
	if(a >= 'a') {
		return (a - 'a' + 0x0a);
	} else if(a >= '0') {
		return(a - '0');
	}
	return a;
}


char gethex(void) {
	return (gethexnib() << 4) + gethexnib();
}


void puthex(char ch) {
	char ah;

	ah = ch >> 4;
	if(ah >= 0x0a) {
		ah = ah - 0x0a + 'a';
	} else {
		ah += '0';
	}
	
	ch &= 0x0f;
	if(ch >= 0x0a) {
		ch = ch - 0x0a + 'a';
	} else {
		ch += '0';
	}
	
	putch(ah);
	putch(ch);
}


void putch(char ch)
{

	while (!(UCSRA & _BV(UDRE)));
	UDR = ch;
}


char getch(void)
{
	uint32_t count = 0;
	while(!(UCSRA & _BV(RXC))){
		
		count++;
		if (count > MAX_TIME_COUNT)
		flash_led(NUM_LED_FLASHES);
		        
		if (START_SW_ON != 0b001)
		{
			LED_PORT |= _BV(LED);
			app_start();

		}
	}
	return UDR;
}


void getNch(uint8_t count)
{
	while(count--) {		
		getch(); // need to handle time out
	}
}


void byte_response(uint8_t val)
{
	if (getch() == ' ') {
		putch(0x14);
		putch(val);
		putch(0x10);
	} else {
		if (++error_count == MAX_ERROR_COUNT)
			app_start();
	}
}


void nothing_response(void)
{
	if (getch() == ' ') {
		putch(0x14);
		putch(0x10);
	} else {
		if (++error_count == MAX_ERROR_COUNT)
			app_start();
	}
}

void flash_led(uint8_t count)
{
	while (count--) {
		LED_PORT |= _BV(LED);
		_delay_ms(200);
		LED_PORT &= ~_BV(LED);
		_delay_ms(200);
	}
}
/********************************************************/
//Control Funtion


void cable_remote_control_init(void)
{	
	DDRD |=  0b00010000; 		// Status LED	
	DDRD &= ~0b11000000;		// Dip SW	
	DDRB &= ~0b00000100;		// Start SW

//cable remocon
	DDRA &= ~0b10011000;		// CABLE REMOCON - Input
	DDRC &= ~0b10000000;		// CABLE REMOCON - Input

	PORTA |= 0b10011000;		// CABLE REMOCON - PullUP
	PORTC |= 0b10000000;		// CABLE REMOCON - PullUP

	DDRA |=  0b01000000; 		// CABLE REMOCON - Common GND
	DDRC |=  0b01000000; 		// CABLE REMOCON - Common GND


	PORTA &= ~0b01000000;		// CABLE REMOCON - LOW
	PORTC &= ~0b01000000; 		// CABLE REMOCON - LOW

}

void cable_remote_control_SELECT(void)
{
	
	/*
	if((DipSw1 == 0)&&(DipSw1 == 0))
	{
		//mode = 0;
	}
	if((DipSw1 == 1)&&(DipSw1 == 1))
	{
		mode = 1;
	}
	
	*/
}



void cable_remote_control_mode(void)
{
	/*
	
	int keyData1 = KEY1;
	int keyData2 = KEY2;
	int keyData3 = KEY3;
	int keyData4 = KEY4;
 
	if(keyData1 == 1)  keyData1 = 0x01;
	else if(keyData2 == 1)  keyData2 = 0x02;

	else if(keyData3 == 1)
	{
		KEY_COMMON2_ON;
		Delay_us(1);

		if(KEY3 == 1)
		{		
			keyData3 = 0x16;
		}
		else
		{
			keyData3 = 0x04;
		}

		KEY_COMMON2_OFF;
		Delay_us(1);
	}

	else if(keyData4 == 1)
	{
		KEY_COMMON2_ON;
		Delay_us(1);

		if(KEY4 == 1)
		{
			keyData4 = 0x32;
		}
		else
		{
			keyData4 = 0x08;
		}	

		KEY_COMMON2_OFF;
		Delay_us(1);
	}


	printf("%d\t",(keyData1));
	printf("%d\t",(keyData2));
	printf("%d\t",(keyData3));
	printf("%d\t",(keyData4));
	printf("%d\n\r",(keyData1 + keyData2 + keyData3 + keyData4));

//Putch(keyData1 + keyData2 + keyData3 + keyData4);

	Delay_ms(100);

	return keyData1 + keyData2 + keyData3 + keyData4;
	*/
}


void CableRemoconControl(void)
{
	/*
	int keyData = CableRemoconKey();

	if 		(keyData ==  CABLE_KEY_UP)		MotorControl(forward,commonSpeed);
	else if (keyData == CABLE_KEY_DOWN)			MotorControl(backward,commonSpeed);
	else if (keyData == CABLE_KEY_LEFT)			MotorControl(left,commonSpeed);
	else if (keyData == CABLE_KEY_RIGHT)			MotorControl(right,commonSpeed);
	else							MotorControl(stop,commonSpeed);
	
	if 		(keyData == CABLE_KEY_A)			
	{	
			servo_act_single(0,0,179);
			_delay_ms(100);
	}

	else if (keyData == CABLE_KEY_B)
	{			
			servo_act_single(0,0,90);
			_delay_ms(100);
	}
	*/
}




/********************************************************/


/* end of file ATmegaBOOT.c */
