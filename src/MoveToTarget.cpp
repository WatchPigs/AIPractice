#include "MoveToTarget.h"
#include "Utils.h"

MoveToTarget::MoveToTarget(Blackboard* blackboard_jr) :
	Task(blackboard_jr)
{
	dynamic_arrive_ = new DynamicArrive();
	kinematic_stop_ = new KinematicStop();
}

MoveToTarget::~MoveToTarget()
{
	if (dynamic_arrive_ != nullptr)
	{
		delete dynamic_arrive_;
		dynamic_arrive_ = nullptr;
	}
	if (kinematic_stop_ != nullptr)
	{
		delete kinematic_stop_;
		kinematic_stop_ = nullptr;
	}
}

bool MoveToTarget::Run()
{
	BlackboardJR* blackboard_jr = dynamic_cast<BlackboardJR*>(blackboard_);
	bool result = false;
	if (blackboard_jr == nullptr || blackboard_jr->in_cleaning_up_) return false;
	
	dynamic_arrive_->NewRequest(blackboard_jr->character_rb_, blackboard_jr->target_.load()->rigidbody_, 64.0f, 128.0f, 8.0f, 192.0f, 0.1f, 8.0f);
	std::function<DynamicSteeringOutput()> get_dynamic_steering = std::bind(&DynamicArrive::GetSteering, dynamic_arrive_);
	
	kinematic_stop_->NewRequest(blackboard_jr->character_rb_);
	std::function<KinematicSteeringOutput()> get_kinematic_steering = std::bind(&KinematicStop::GetSteering, kinematic_stop_);

	std::unique_lock<std::shared_mutex> lock_status_string(blackboard_jr->mtx_status_string_, std::defer_lock);

	bool registered_dynamic_arrive = false;
	bool set_status_string = false;
	while (isThreadRunning())
	{
		if (!registered_dynamic_arrive && !dynamic_arrive_->arrived_)
		{
			blackboard_jr->get_dynamic_steering_ = get_dynamic_steering;
			registered_dynamic_arrive = true;
		}
		if (registered_dynamic_arrive && !set_status_string && lock_status_string.try_lock())
		{
			const std::type_info& type = typeid(*blackboard_jr->target_.load());
			std::stringstream target_type_name_stream;
			target_type_name_stream << type.name();
			blackboard_jr->status_string_ = "Moving to nearest " + split(target_type_name_stream.str(), ' ')[1];
			lock_status_string.unlock();
			set_status_string = true;
		}
		if (registered_dynamic_arrive && dynamic_arrive_->arrived_)
		{
			blackboard_jr->get_dynamic_steering_ = nullptr;
			registered_dynamic_arrive = false;
			break;
		}
	}

	// on terminated
	if (registered_dynamic_arrive)
	{
		dynamic_arrive_->arrived_ = true;
		blackboard_jr->get_dynamic_steering_ = nullptr;
		registered_dynamic_arrive = false;
	}

	bool registered_kinematic_stop = false;
	while (isThreadRunning())
	{
		if (!registered_kinematic_stop && !kinematic_stop_->arrived_)
		{
			blackboard_jr->get_kinematic_steering_ = get_kinematic_steering;
			registered_kinematic_stop = true;
		}
		if (registered_kinematic_stop && kinematic_stop_->arrived_)
		{
			blackboard_jr->get_kinematic_steering_ = nullptr;
			registered_kinematic_stop = false;
			result = true;
			break;
		}
	}

	// on terminated
	if (registered_kinematic_stop)
	{
		kinematic_stop_->arrived_ = true;
		//lock_get_kinematic_steerings_.lock();
		blackboard_jr->get_kinematic_steering_ = nullptr;
		//lock_get_kinematic_steerings_.unlock();
		registered_kinematic_stop = false;
	}

	lock_status_string.lock();
	blackboard_jr->status_string_ = "";
	lock_status_string.unlock();
	set_status_string = false;
	
	return result;
}
