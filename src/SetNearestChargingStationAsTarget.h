#pragma once
#include "Task.h"
#include "BlackboardJR.h"

class SetNearestChargingStationAsTarget : public Task
{
public:
	SetNearestChargingStationAsTarget(Blackboard* blackboard_jr);
	SetNearestChargingStationAsTarget() = delete;

protected:
	bool Run() override;

private:
	InteractableObject* Nearest(std::set<ChargingStation*> charging_stations, glm::vec2 character_position);
};

