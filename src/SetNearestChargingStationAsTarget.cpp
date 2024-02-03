#include "SetNearestChargingStationAsTarget.h"

SetNearestChargingStationAsTarget::SetNearestChargingStationAsTarget(Blackboard* blackboard_jr) :
	Task(blackboard_jr)
{
}

bool SetNearestChargingStationAsTarget::Run()
{
	BlackboardJR* blackboard_jr = dynamic_cast<BlackboardJR*>(blackboard_);
	bool result = false;
	if (blackboard_jr == nullptr || blackboard_jr->in_cleaning_up_) return false;
	else
	{
		std::shared_lock<std::shared_mutex> lock_in_use(blackboard_jr->mtx_bb_in_use_);
		std::shared_lock<std::shared_mutex> lock_charging_stations_(blackboard_jr->mtx_charging_stations_, std::defer_lock);
		std::shared_lock<std::shared_mutex> lock_character_position(blackboard_jr->mtx_character_position_, std::defer_lock);

		std::set<ChargingStation*> charging_stations_;
		glm::vec2 character_position = glm::zero<glm::vec2>();

		while (isThreadRunning())
		{
			if (charging_stations_.size() == 0 && lock_charging_stations_.try_lock())
			{
				charging_stations_ = blackboard_jr->charging_stations_;
				lock_charging_stations_.unlock();
				break;
			}
		}
		while (isThreadRunning())
		{
			if (character_position == glm::zero<glm::vec2>() && lock_character_position.try_lock())
			{
				character_position = blackboard_jr->character_position_;
				lock_character_position.unlock();
				break;
			}
		}
		if (charging_stations_.size() > 0 && character_position != glm::zero<glm::vec2>())
		{
			blackboard_jr->target_ = Nearest(charging_stations_, character_position);
			result = true;
		}
	}
	return result;
}

InteractableObject* SetNearestChargingStationAsTarget::Nearest(std::set<ChargingStation*> charging_stations, glm::vec2 character_position)
{
	float nearest_distance = -1.0f;
	ChargingStation* nearest_charging_station = nullptr;

	for (ChargingStation* charging_station : charging_stations)
	{
		float distance = glm::length(charging_station->rigidbody_->position_ - character_position);
		if (nearest_distance == -1.0f || nearest_distance > distance)
		{
			nearest_distance = distance;
			nearest_charging_station = charging_station;
		}
	}
	return nearest_charging_station;
}
