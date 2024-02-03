#pragma once
#include "Blackboard.h"
#include <shared_mutex>

class BBTest : public Blackboard
{
public:
	int value_;
	std::shared_mutex mtx_;

	BBTest(int value);
};

