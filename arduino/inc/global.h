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

#define SIZE_ARRAY 101
#define WAIT_DURATION SIZE_ARRAY - 32

EXTERN volatile int freeze;
EXTERN volatile int stopIndex;
EXTERN volatile int counter;
EXTERN uint8_t u8Value;
EXTERN uint8_t u8Vector[SIZE_ARRAY];