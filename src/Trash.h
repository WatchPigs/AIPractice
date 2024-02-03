#pragma once
#include "InteractableObject.h"

class Trash : public InteractableObject
{
public:
	float radius_;
	ofColor color_;

	Trash(glm::vec2 position, float radius, ofColor color);
	Trash() = delete;

	void Draw();
};
