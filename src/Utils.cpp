#include "Utils.h"

//bool RaySegmentIntersection(glm::vec2 ray_origin, glm::vec2 ray_direction, glm::vec2 point1, glm::vec2 point2, float& distance_ratio)
//{
//	glm::vec2 v1 = ray_origin - point1;
//	glm::vec2 v2 = point2 - point1;
//	glm::vec2 v3 = glm::vec2(-ray_direction.y, ray_direction.x);
//
//	float dot = glm::dot(v2, v3);
//	if (abs(dot) < 0.001f) return false;
//
//	//float t1 = glm::cross(v2, v1) / dot;
//	float t1 = (v2.x * v1.y - v2.y * v1.x) / dot;
//	float t2 = glm::dot(v1, v3) / dot;
//
//	if (t1 >= 0.0f && t2 >= 0.0f && t2 <= 1.0f) 
//	{
//		distance_ratio = t1;
//		return true;
//	}
//
//	return false;
//}