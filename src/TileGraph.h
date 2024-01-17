#pragma once
#include "Graph.h"
#include "TileNode.h"
#include "ofMain.h"
#include "glm/gtx/hash.hpp"
#include <map>

class TileGraph : public Graph
{
public:
	float tile_size_;
	glm::vec2 screen_size_;
	glm::ivec2 grid_size_;
	float default_cost_;

	TileGraph() = delete;
	TileGraph(float tile_size, glm::vec2 screen_size);
	~TileGraph();

	TileNode* GetNodeOnPosition(glm::vec2 position);
	glm::vec2 GetNodePosition(TileNode* node);
	
private:
	std::unordered_map<glm::ivec2, TileNode*> grid_position_to_node_map_;
};

