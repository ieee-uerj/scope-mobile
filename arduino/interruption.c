#include <stdio.h>
#include <avr/interrupt.h>

#include "adc.h"
#include "hserial.h"
#include "global.h"

#define SIZE_ARRAY 101

void interruption_setup(void);
void interruption_start(void);
void interruption_stop(void);

uint8_t u8Value;
uint8_t u8Vector[SIZE_ARRAY];

char strValue[3];
volatile int counter = 0;
int j;

int main (void)
{
	
	adc_init();
	
	hs_init();
	
	hs_start(SERIAL_PORT, BAUD);
	interruption_setup();
	
	for(;;)
	{
		/*if (counter >= SIZE_ARRAY)
		{
			interruption_stop();
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
			interruption_start();
		}*/
		if (freeze)
		{
			Serial.write( (uint8_t *)ADCBuffer + ADCCounter, ADCBUFFERSIZE - ADCCounter );
			Serial.write( (uint8_t *)ADCBuffer, ADCCounter );
			wait = 0;
			freeze = 0;
		}
	}
	
	return 0;
}


void interruption_setup(void)
{
	//(target time) = (timer resolution) * (# timer counts + 1) -> # timer counts
    // initialize Timer1 48kHz
    cli();          // disable global interrupts
    
    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B
 
    // set compare match register to desired timer count:
    OCR1A = 40;
    //OCR1A = 15624;
			
    // turn on CTC mode:
    TCCR1B |= (1 << WGM12);
    
    // Set CS11 bits for 8 prescaler:
    //TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS11); 
    //TCCR1B |= (1 << CS12);
    
    // enable timer compare interrupt:
    TIMSK1 |= (1 << OCIE1A);
    
    sei();          // enable global interrupts  
}

void interruption_start(void)
{
  TIMSK1 |= (1 << OCIE1A);
}

void interruption_stop(void)
{
  TIMSK1 = 0;
}

ISR(TIMER1_COMPA_vect)
{
	//u8Vector[counter++] = adc_read(ANALOG_0);
	ADCBuffer[ADCCounter] = adc_read(ANALOG_0);

	ADCCounter = ( ADCCounter + 1 ) % ADCBUFFERSIZE;

	if ( wait )
	{
		if ( stopIndex == ADCCounter )
		{
			// Freeze situation
			// Disable ADC and stop Free Running Conversion Mode
			ADCSRA &= ~(1<<ADEN);

			freeze = 1;
		}
	}

}

ISR(ANALOG_COMP_vect)
{
	// Disable Analog Comparator interrupt
	cbi( ACSR,ACIE );

	wait = 1;
	stopIndex = ( ADCCounter + WAIT_DURATION ) % ADCBUFFERSIZE;
}

	