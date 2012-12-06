#include "parser.h"

void parse(unsigned char command_buffer[MASSIVE_COMMAND_SIZE])
{
	int i, j, k;
	i, j, k = 0;
	
	char command_id[MASSIVE_MAX_COMMAND_IDENTIFIER] = {'0'};
	char command_params[MASSIVE_MAX_COMMAND_PARAMS] = {'0'};

	if (command_buffer[0] == MASSIVE_SEPARATE_CHAR) /*Is a valid command, i.e., starts with MASSIVE_SEPARATE_CHAR ?*/
	{
		for (i=1; i<MASSIVE_COMMAND_SIZE; i++)
		{
			/*Parse valid command id*/
			if (command_buffer[i] != MASSIVE_SEPARATE_CHAR)
			{
				command_id[j] = command_buffer[i];
				j++;
			}else{
				break;
			}
		}

		/*Parse valid command params*/
		j = 0;
		for (i=i+1; i<MASSIVE_COMMAND_SIZE; i++)
		{
			command_params[j] = command_buffer[i];
			j++;
		}
	}
}