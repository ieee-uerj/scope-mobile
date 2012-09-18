#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <avr/io.h>
#include <util/delay.h>

#define ANALOG_0 0

#define SERIAL_PORT 0	
#define BAUD 57600

#define ADCBUFFERSIZE 1280
#define WAIT_DURATION 32

volatile uint8_t ADCBuffer[ADCBUFFERSIZE];
volatile int ADCCounter;
volatile int wait;
volatile int freeze;
volatile int stopIndex;

#endif