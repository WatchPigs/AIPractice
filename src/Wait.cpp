#include "Wait.h"

Wait::Wait(int duration, int max_terminate_time) :
	duration_(duration), max_terminate_time_(max_terminate_time)
{
}

bool Wait::Run()
{
	for (int time = 0; time < duration_; time += max_terminate_time_)
	{
		if (!isThreadRunning()) return false;
		sleep(max_terminate_time_);
	}
	return true;
}
