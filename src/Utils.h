#pragma once
#include "ofMain.h"

inline float OrientationToVec2(float current, glm::vec2 vector)
{
	if (glm::length(vector) > 0.01f)
	{
		return atan2(vector.y, vector.x);
	}
	else return current;
}

inline float RandomBinomial()
{
	return ofRandomuf() - ofRandomuf();
}

inline glm::vec2 AsVector(float orientation)
{
	return glm::rotate(glm::vec2(1.0f, 0.0f), orientation);
}

vector<string> split(const string& s, const char& seperator);