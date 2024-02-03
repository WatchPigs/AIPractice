#pragma once
#include "InteractableObject.h"

class ChargingStation : public InteractableObject
{
public:
	float size_;
	ofColor color_;

	ChargingStation(glm::vec2 position, float size, ofColor color);
	ChargingStation() = delete;

	void Draw();
};

