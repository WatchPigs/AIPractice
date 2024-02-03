#pragma once
#include <shared_mutex>
#include <atomic>
class Blackboard
{
public:

	std::shared_mutex mtx_bb_in_use_;
	std::atomic<bool> in_cleaning_up_;

	Blackboard();
	virtual ~Blackboard();

	// block until not in use;
	virtual void SafeCleanUp();
};

