MCU=atmega328
F_CPU=16000000UL
CFLAGS=-std=gnu++17 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
TARGET=main
SRCS=main.cc base/*.cc hardware/*.cc hwd_managment/*.cc

all:
	avr-g++ ${CFLAGS} -o ${TARGET}.bin ${SRCS}
	avr-objcopy -j .text -j .data -O ihex ${TARGET}.bin ../${TARGET}.hex
	rm ${TARGET}.bin