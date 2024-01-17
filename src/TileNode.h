#pragma once
#include "ofMain.h"
#include "Node.h"

class TileNode : public Node
{
public:
	glm::ivec2 grid_position_;

	TileNode() = delete;
	TileNode(glm::ivec2 grid_position);
	~TileNode();
};

