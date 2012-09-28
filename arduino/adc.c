#include "adc.h"

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
