#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#define OWNER
#include "global.h"

#include "interruptions.h"
#include "hserial.h"
#include "handlers.h"
#include "adc.h"

int j;
static char strValue[3] = "";

int main (void) {
	
	setupADC();

	hs_init();
	
	hs_start(SERIAL_PORT, BAUD);
	setupTimerInterruption();
	
	for(;;)
	{
		if (counter >= SIZE_ARRAY)
		{
			stopTimerInterruption();
			hs_writeChar(SERIAL_PORT, 'A');
			hs_writeChar(SERIAL_PORT,'%');
			for (j = 0; j < SIZE_ARRAY; j++)
			{
				sprintf(strValue, "%d", u8Vector[j]);
				hs_writeStr(SERIAL_PORT,strValue);
				hs_writeChar(SERIAL_PORT, '%');
				_delay_ms(40);
			} 
			for (j = 0; j < SIZE_ARRAY; j++)
			{
				u8Vector[j] = 0; 
			}
			counter = 0;
			startTimerInterruption();
		}
	}

	return 0;
}

ISR(TIMER1_COMPA_vect)
{
    timer_isr();
}

	