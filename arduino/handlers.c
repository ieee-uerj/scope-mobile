/*
Handlers to interruptions
*/

#include "handlers.h"

void timer_isr()
{
    u8Vector[counter++] = adc_read(ANALOG_0);
}