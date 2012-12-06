#ifndef __PARSER_H_
#define __PARSER_H__

#ifdef OWNER
#undef OWNER
#endif

#include "global.h"

void parse(unsigned char command_buffer[MASSIVE_COMMAND_SIZE]);

#endif
