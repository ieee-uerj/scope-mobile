#include <stdio.h>
#include <avr/interrupt.h>

#define OWNER
#include "global.h"

#include "interruptions.h"
#include "hserial.h"
#include "handlers.h"
#include "adc.h"

int j;
int liga = 0;

int main (int argc, char * argv[]) {

	counter = 0;
	stopIndex = -1;
	freeze = 0;

	DDRB = 0b00100000;
	setupAnalogComparator();
	sei();
	startAnalogComparator();

	
	setupADC();

	hs_init();
	
	hs_start(SERIAL_PORT, BAUD);
	setupTimerInterruption();
	
	for(;;)
	{
		/*if (freeze)
		{
			stopTimerInterruption();
			stopAnalogComparator();
			// hs_writeChar(SERIAL_PORT, 'A');
			hs_writeBuffer(SERIAL_PORT, u8Vector, SIZE_ARRAY);
			_delay_ms(100);
			counter = 0;
			stopIndex = -1;
			freeze = 0;
			startAnalogComparator();
			startTimerInterruption();
		}*/
	}

	return 0;
}

ISR(TIMER1_COMPA_vect)
{
    timer_isr();
}

ISR(ANALOG_COMP_vect)
{
	//comparator_isr();
	if bit_is_clear(ACSR, ACO){

		cbi(PORTB, PORTB5);
	}else{

		sbi(PORTB, PORTB5);
	}
}

	
