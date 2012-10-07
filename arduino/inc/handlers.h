#ifndef __HANDLERS_H__		/* include guard */
#define __HANDLERS_H__

#ifdef OWNER
#undef OWNER
#endif
#include "global.h"

#include "adc.h"

#define _BV(n) (1 << n) /*_BV() is not standard and non portable.*/

#ifndef cbi
#define cbi(reg, bit) (_SFR_BYTE(reg) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(reg, bit) (_SFR_BYTE(reg) |= _BV(bit))
#endif

void timer_isr();
void comparator_isr();

#endif