#pragma once
#include "ofMain.h"
#include "Rigidbody.h"

class InteractableObject
{
public:
	Rigidbody* rigidbody_;

	InteractableObject() = delete;
	InteractableObject(glm::vec2 position);

	virtual ~InteractableObject();
};

