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
		freeze = 1;
		// cbi(PORTB, PORTB5);
		stopTimerInterruption();
	}
}

void comparator_isr()
{

	/*
		Disable Analog Comparator interrupt
	*/
	stopAnalogComparator();
		
	// sbi(PORTB, PORTB5);
	
	startTimerInterruption();
}