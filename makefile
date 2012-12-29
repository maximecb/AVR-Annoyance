MCU = attiny85

CFLAGS = -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wall -std=gnu99

PROGRAMMER = usbasp

SRCS = main.c
OBJS = $(SRCS:.c=.o)

TARGET = avr

all: flash

# 8MHz internal oscillator
# Brown out protection disabled
fuse:
	sudo avrdude -c $(PROGRAMMER) -p $(MCU) -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m

build:
	avr-gcc $(CFLAGS) -mmcu=$(MCU) -c $(SRCS)
	avr-gcc $(CFLAGS) -mmcu=$(MCU) -o $(TARGET).elf $(OBJS)
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex

flash: build
	sudo avrdude -c $(PROGRAMMER) -p $(MCU) -U flash:w:$(TARGET).hex	

clean:
	rm *.o
	rm *.elf
	rm *.hex

