#include "GraphNode.h"


GraphNode::GraphNode(int key) : _key{ key }, _visited{ false }, _component{ 0 }{}

int GraphNode::getKey() { return _key; }
void GraphNode::setKey(int key) { _key = key; }
bool GraphNode::getVisited() { return _visited; }
void GraphNode::setVisited(bool visited) { _visited = visited; }
void GraphNode::addEdge(edge e) { _edges.push_back(e); }
edge* GraphNode::getEdge(int n)
{
	if (_edges.size() != 0)
	{
		//for (std::vector<edge>::iterator it = _edges.begin(); it != _edges.end(); ++it)
		//{
		//	if (it->neighbour == n)
		//		return &*it;
		//}
		return &_edges[n];
	}
	return nullptr;
}
int GraphNode::getNumberOfEdges() { return _edges.size(); }
int GraphNode::getComponent() { return _component; }
void GraphNode::setComponent(int c) { _component = c; }