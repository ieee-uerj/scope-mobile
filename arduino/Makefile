###############################################################################
###############################################################################
#### Scope Mobile 
####
#### Author: Renan Prata 										October 4, 2012
####
####
#### This makefile allows you to build the project from the command line
####
#### Instructions for using the makefile:
#### 
#### 1. Type "make" and press enter to compile/verify your program
#### 2. Check the USB port and change "PORT" value in makefile (/dev/*)
#### 3. Type "make upload-*" and press enter upload your program to the 
####    Arduino board. If you're using arduino UNO, type "make upload-uno"
###############################################################################
###############################################################################

#Compiler Settings
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

#MCU Settings
MCU = atmega328p
F_CPU = 16000000L
FORMAT = ihex

#Source Settings
SOURCE = scope.c adc.c hserial.c handlers.c interruptions.c
CFLAGS =  -Wp, -w -Os 
CINCS = -I./inc
BIN = bin/scope
HEX = hex/scope.hex
MKDIR_P = mkdir -p bin/ hex/
RM_RF = rm -rf bin/ hex/
	
#Upload Settings
AVRDUDE_PROGRAMMER = arduino
AVR_PORT = /dev/ttyUSB0
AVRDUDE_FLAGS = -F -V 
AVRDUDE_FLASH = -U flash:w:$(HEX)
UPLOAD_RATE_DUEMILANOVE = 57600
UPLOAD_RATE_UNO = 115200

all:
	$(MKDIR_P)
	$(CC) $(CFLAGS) -DF_CPU=$(F_CPU) $(CINCS) -mmcu=$(MCU) $(SOURCE) -o $(BIN)
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $(BIN) $(HEX)

upload-uno:
	$(AVRDUDE) $(AVRDUDE_FLAGS) -c $(AVRDUDE_PROGRAMMER) -p $(MCU) -P $(AVR_PORT) -b $(UPLOAD_RATE_UNO) $(AVRDUDE_FLASH)

upload-duemilanove:
	$(AVRDUDE) $(AVRDUDE_FLAGS) -c $(AVRDUDE_PROGRAMMER) -p $(MCU) -P $(AVR_PORT) -b $(UPLOAD_RATE_DUEMILANOVE) $(AVRDUDE_FLASH)

clean:
	$(RM_RF)