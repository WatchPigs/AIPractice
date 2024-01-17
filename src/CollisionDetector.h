#pragma once
#include "ofMain.h"
#include <vector>

class CollisionDetector
{
public:
	
	struct LineSegment
	{
		glm::vec2 p1;
		glm::vec2 p2;
	};
	
	std::vector<LineSegment> line_segments_;

	struct Collision
	{
		bool collided = false;
		glm::vec2 position = glm::zero<glm::vec2>();
		glm::vec2 normal = glm::zero<glm::vec2>();
	};

	void AddLineSegment(glm::vec2 p1, glm::vec2 p2);

	bool RaySegmentIntersection(glm::vec2 ray_origin, glm::vec2 ray_direction, glm::vec2 point1, glm::vec2 point2, float& distance_ratio);

	Collision GetCollision(glm::vec2 origin, glm::vec2 direction);
};

