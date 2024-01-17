#pragma once
#include "Rigidbody.h"

class DynamicSeek
{
public:
	Rigidbody* character_rb_;
	Rigidbody* target_rb_;

	float max_acceleration_;

	bool arrived_;

	DynamicSeek();
	virtual ~DynamicSeek();

	virtual void NewRequest(Rigidbody* character, Rigidbody* target, float max_acceleration);

	virtual DynamicSteeringOutput GetSteering();
};

