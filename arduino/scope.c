#include <stdio.h>
#include <avr/interrupt.h>

#define OWNER
#include "global.h"

#include "interruptions.h"
#include "hserial.h"
#include "handlers.h"
#include "adc.h"

int main (int argc, char * argv[]) {

	counter = 0;
	freeze = 0;
	// stopIndex = -1;

	setupAnalogComparator();
	setupTimerInterruption();

	startAnalogComparator();	

	setupADC();

	hs_init();
	
	hs_start(SERIAL_PORT, BAUD);
	
	for(;;)
	{
		if (freeze)
		{
			hs_writeBuffer(SERIAL_PORT, u8Vector, SIZE_ARRAY);
			_delay_ms(100);
			counter = 0;
			// stopIndex = -1;
			startAnalogComparator();
			freeze = 0;

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

	
