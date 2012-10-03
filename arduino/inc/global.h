#include <avr/io.h>
#include <util/delay.h>

#ifdef OWNER
#define EXTERN
#else
#define EXTERN extern	/* declares external variables */
#endif

#define ANALOG_0 0

#define SERIAL_PORT 0	
#define BAUD 57600

#define ADCBUFFERSIZE 1280
#define WAIT_DURATION 32

#define SIZE_ARRAY 101

EXTERN volatile uint8_t ADCBuffer[ADCBUFFERSIZE];
EXTERN volatile int ADCCounter;
EXTERN volatile int wait;
EXTERN volatile int freeze;
EXTERN volatile int stopIndex;
EXTERN volatile int counter;
EXTERN uint8_t u8Value;
EXTERN uint8_t u8Vector[SIZE_ARRAY];