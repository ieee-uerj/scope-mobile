#ifndef __HANDLERS_H__		/* include guard */
#define __HANDLERS_H__

#ifdef OWNER
#undef OWNER
#endif
#include "global.h"

#include "adc.h"

void timer_isr();

#endif