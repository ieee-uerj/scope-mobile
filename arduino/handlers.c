/*
Handlers to interruptions
*/

#include "handlers.h"
#include "interruptions.h"

void timer_isr()
{
    
    u8Vector[counter] = adc_read(ADC_IN);

	if (++counter >= SIZE_ARRAY) 
	{
		// counter = 0;
		freeze = 1;
		cbi(PORTB, PORTB5);
		stopTimerInterruption();
	}

 	//if (stopIndex == counter)
	// {
	// 	//cbi(ADCSRA, ADEN);
	// 	freeze = 1;
	// }
}

void comparator_isr()
{

	/*
		Disable Analog Comparator interrupt
	*/
	stopAnalogComparator();
		
	sbi(PORTB, PORTB5);
	// stopIndex = ( counter + WAIT_DURATION ) % SIZE_ARRAY;
	
	startTimerInterruption();
}