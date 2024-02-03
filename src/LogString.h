#pragma once
#include "Task.h"
#include <string>

class LogString : public Task
{
public:
	std::string s_;
	LogString(std::string s);

protected:
	bool Run() override;
};


