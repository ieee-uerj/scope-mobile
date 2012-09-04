/*
This is the global header. If you want to declare a global variable, put it here.
The DEFINE OWNER macro is used to set the owner of global variables.
*/

#include <Arduino.h>

#ifndef __GLOBAL_H__	/* include guard */
#define __GLOBAL_H__

#ifdef OWNER
#define EXTERN
#else
#define EXTERN extern	/* declares external variables */
#endif

#define ADCBUFFERSIZE 1280
#define SIZE_ARRAY 101
#define BAUDRATE 115200

EXTERN volatile uint16_t ADCBuffer[ADCBUFFERSIZE];
EXTERN volatile int intArray[SIZE_ARRAY];
EXTERN volatile int counter;

#endif