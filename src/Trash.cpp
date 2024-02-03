#include "Trash.h"

Trash::Trash(glm::vec2 position, float radius, ofColor color) :
	InteractableObject(position), radius_(radius), color_(color)
{
}

void Trash::Draw()
{
	ofPushMatrix();

	ofTranslate(rigidbody_->position_);
	ofSetColor(color_);

	ofDrawCircle(0, 0, radius_);

	ofPopMatrix();
}
