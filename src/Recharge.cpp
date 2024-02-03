#include "Recharge.h"

Recharge::Recharge(Blackboard* blackboard_jr, int duration, int max_terminate_time) :
	Task(blackboard_jr), duration_(duration), max_terminate_time_(max_terminate_time)
{
}

bool Recharge::Run()
{
	BlackboardJR* blackboard_jr = dynamic_cast<BlackboardJR*>(blackboard_);
	bool result = false;
	if (blackboard_jr == nullptr || blackboard_jr->in_cleaning_up_) return false;
	else
	{
		std::shared_lock<std::shared_mutex> lock_in_use(blackboard_jr->mtx_bb_in_use_);

		std::unique_lock<std::shared_mutex> lock_status_string(blackboard_jr->mtx_status_string_, std::defer_lock);

		bool set_status_string = false;

		while (isThreadRunning() && !set_status_string)
		{
			if (lock_status_string.try_lock())
			{
				blackboard_jr->status_string_ = "Recharging...";
				lock_status_string.unlock();
				set_status_string = true;
			}
		}

		for (int time = 0; time < duration_; time += max_terminate_time_)
		{
			if (!isThreadRunning()) return false;
			sleep(max_terminate_time_);
		}

		ChargingStation* charging_station = dynamic_cast<ChargingStation*>(blackboard_jr->target_.load());
		if (charging_station == nullptr) return false;
		else
		{
			while (isThreadRunning())
			{
				blackboard_jr->target_ = nullptr;
				if (blackboard_jr->power_ >= blackboard_jr->max_power_) return false;
				blackboard_jr->power_++;
				result = true;
				break;
			}
		}

		lock_status_string.lock();
		blackboard_jr->status_string_ = "";
		lock_status_string.unlock();
		set_status_string = false;
	}
	return result;
}
