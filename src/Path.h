#pragma once
#include <vector>
#include "ofMain.h"

class Path
{
public:
	std::vector<glm::vec2> waypoints_;
	
	int GetNearestPointParam(glm::vec2 character_position, bool first_time, int last_point_param = 0, int look_ahead = 1);
	glm::vec2 GetPosition(int param);
	int GetTargetPointParamWithOffset(int current_param, float offset);
	static Path* CreatePath(std::vector<glm::vec2> waypoints_input, float maximum_interval);

private:
	Path();
	Path(std::vector<glm::vec2> waypoints);
};

