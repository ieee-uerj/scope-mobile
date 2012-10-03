/*
General setup for interruptions
*/

#include "interruptions.h"

void setupTimerInterruption(void)
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

void startTimerInterruption(void)
{
  TIMSK1 |= (1 << OCIE1A);
}

void stopTimerInterruption(void)
{
  TIMSK1 = 0;
}

// initialize adc
void setupADC()
{
    ADMUX = (1 << ADLAR)|(1 << REFS0); // Set 8 bits resolution and set AREF = AVcc - 5V  
    ADCSRA = (1 << ADEN)|(1 << ADPS2)|(0 << ADPS1)|(0 << ADPS0); // Set prescaler (16MHz/16 =  1000kHz) and enable ADC (ADEN)  - FAST ADC
}