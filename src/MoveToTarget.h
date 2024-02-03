#pragma once
#include "Task.h"
#include "BlackboardJR.h"
#include "DynamicArrive.h"
#include "KinematicStop.h"

class MoveToTarget : public Task
{
public:
	DynamicArrive* dynamic_arrive_;
	KinematicStop* kinematic_stop_;

	MoveToTarget(Blackboard* blackboard_jr);
	MoveToTarget() = delete;
	~MoveToTarget();

protected:
	bool Run() override;
};

