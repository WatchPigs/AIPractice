#include "DetectSufficientPower.h"

DetectSufficientPower::DetectSufficientPower(Blackboard* blackboard_jr) :
	Task(blackboard_jr)
{
}

bool DetectSufficientPower::Run()
{
	BlackboardJR* blackboard_jr = dynamic_cast<BlackboardJR*>(blackboard_);
	bool result = false;
	if (blackboard_jr == nullptr || blackboard_jr->in_cleaning_up_) return false;
	else
	{
		std::shared_lock<std::shared_mutex> lock_in_use(blackboard_jr->mtx_bb_in_use_);
		std::shared_lock<std::shared_mutex> lock_trashes(blackboard_jr->mtx_trashes_, std::defer_lock);

		std::unique_lock<std::shared_mutex> lock_notice_string(blackboard_jr->mtx_notice_string_, std::defer_lock);

		while (isThreadRunning())
		{
			if (lock_trashes.try_lock())
			{
				result = blackboard_jr->power_ >= blackboard_jr->trashes_.size();
				lock_trashes.unlock();
				break;
			}
		}

		while (isThreadRunning() && !result)
		{
			if (lock_notice_string.try_lock())
			{
				blackboard_jr->notice_string_ = "Insufficient power!";
				blackboard_jr->notice_time_ += 1000;
				lock_notice_string.unlock();
				break;
			}
		}
	}
	return result;
}
