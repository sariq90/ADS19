#pragma once
#include <vector>

struct edge
{
	int neighbour;
	int weight;
};

class GraphNode
{
private:
	int _key;
	std::vector<edge> _edges;
	bool _visited;
	int _component;

public:
	GraphNode(int key);
	int getKey();
	void setKey(int);
	bool getVisited();
	void setVisited(bool);
	void addEdge(edge);
	edge* getEdge(int);
	int getNumberOfEdges();
	int getComponent();
	void setComponent(int);
};

