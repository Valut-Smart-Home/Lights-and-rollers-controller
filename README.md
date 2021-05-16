# Valut Smart Home - Lights and rollers controller
## Description
Lights and rollers controller is used to control lights and rollers in home using Arduino module with external modules. The main idea is that controller can work without any connections to another devices. It read states of switches and write controll to lights and rollers modules.
## Technologies
- C++ 17
## Modules
### Main control unit
The main control unit is Arduino NANO module with AVR ATmega328P, with erased Arduino bootloader.
### Switches
All the switches are push buttons. Read modules are IO expanders based on PCF8574T chip. Buttons connect pins to ground.
### Light control
Main controll module is based on PCA9685 chip. Betwean it and LEDs are IRF520 based modules.
### Roller control
Rollers are controlled by relays modules, one relay for ON/OFF function, and second for direction switching. Relays are controlled by IO expanders based on PCF8574T chip.
### Roller state
Rollers are equiped in limit switches. To detect if roller is working are used ACS712 based module connected to AVRs analog inputs.
### Comunication
Comunication with main server is realised by MAX485 based module connected to main AVR's UART.
## Current functionality
Currently controller can set lights ON or OFF based on pushing switches. Controller can dim the light based on communication channels commands, and send state of switches. All functions are hard-coded.
## Planned functionality
- Dim the lights by switches
- Controll the rollers
- Programmed switch bechavior
- Svaing last state before power off and bring it back after power on
