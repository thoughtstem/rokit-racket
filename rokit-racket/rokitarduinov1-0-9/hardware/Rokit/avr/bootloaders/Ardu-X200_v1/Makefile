TARGET = atmega128

PROGRAM    = ARDU-X200

OBJ        = $(PROGRAM).o
OPTIMIZE   = -O2

CC         = avr-gcc

# Override is only needed by avr-lib build system.

override CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) -DF_CPU=$(AVR_FREQ) $(DEFS)
override LDFLAGS       = -Wl,$(LDSECTION)

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump

atmega128: MCU_TARGET = atmega128
atmega128: CFLAGS += '-DMAX_TIME_COUNT=F_CPU>>4' '-DNUM_LED_FLASHES=1' -DBAUD_RATE=19200
atmega128: AVR_FREQ = 16000000L
atmega128: LDSECTION  = --section-start=.text=0x1F000
atmega128: HFUSE = D9
atmega128: LFUSE = BE
atmega128: EFUSE = FF
atmega128: $ ARDU-X200.hex


%.elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o *.elf *.lst *.map *.sym *.lss *.eep *.srec *.bin *.hex

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@
	
