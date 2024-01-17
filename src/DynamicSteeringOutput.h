#pragma once
#include "ofMain.h"

struct DynamicSteeringOutput
{
	glm::vec2 linear = glm::zero<glm::vec2>();
	float angular = 0.0f;

	inline DynamicSteeringOutput& operator+=(const DynamicSteeringOutput& rhs)
	{
		linear += rhs.linear;
		angular += rhs.angular;
		return *this;
	}
	inline DynamicSteeringOutput operator+(const DynamicSteeringOutput& rhs)
	{
		return { linear + rhs.linear, angular + rhs.angular };
	}
	inline DynamicSteeringOutput operator*(const float& rhs)
	{
		return { linear * rhs, angular * rhs };
	}
	inline DynamicSteeringOutput operator/(const float& rhs)
	{
		return { linear / rhs, angular / rhs };
	}
};

