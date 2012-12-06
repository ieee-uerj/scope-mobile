#include <avr/io.h>
#include <util/delay.h>

#ifdef OWNER
#define EXTERN
#else
#define EXTERN extern	/* declares external variables */
#endif

#define ADC_IN 1

#define SERIAL_PORT 0	
#define BAUD 57600

#define SIZE_ARRAY 500
#define WAIT_DURATION SIZE_ARRAY - 32

/*Massive Receiver API constants*/
#define MASSIVE_COMMAND_SIZE 6
#define MASSIVE_MAX_COMMAND_IDENTIFIER 1
#define MASSIVE_SEPARATE_CHAR '%'
#define MASSIVE_MAX_COMMAND_PARAMS 3

#define DEFAULT_TIMER_COUNT 40

EXTERN volatile int freeze;
EXTERN volatile int counter;
EXTERN uint8_t u8Value;
EXTERN uint8_t u8Vector[SIZE_ARRAY];
EXTERN volatile unsigned char command_buffer[MASSIVE_COMMAND_SIZE];