#include "Path.h"

int Path::GetNearestPointParam(glm::vec2 character_position, bool first_time, int last_point_param /*= 0*/, int look_ahead /*= 1*/)
{
	if (first_time)
	{
		float nearest_distance = -1.0f;
		int nearest_point_param = last_point_param;
		for (int i = 0; i < waypoints_.size(); i++)
		{
			if (nearest_distance < 0.0f || glm::length(waypoints_[i] - character_position) < nearest_distance)
			{
				nearest_point_param = i;
				nearest_distance = glm::length(waypoints_[i] - character_position);
			}
		}
		return nearest_point_param;
	}

	else
	{
		if (last_point_param == waypoints_.size() - 1) return last_point_param;

		std::vector<int> checkers;

		for (int i = 1; i <= look_ahead; i++)
		{
			checkers.push_back(last_point_param + i);
			if (checkers.back() == waypoints_.size() - 1) break;
		}

		float nearest_distance = glm::length(waypoints_[last_point_param] - character_position);
		int nearest_point_param = last_point_param;

		for (int param : checkers)
		{
			if (glm::length(waypoints_[param] - character_position) < nearest_distance)
			{
				nearest_point_param = param;
				nearest_distance = glm::length(waypoints_[param] - character_position);
			}
		}
		return nearest_point_param;
	}
}

glm::vec2 Path::GetPosition(int param)
{
	if (param >= 0 && param < waypoints_.size())
	{
		return waypoints_[param];
	}
	else
	{
		ofLog(OF_LOG_NOTICE, "Wrong param on getting position");
		return glm::zero<glm::vec2>();
	}
}

int Path::GetTargetPointParamWithOffset(int current_param, float offset)
{
	int target_param = current_param;
	if (offset >= 0.0f)
	{
		float distance = 0.0f;
		while (distance < offset && target_param < waypoints_.size() - 1)
		{
			distance += glm::length(GetPosition(target_param + 1) - GetPosition(target_param));
			target_param++;
		}
		return target_param;
	}
	else
	{
		float distance = 0.0f;
		while (distance < (-offset) && target_param > 0)
		{
			distance += glm::length(GetPosition(target_param - 1) - GetPosition(target_param));
			target_param--;
		}
		return target_param;
	}
}

Path* Path::CreatePath(std::vector<glm::vec2> waypoints_input, float maximum_interval)
{
	Path* path = new Path();
	glm::vec2 last_waypoint = glm::zero<glm::vec2>();
	for (glm::vec2 waypoint_input : waypoints_input)
	{
		if (last_waypoint != glm::zero<glm::vec2>())
		{
			float lenth_to_last = glm::length(waypoint_input - last_waypoint);
			if (lenth_to_last > maximum_interval)
			{
				int additional_waypoints_amount = lenth_to_last / maximum_interval;
				if (fmod(lenth_to_last, maximum_interval) == 0.0f) additional_waypoints_amount -= 1;
				glm::vec2 direction = glm::normalize(waypoint_input - last_waypoint);
				direction *= maximum_interval;
				for (int i = 1; i <= additional_waypoints_amount; i++)
				{
					path->waypoints_.push_back(last_waypoint + i * direction);
				}
			}
		}
		path->waypoints_.push_back(waypoint_input);
		last_waypoint = waypoint_input;
	}
	return path;
}

Path::Path()
{
	waypoints_ = std::vector<glm::vec2>();
}

Path::Path(std::vector<glm::vec2> waypoints) :
	waypoints_(waypoints)
{
}
