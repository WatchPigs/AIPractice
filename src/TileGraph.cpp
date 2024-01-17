#include "TileGraph.h"

TileGraph::TileGraph(float tile_size, glm::vec2 screen_size) :
	Graph(), tile_size_(tile_size), screen_size_(screen_size), grid_size_(glm::ivec2(screen_size.x / tile_size, screen_size.y / tile_size)), default_cost_(1.0f)
{
	// Create nodes
	for (int tile_y = 0; tile_y < grid_size_.y; tile_y++)
	{
		for (int tile_x = 0; tile_x < grid_size_.x; tile_x++)
		{
			TileNode* node = new TileNode(glm::ivec2(tile_x, tile_y));
			AddNode(node);
			grid_position_to_node_map_.insert(std::pair<glm::ivec2, TileNode*>(glm::ivec2(tile_x, tile_y), node));
		}
	}

	// Create connections
	for (Node* node : nodes_)
	{
		TileNode* tile_node = dynamic_cast<TileNode*>(node);
		if (tile_node != nullptr)
		{
			if (tile_node->grid_position_.x > 0)
			{
				SetConnection(tile_node, grid_position_to_node_map_[glm::ivec2(tile_node->grid_position_.x - 1, tile_node->grid_position_.y)], default_cost_);
			}
			if (tile_node->grid_position_.x < grid_size_.x - 1)
			{
				SetConnection(tile_node, grid_position_to_node_map_[glm::ivec2(tile_node->grid_position_.x + 1, tile_node->grid_position_.y)], default_cost_);
			}
			if (tile_node->grid_position_.y > 0)
			{
				SetConnection(tile_node, grid_position_to_node_map_[glm::ivec2(tile_node->grid_position_.x, tile_node->grid_position_.y - 1)], default_cost_);
			}
			if (tile_node->grid_position_.y < grid_size_.y - 1)
			{
				SetConnection(tile_node, grid_position_to_node_map_[glm::ivec2(tile_node->grid_position_.x, tile_node->grid_position_.y + 1)], default_cost_);
			}
		}
	}
}

TileGraph::~TileGraph()
{
}

TileNode* TileGraph::GetNodeOnPosition(glm::vec2 position)
{
	glm::ivec2 grid_position = glm::ivec2(position.x / tile_size_, position.y / tile_size_);
	if (grid_position_to_node_map_.count(grid_position))
	{
		return grid_position_to_node_map_[grid_position];
	}
	else return nullptr;
}

glm::vec2 TileGraph::GetNodePosition(TileNode* node)
{
	return glm::vec2((node->grid_position_.x) * tile_size_, (node->grid_position_.y ) * tile_size_);
}
