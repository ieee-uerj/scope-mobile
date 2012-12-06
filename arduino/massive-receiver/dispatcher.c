#include "dispatcher.h"

void set_sampling_rate(int new_sr)
{
	setupTimerInterruption(new_sr);
}