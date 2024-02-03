#include "InteractableObject.h"

InteractableObject::InteractableObject(glm::vec2 position)
{
	rigidbody_ = new Rigidbody();
	rigidbody_->position_ = position;
}

InteractableObject::~InteractableObject()
{
	if (rigidbody_ != nullptr)
	{
		delete rigidbody_;
		rigidbody_ = nullptr;
	}
}
