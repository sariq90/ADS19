#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

Graph::Graph() : _anzKnoten{ 0 }, _ger{ false }, _gew{ true }{}
Graph::~Graph()
{
	if (_nodes.size() != 0)
	{
		for (std::vector<GraphNode*>::iterator it = _nodes.begin(); it != _nodes.end(); ++it)
			delete *it;
	}
}
bool Graph::init(std::string path)
{
	std::ifstream file;
	file.open(path, std::ios_base::in);

	if (!file)
	{
		std::cout << "Cannot open file." << std::endl;
		return false;
	}
	else
	{
		std::string line;
		std::getline(file, line);
		std::istringstream iss(line);
		iss >> _anzKnoten; //Erste Zeile Auslesen

		//Alle Knoten anlegen
		for (int i = 0; i < _anzKnoten; i++)
		{
			GraphNode* gn = new GraphNode(i);
			_nodes.push_back(gn);
		}
		//Alle Kanten anlegen
		while (std::getline(file, line))
		{
			std::istringstream iss(line);
			int n1, n2, w;
			iss >> n1 >> n2 >> w;

			_nodes[n1]->addEdge(edge{ n2, w });
			_nodes[n2]->addEdge(edge{ n1, w });
			_gEdges.push_back(gEdge{ n1, n2, w });
		}
		//Komponenten zuteilen wenn Teilgraph
		if (_anzKnoten > 0 && !depthSearchRek(0))
		{
			int component = 0;
			for (int i = 0; i < _anzKnoten; ++i)
			{
				if (!_nodes[i]->getVisited())
				{
					++component;
					depthSearchRek(i, false, component);
				}
			}
			//_components = component+1;
		}
		setAllUnvisited();
		return true;
	}
	return false;
}

bool Graph::printAll()
{
	std::cout << std::endl;
	for (int i = 0; i < _anzKnoten; ++i)
	{
		std::cout << i;
		for (int j = 0; j < _nodes[i]->getNumberOfEdges(); ++j)
		{
			edge* e = _nodes[i]->getEdge(j);
			std::cout << " -> " << e->neighbour << " [" << e->weight << "]";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	return true;
}

bool Graph::depthSearchRek(int startKey, bool reset, int component)
{
	// Reset-toggle for component run
	if (reset)
		setAllUnvisited();
	GraphNode* sNode = getNodeByKey(startKey);
	if (!sNode)
		return false;
	startDepthSearchRek(getNodeByKey(startKey), component);
	return checkVisited();
}
bool Graph::breadthSearchIter(int startKey)
{
	setAllUnvisited();
	int key = startKey;
	std::queue<int> q;
	GraphNode* n = getNodeByKey(key);
	n->setVisited(true);
	q.push(key);

	while (!q.empty())
	{
		key = q.front();
		q.pop();
		n = getNodeByKey(key);
		for (int i = 0; i < n->getNumberOfEdges(); ++i)
		{
			key = n->getEdge(i)->neighbour;
			if (!getNodeByKey(key)->getVisited())
			{
				getNodeByKey(key)->setVisited(true);
				q.push(key);
			}
		}
	}
	return checkVisited();
}
double Graph::prim(int startKey)
{
	// check if graph is split
	//for (int i = 0; i < _anzKnoten; ++i)
	//{
	//	if (_nodes[i]->getComponent() != 0)
	//		return 0.0;
	//}
	std::vector<int> marked;
	std::vector<gEdge> mst;
	std::priority_queue<gEdge> pq;
	for (int i = 0; i < _anzKnoten; ++i)
		marked.push_back(i);
	for (int i = 0; i < _gEdges.size(); ++i)
	{
		if (_gEdges[i].node1 == startKey || _gEdges[i].node2 == startKey)
			pq.push(_gEdges[i]);
	}
	while (!pq.empty())
	{
		gEdge e = pq.top();
		pq.pop();
		int v = e.node1; int w = e.node2;
		if (marked[v] == startKey && marked[w] == startKey)
			continue;
		mst.push_back(e);
		if (marked[v] != startKey)
		{
			for (int i = 0; i < _gEdges.size(); ++i)
			{
				if (_gEdges[i].node1 == v || _gEdges[i].node2 == v)
					pq.push(_gEdges[i]);
			}
			marked[v] = (startKey);
		}
		if (marked[w] != startKey)
		{
			for (int i = 0; i < _gEdges.size(); ++i)
			{
				if (_gEdges[i].node1 == w || _gEdges[i].node2 == w)
					pq.push(_gEdges[i]);
			}
			marked[w] = (startKey);
		}
	}
	double sum = 0;
	for (int i = 0; i < mst.size(); ++i)
	{
		sum += mst[i].weight;
	}
	return sum;
}
double Graph::kruskal()
{
	std::vector<int> marked;
	std::vector<gEdge> mst;
	std::priority_queue<gEdge> pq;
	// number-flag nodes
	for (int i = 0; i < _anzKnoten; ++i)
		marked.push_back(i);

	// fill pq_heap
	for (int i = 0; i < _gEdges.size(); ++i)
	{
		//if (getNodeByKey(_gEdges[i].node1)->getComponent() == c)
		pq.push(_gEdges[i]);
	}
	while (!pq.empty())
	{
		gEdge e = pq.top();
		pq.pop();
		int v = e.node1; int w = e.node2;
		// for smallest edge, if subgraphs are not connected
		if (marked[v] != marked[w])
		{
			mst.push_back(e);
			int cmp = marked[w];
			// re-flag absorbed nodes
			for (int i = 0; i < _anzKnoten; ++i)
			{
				if (marked[i] == cmp)
					marked[i] = marked[v];
			}
		}
	}

	double sum = 0;
	for (int i = 0; i < mst.size(); ++i)
	{
		sum += mst[i].weight;
	}
	return sum;
}

int Graph::getAnzKnoten() { return _anzKnoten; }

GraphNode* Graph::getNodeByKey(int key)
{
	if (key >= _anzKnoten)
		return nullptr;
	return _nodes[key];
}

void Graph::setAllUnvisited()
{
	for (int i = 0; i < _anzKnoten; ++i)
		_nodes[i]->setVisited(false);
}

bool Graph::checkVisited()
{
	for (int i = 0; i < _anzKnoten; ++i)
	{
		if (!_nodes[i]->getVisited())
			return false;
	}
	return true;
}

void Graph::startDepthSearchRek(GraphNode* node, int component)
{
	node->setVisited(true);
	// Set component if graph is split
	if (component != 0)
		node->setComponent(component);
	for (int i = 0; i < node->getNumberOfEdges(); ++i)
	{
		int nKey = node->getEdge(i)->neighbour;
		GraphNode* nNode = getNodeByKey(nKey);
		if (!nNode->getVisited())
			startDepthSearchRek(nNode, component);
	}
}
bool Graph::testChildComponent(GraphNode* node)
{
	return true;
}
bool operator<(const gEdge& a, const gEdge& b)
{
	return a.weight > b.weight;
}