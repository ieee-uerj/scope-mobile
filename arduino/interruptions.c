#include <avr/interrupt.h>
/*
General setup for interruptions
*/

#include "interruptions.h"

void setupTimerInterruption(int timer_count)
{
	//(target time) = (timer resolution) * (# timer counts + 1) -> # timer counts
    // initialize Timer1 48kHz
    /* 
    Default values: 
    prescaler = 8
    timer resolution = 1/(16Mhz/8) = 0,5 us
    target time = 20us
    timer count = 40
    */
    cli();          // disable global interrupts
    
    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B
 
    // set compare match register to desired timer count:
    OCR1A = timer_count;
                        
    // turn on CTC mode:
    sbi(TCCR1B, WGM12);

    // prescaler = 8
    sbi(TCCR1B, CS11);

    // disable timer compare interrupt in initial state:
    TIMSK1 = 0;
    
    sei();          // enable global interrupts  
}

void startTimerInterruption(void)
{
  sbi(TIMSK1, OCIE1A);
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

void setupAnalogComparator(void)
{
  
    cli();          // disable global interrupts
    
    /*
        Switch on analog comparator power.
    */
    cbi(ACSR, ACD);

    /*
        Not using Bandgap voltage reference.
        Using AIN0 in positive input of comparator.
        See Page 247 of datasheet for more details.
    */
    sbi(ACSR, ACBG);

    /*AIN1 as negative input of comparator*/
    sbi(ADCSRA, ADEN);


    /*
        Everytime you change ACD bit, you MUST disable AC Interrupt.
        If you do not do this, an interrupt can occur.
        See Page 247 for more details.
    */
    cbi(ACSR, ACIE);

    /*
        Disable input capture function in Timer/Counter1
        to be triggered by AC. (Figure 22-1 on page 246)
    */
    cbi(ACSR, ACIC);

    /*
        These bits determine which comparator events that
        trigger the Analog Comparator interrupt.
        Rising edge in this case.
    */
    cbi(ACSR, ACIS1);
    cbi(ACSR, ACIS0);

    /*
        Disable digital input buffer from AIN0/1 to reduce power consumption.
    */
    sbi(DIDR1, AIN1D);
    sbi(DIDR1, AIN0D);

    /*
        Configure PortB direction - B5 is output
    */
    DDRB = 0x20;

    
    sei(); // enable global interrupts 

}

void startAnalogComparator(void)
{
    /* Enable Analog Comparator Interrupt */
    sbi(ACSR, ACIE);
}

void stopAnalogComparator(void)
{
    /* Disable Analog Comparator interrupt */
    cbi(ACSR, ACIE);
}