#include "CollisionDetector.h"

void CollisionDetector::AddLineSegment(glm::vec2 p1, glm::vec2 p2)
{
	line_segments_.push_back({p1, p2});
}

bool CollisionDetector::RaySegmentIntersection(glm::vec2 ray_origin, glm::vec2 ray_direction, glm::vec2 point1, glm::vec2 point2, float& distance_ratio)
{
	glm::vec2 v1 = ray_origin - point1;
	glm::vec2 v2 = point2 - point1;
	glm::vec2 v3 = glm::vec2(-ray_direction.y, ray_direction.x);

	float dot = glm::dot(v2, v3);
	if (abs(dot) < 0.001f) return false;

	//float t1 = glm::cross(v2, v1) / dot;
	float t1 = (v2.x * v1.y - v2.y * v1.x) / dot;
	float t2 = glm::dot(v1, v3) / dot;

	if (t1 >= 0.0f && t2 >= 0.0f && t2 <= 1.0f)
	{
		distance_ratio = t1;
		return true;
	}

	return false;
}
CollisionDetector::Collision CollisionDetector::GetCollision(glm::vec2 origin, glm::vec2 direction)
{
	bool collided = false;
	LineSegment first_line;
	float first_distance_ratio = -1.0f; // distance / length of ray

	for (int i = 0; i < 4; i++)
	{
		float distance_ratio;
		if (RaySegmentIntersection(origin, direction, line_segments_[i].p1, line_segments_[i].p2, distance_ratio) && distance_ratio <= 1.0f && (distance_ratio < first_distance_ratio || first_distance_ratio < 0.0f))
		{
			collided = true;
			first_line = line_segments_[i];
			first_distance_ratio = distance_ratio;
		}
	}
	glm::vec2 position = origin + direction * first_distance_ratio;
	glm::vec2 normal = glm::vec2(glm::normalize(first_line.p1 - first_line.p2).y, -glm::normalize(first_line.p1 - first_line.p2).x);
	if (glm::dot(direction, normal) > 0) normal = -normal;

	return {collided, position, normal};
}

