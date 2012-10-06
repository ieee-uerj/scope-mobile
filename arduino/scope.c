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

	counter = 0;
	stopIndex = -1;
	freeze = 0;
	
	setupADC();

	hs_init();
	
	hs_start(SERIAL_PORT, BAUD);
	setupTimerInterruption();

	setupAnalogComparator();
	startAnalogComparator();
	
	for(;;)
	{
		if (freeze)
		{
			stopTimerInterruption();
			stopAnalogComparator();
			hs_writeChar(SERIAL_PORT, 'A');
			hs_writeBuffer(SERIAL_PORT, u8Vector, SIZE_ARRAY);
			counter = 0;
			stopIndex = -1;
			freeze = 0;
			startAnalogComparator();
			startTimerInterruption();
		}
	}

	return 0;
}

ISR(TIMER1_COMPA_vect)
{
    timer_isr();
}

ISR(ANALOG_COMP_vect)
{
	comparator_isr();
}

	
