MCU=atmega328
F_CPU=16000000UL
CC=avr-g++
OBJCOPY=avr-objcopy
CFLAGS=-std=gnu++17 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
TARGET=main
SRCS=main.cpp programTimerModule.cpp twiControlModule.cpp uartControlModule.cpp simpleManager.cpp

all:
	${CC} ${CFLAGS} -o ${TARGET}.bin ${SRCS}
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex

flash:
	avrdude -p ${MCU} -c usbasp -U flash:w:${TARGET}.hex:i -F -P usb

clean:
	rm -f *.bin *.hex
