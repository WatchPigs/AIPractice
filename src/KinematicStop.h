#pragma once
#include <atomic>
#include "Rigidbody.h"

class KinematicStop
{
public:
	Rigidbody* character_rb_;

	std::atomic<bool> arrived_;

	KinematicStop();

	void NewRequest(Rigidbody* character);

	KinematicSteeringOutput GetSteering();
};

