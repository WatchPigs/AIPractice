#include "DetectFullPower.h"

DetectFullPower::DetectFullPower(Blackboard* blackboard_jr) :
	Task(blackboard_jr)
{

}

bool DetectFullPower::Run()
{
	BlackboardJR* blackboard_jr = dynamic_cast<BlackboardJR*>(blackboard_);
	bool result = false;
	if (blackboard_jr == nullptr || blackboard_jr->in_cleaning_up_) return false;
	else
	{
		std::shared_lock<std::shared_mutex> lock_in_use(blackboard_jr->mtx_bb_in_use_);
		result = blackboard_jr->power_ >= blackboard_jr->max_power_;
	}
	return result;
}
