#include "PathfindingDijkstraDemo.h"
#include "DrawString.h"
#include "Dijkstra.h"

PathfindingDijkstraDemo::PathfindingDijkstraDemo() :
	tile_graph_(nullptr), start_node_(nullptr), end_node_(nullptr), dijkstra_thread_(nullptr), process_(kReady)
{
}

void PathfindingDijkstraDemo::Setup()
{
	tile_graph_ = new TileGraph(32, glm::vec2(ofGetWidth(), ofGetHeight()));
	dijkstra_thread_ = new DijkstraThread(5);
}

void PathfindingDijkstraDemo::Update()
{
	switch (process_)
	{
	case PathfindingDijkstraDemo::kReady:
		break;
	case PathfindingDijkstraDemo::kSetObstacles:
		break;
	case PathfindingDijkstraDemo::kSetStart:
		break;
	case PathfindingDijkstraDemo::kSetEnd:
		break;
	case PathfindingDijkstraDemo::kStartProcess:
		process_ = kProcessing;
		dijkstra_thread_->Init(tile_graph_, start_node_, end_node_);
		dijkstra_thread_->startThread();
		break;
	case PathfindingDijkstraDemo::kProcessing:
		if (dijkstra_thread_->finished_)
		{
			process_ = kFinished;
			SetPathNodes(dijkstra_thread_->result_);
		}
		break;
	case PathfindingDijkstraDemo::kFinished:
		break;
	default:
		break;
	}
}

void PathfindingDijkstraDemo::Exit()
{
	if (tile_graph_ != nullptr)
	{
		delete tile_graph_;
		tile_graph_ = nullptr;
	}
	if (start_node_ != nullptr) start_node_ = nullptr;
	if (end_node_ != nullptr) end_node_ = nullptr;
	if (dijkstra_thread_ != nullptr)
	{
		dijkstra_thread_->stopThread();
		delete dijkstra_thread_;
		dijkstra_thread_ = nullptr;
	}
}

void PathfindingDijkstraDemo::Draw()
{
	for (auto node : tile_graph_->nodes_)
	{
		TileNode* tile_node = dynamic_cast<TileNode*>(node);
		if (tile_node != nullptr)
		{
			ofPushMatrix();

			ofColor color;
			switch (tile_node->status)
			{
			case Node::kUnvisited:
				color = ofColor::white;
				color.a = 63;
				break;
			case Node::kOpen:
				color = ofColor::green;
				color.a = 127;
				break;
			case Node::kClosed:
				color = ofColor::green;
				color.a = 63;
				break;
			case Node::kPath:
				color = ofColor::red;
				break;
			default:
				break;
			}

			if (tile_node == start_node_) color = ofColor::brown;
			if (tile_node == end_node_) color = ofColor::orange;

			ofSetColor(color);

			ofTranslate(tile_graph_->GetNodePosition(tile_node));

			ofDrawRectangle(0.0f, 0.0f, tile_graph_->tile_size_, tile_graph_->tile_size_);

			ofPopMatrix();
		}
	}
	DrawStrings();
}

void PathfindingDijkstraDemo::SetPathNodes(std::list<Connection*> result)
{
	for (Connection* connection : result)
	{
		if (connection->from_node_ != start_node_) connection->from_node_->status = Node::kPath;
	}
}

void PathfindingDijkstraDemo::DrawStrings()
{
	switch (process_)
	{
	case PathfindingDijkstraDemo::kReady:
		break;
	case PathfindingDijkstraDemo::kSetObstacles:
		DrawString::Draw("Left click anywhere to set obstacles\nPress ENTER to finish this step", glm::vec2(ofGetWidth() * 0.5f, ofGetHeight() * 0.25f), DrawString::kHorizontalCenter, DrawString::VerticalAlign::kVerticalTop, ofColor::white);
		break;
	case PathfindingDijkstraDemo::kSetStart:
		DrawString::Draw("Left click anywhere to set start position", glm::vec2(ofGetWidth() * 0.5f, ofGetHeight() * 0.25f), DrawString::kHorizontalCenter, DrawString::VerticalAlign::kVerticalTop, ofColor::white);
		break;
	case PathfindingDijkstraDemo::kSetEnd:
		DrawString::Draw("Left click anywhere to set end position", glm::vec2(ofGetWidth() * 0.5f, ofGetHeight() * 0.25f), DrawString::kHorizontalCenter, DrawString::VerticalAlign::kVerticalTop, ofColor::white);
		break;
	case PathfindingDijkstraDemo::kStartProcess:
		break;
	case PathfindingDijkstraDemo::kProcessing:
		break;
	case PathfindingDijkstraDemo::kFinished:
		break;
	default:
		break;
	}
}

void PathfindingDijkstraDemo::keyPressed(int key)
{
	switch (process_)
	{
	case PathfindingDijkstraDemo::kReady:
		break;
	case PathfindingDijkstraDemo::kSetObstacles:
		if (key == OF_KEY_RETURN) process_ = kSetStart;
		break;
	case PathfindingDijkstraDemo::kSetStart:
		break;
	case PathfindingDijkstraDemo::kSetEnd:
		break;
	case PathfindingDijkstraDemo::kStartProcess:
		break;
	case PathfindingDijkstraDemo::kProcessing:
		break;
	case PathfindingDijkstraDemo::kFinished:
		break;
	default:
		break;
	}
}

void PathfindingDijkstraDemo::mousePressed(int x, int y, int button)
{
	if (button == 0)
	{
		glm::vec2 position = glm::vec2(static_cast<float>(x), static_cast<float>(y));
		TileNode* node = tile_graph_->GetNodeOnPosition(position);
		switch (process_)
		{
		case PathfindingDijkstraDemo::kReady:
			break;
		case PathfindingDijkstraDemo::kSetObstacles:
			if (node != nullptr) tile_graph_->RemoveNode(node);
			break;
		case PathfindingDijkstraDemo::kSetStart:
			if (node != nullptr)
			{
				start_node_ = node;
				process_ = kSetEnd;
			}
			break;
		case PathfindingDijkstraDemo::kSetEnd:
			if (node != nullptr && node != start_node_)
			{
				end_node_ = node;
				process_ = kStartProcess;
			}
			break;
		case PathfindingDijkstraDemo::kStartProcess:
			break;
		case PathfindingDijkstraDemo::kProcessing:
			break;
		case PathfindingDijkstraDemo::kFinished:
			break;
		default:
			break;
		}

	}
}

