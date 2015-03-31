#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <stack>
#include <list>
#include <algorithm>
#include <iostream>
#include "glm\glm.hpp"
#include "sprite.h"
#include "animotion.h"
#include "time.h"

class GraphNode;
struct Edge;

typedef std::vector<Edge> EdgeList;
typedef std::vector<GraphNode*> NodeList;

struct Edge
{
	GraphNode* a_Start;
	GraphNode* a_End;

	float a_Cost;
};
class GraphNode
{
public:
	GraphNode();
	GraphNode(int a_Num);
	void PrintNeigh();

	float gScore, fScore;
	bool lock = false;
	int data;
	int x, y;

	int	a_NodeNum;
	EdgeList a_Edge;
	bool a_Visited;
	GraphNode* LastNode;
	Sprite * sprite;
};
class Graph
{
public:
	Graph();
	Graph(unsigned int a_NodeCount);

	void AddNode(GraphNode* a_Node);
	void RemoveNode(GraphNode* a_Node);
	void resetVisited();
	void drawGrid();
	bool NodeCompareG(const GraphNode* left, const GraphNode* right);
	bool NodeComparef(const GraphNode* left, const GraphNode* right);
	void drawNodes();
	void generateNodes(int a_Row, int a_Col);
	std::vector<GraphNode*> returnPath();

	bool searchDFS(GraphNode* a_Start, GraphNode* a_End);
	bool searchDijkstra(GraphNode* a_Start, GraphNode* a_End);
	bool searchAStar(GraphNode* a_Start, GraphNode* a_End, float inAdmissible);
	bool searchThetaStar(GraphNode* a_Start, GraphNode* a_End, float inadmissible);
	Sprite * sprite;
	Sprite * visitedSprite;
	Sprite * player;

	GraphNode * lastStart;
	GraphNode * lastDestination;
	NodeList Node;

private:
	EdgeList edge;
	int NodeNumbers;
};

#endif
