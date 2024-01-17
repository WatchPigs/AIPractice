#include "Connection.h"

Connection::Connection(Node* from_node, Node* to_node, float cost) :
	from_node_(from_node), to_node_(to_node), cost_(cost)
{
}
