/*
Handlers to interruptions
*/

#include "handlers.h"

void timer_isr()
{
	if (++counter >= SIZE_ARRAY) counter = 0;
    u8Vector[counter] = adc_read(ANALOG_0);

    if (stopIndex == counter)
	{
		cbi(ADCSRA, ADEN);
		freeze = 1;
	}
}

void comparator_isr()
{
	/*
		Disable Analog Comparator interrupt
	*/
	cbi(ACSR, ACIE);
	sbi(PORTB, PORTB5);
	stopIndex = ( counter + WAIT_DURATION ) % SIZE_ARRAY;
}