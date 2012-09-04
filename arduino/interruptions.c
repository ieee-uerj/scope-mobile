/*********************************************************
This is the handle to interruptions. No matter what kind
of interruption you are dealing with, put its handler here.
**********************************************************/

#ifdef OWNER
#undef OWNER
#endif

#include <global.h>
#include <SoftwareSerial.h>

uint8_t low = 0x00;
uint8_t high = 0x00;
uint16_t digital = 0x0000;

ISR(TIMER1_COMPA_vect)
{
  intArray[counter++] = analogRead(A0);
}

ISR(ADC_vect)
{
	// When ADCL is read, the ADC Data Register is not updated until ADCH
	// is read. Consequently, if the result is left adjusted and no more
	// than 8-bit precision is required, it is sufficient to read ADCH.
	// Otherwise, ADCL must be read first, then ADCH.

	low = ADCL;
	high = ADCH;
	digital = (high << 8) + low;

	ADCBuffer[ADCCounter] = digital;

	ADCCounter = ( ADCCounter + 1 ) % ADCBUFFERSIZE;

	if ( (ADCCounter == 0 ) || (counter >= SIZE_ARRAY) ){ /* Has buffer reached the end
														  or reached the limit?
														  Time to flush the buffer!*/
		Serial.write( (uint16_t *)ADCBuffer, ADCBUFFERSIZE );
	}
}