#ifndef __ADC_H_
#define __ADC_H__

#ifdef OWNER
#undef OWNER
#endif

#include "global.h"

uint8_t adc_read(uint8_t channel);

#endif
