#include "Wander.h"

Wander::Wander(Blackboard* blackboard_jr) :
	Task(blackboard_jr)
{
	dynamic_wander_ = new DynamicWander();
}

Wander::~Wander()
{
	if (dynamic_wander_ != nullptr)
	{
		delete dynamic_wander_;
		dynamic_wander_ = nullptr;
	}
}

bool Wander::Run()
{
	BlackboardJR* blackboard_jr = dynamic_cast<BlackboardJR*>(blackboard_);
	bool result = false;
	if (blackboard_jr == nullptr || blackboard_jr->in_cleaning_up_) return false;

	dynamic_wander_->NewRequest(blackboard_jr->character_rb_, 8.0f, 48.0f, ofDegToRad(15.0f), 128.0f, ofDegToRad(360.0f), ofDegToRad(90.0f), ofDegToRad(2.0f), ofDegToRad(30.0f), 0.1f);
	std::function<DynamicSteeringOutput()> get_dynamic_steering = std::bind(&DynamicWander::GetSteering, dynamic_wander_);

	std::unique_lock<std::shared_mutex> lock_status_string(blackboard_jr->mtx_status_string_, std::defer_lock);

	bool set_status_string = false;

	while (isThreadRunning() && !set_status_string)
	{
		if (lock_status_string.try_lock())
		{
			blackboard_jr->status_string_ = "Wandering...";
			lock_status_string.unlock();
			set_status_string = true;
		}
	}

	bool registered_dynamic_wander = false;
	while (isThreadRunning())
	{
		if (!registered_dynamic_wander)
		{
			blackboard_jr->get_dynamic_steering_ = get_dynamic_steering;
			registered_dynamic_wander = true;
		}
	}

	// on terminated
	if (registered_dynamic_wander)
	{
		dynamic_wander_->arrived_ = true;
		blackboard_jr->get_dynamic_steering_ = nullptr;
		registered_dynamic_wander = false;
	}

	lock_status_string.lock();
	blackboard_jr->status_string_ = "";
	lock_status_string.unlock();
	set_status_string = false;

	return result;
}

