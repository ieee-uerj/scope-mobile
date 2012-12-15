#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include <stdio.h>

#ifdef OWNER
#undef OWNER
#endif
#include "interruptions.h"

void set_sampling_rate(int new_sr);

#endif