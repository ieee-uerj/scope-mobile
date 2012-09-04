/*
Functions' prototypes
*/
#ifndef __PROTOTYPES_H__		/* include guard */
#define __PROTOTYPES_H__


/* 	Initial setup of timer interruption    *
 *  Parameters:  nothing                   *
 *  Returns:     nothing                   */
void setupTimerInterruption();

/* 	Stop timer interruption	        *
 *  Parameters:  nothing            *
 *  Returns:     nothing            */
void stopTimerInterruption();

/* 	Start timer interruption		*
 *  Parameters:  nothing            *
 *  Returns:     nothing            */
void startTimerInterruption();

/* 	Initial setup of interruptions  *
 *  Parameters:  nothing            *
 *  Returns:     nothing            */
void setupADC(void);

/* 	Start ADC Interruption  		*
 *  Parameters:  nothing            *
 *  Returns:     nothing            */
void startADC( void );

/* 	Stop ADC Interruption 			*
 *  Parameters:  nothing            *
 *  Returns:     nothing            */
void stopADC( void );

#endif
