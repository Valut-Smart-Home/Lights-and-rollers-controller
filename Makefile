MCU=atmega328
COMPILER_CONTAINER=avr-build
TARGET=main

build-compiler:
	docker build -t ${COMPILER_CONTAINER} compiler 

build:
	docker run -v  $(CURDIR):/code -w /code/src ${COMPILER_CONTAINER}

test:
	docker run -v $(CURDIR):/code -w /code/tests ${COMPILER_CONTAINER}

flash:
	avrdude -p ${MCU} -c usbasp -U flash:w:${TARGET}.hex:i -F -P usb
