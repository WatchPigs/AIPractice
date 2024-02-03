#pragma once
#include "Task.h"

class Wait : public Task
{
public:
	int duration_;
	int max_terminate_time_;

	Wait(int duration, int max_terminate_time);
	Wait() = delete;

protected:
	bool Run() override;
};

