#include <stdio.h>
#include <avr/interrupt.h>

#define OWNER
#include "global.h"

#include "interruptions.h"
#include "hserial.h"
#include "handlers.h"
#include "adc.h"

int j;

int main (int argc, char * argv[]) {
	
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
			hs_writeBuffer(SERIAL_PORT, u8Vector, SIZE_ARRAY);
			_delay_ms(100);
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

	
