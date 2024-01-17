#pragma once

class Node
{
public:
	
	Node();
	virtual ~Node();

	enum NodeStatus
	{
		kUnvisited = 0,
		kOpen = 1,
		kClosed = 2,
		kPath = 3,
	};

	NodeStatus status;
};

