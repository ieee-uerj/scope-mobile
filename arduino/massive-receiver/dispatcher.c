#include <string.h>
#include <stdlib.h>

#include "dispatcher.h"
#include "commands.h"


void dispatch(char command_id[], char command_params[])
{

	if ( strcmp(command_id, "A") )
	{
		set_sampling_rate(atoi(command_params));
	}

}