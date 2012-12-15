#ifndef __DISPATCHER_H__		/* include guard */
#define __DISPATCHER_H__

#ifdef OWNER
#undef OWNER
#endif
#include "global.h"

void dispatch(char command_id[], char command_params[]);

#endif