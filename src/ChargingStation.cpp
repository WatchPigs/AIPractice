#include "ChargingStation.h"

ChargingStation::ChargingStation(glm::vec2 position, float size, ofColor color) :
	InteractableObject(position), size_(size), color_(color)
{
}

void ChargingStation::Draw()
{
	ofPushMatrix();

	ofTranslate(rigidbody_->position_);
	ofSetColor(color_);

	ofDrawRectangle(0.0f - size_ * 0.5f, 0.0f - size_ * 0.5f, size_, size_);

	ofPopMatrix();
}
