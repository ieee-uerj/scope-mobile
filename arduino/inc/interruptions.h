/*
Interruption Functions' prototypes
*/
#ifndef __INTERRUPTIONS_H__		/* include guard */
#define __INTERRUPTIONS_H__

#ifdef OWNER
#undef OWNER
#endif

#include <avr/interrupt.h>
#include "global.h"

#define _BV(n) (1 << n) /*_BV() is not standard and non portable.*/

#ifndef cbi
#define cbi(reg, bit) (_SFR_BYTE(reg) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(reg, bit) (_SFR_BYTE(reg) |= _BV(bit))
#endif

/* 	Initial setup of timer interruption    *
 *  Parameters:  nothing                   *
 *  Returns:     nothing                   */
void setupTimerInterruption();

/* 	Start timer interruption		*
 *  Parameters:  nothing            *
 *  Returns:     nothing            */
void startTimerInterruption();

/* 	Stop timer interruption	        *
 *  Parameters:  nothing            *
 *  Returns:     nothing            */
void stopTimerInterruption();

/* 	Initial setup of interruptions  *
 *  Parameters:  nothing            *
 *  Returns:     nothing            */
void setupADC();

/* 	Start ADC Interruption  		*
 *  Parameters:  nothing            *
 *  Returns:     nothing            */
void startADC();

/* 	Stop ADC Interruption 			*
 *  Parameters:  nothing            *
 *  Returns:     nothing            */
void stopADC();

/* 	Initial setup of Analog Comparator *
 *  Parameters:  nothing               *
 *  Returns:     nothing               */
void setupAnalogComparator();

#endif
