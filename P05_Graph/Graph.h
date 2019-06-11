#pragma once
#include <vector>
#include <string>
#include "GraphNode.h"

struct gEdge
{
	int node1;
	int node2;
	int weight;
};

bool operator<(const gEdge& a, const gEdge& b);

class Graph
{
private:
	int _anzKnoten;
	bool _ger;
	bool _gew;
	std::vector<GraphNode*> _nodes;
	std::vector<gEdge> _gEdges;
	//int _components;

public:
	Graph();
	~Graph();
	bool init(std::string file);
	bool printAll();
	bool depthSearchRek(int startKey, bool reset = true, int component = 0);
	bool breadthSearchIter(int startKey);
	double prim(int startKey);
	double kruskal();
	int getAnzKnoten();

private:
	GraphNode* getNodeByKey(int key);
	void setAllUnvisited();
	bool checkVisited();
	void startDepthSearchRek(GraphNode* node, int component = 0);
	bool testChildComponent(GraphNode* node);
};
