#include "DetectTrash.h"

DetectTrash::DetectTrash(Blackboard* blackboard_jr) :
	Task(blackboard_jr)
{
}

bool DetectTrash::Run()
{
	BlackboardJR* blackboard_jr = dynamic_cast<BlackboardJR*>(blackboard_);
	bool result = false;
	if (blackboard_jr == nullptr || blackboard_jr->in_cleaning_up_) return false;
	else
	{
		std::shared_lock<std::shared_mutex> lock_in_use(blackboard_jr->mtx_bb_in_use_);
		std::shared_lock<std::shared_mutex> lock(blackboard_jr->mtx_trashes_, std::defer_lock);
		while (isThreadRunning())
		{
			if (lock.try_lock())
			{
				result = (blackboard_jr->trashes_.size() > 0);
				lock.unlock();
				break;
			}
		}
	}
	return result;
}
