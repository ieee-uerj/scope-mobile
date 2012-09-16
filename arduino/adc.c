#include "adc.h"

// initialize adc
void adc_init(void)
{
    ADMUX = (1 << ADLAR)|(1 << REFS0); // Set 8 bits resolution and set AREF = AVcc - 5V  
    ADCSRA = (1 << ADEN)|(1 << ADPS2)|(0 << ADPS1)|(0 << ADPS0); // Set prescaler (16MHz/16 =  1000kHz) and enable ADC (ADEN)  - FAST ADC
}

// read adc value
uint8_t adc_read(uint8_t channel)
{
    channel &= 0b00000111;
    ADMUX = (ADMUX & 0xF8)|channel;     // Clears the bottom 3 bits before ORing
    ADCSRA |= (1 << ADSC); // Start convertion
    // wait for conversion to complete
    // ADSC becomes '0' again
    // till then, run loop continuously
    while(ADCSRA & (1 << ADSC));

    return (ADCH);
}
