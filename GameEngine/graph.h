#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <stack>
#include <list>
#include <iostream>
#include "sprite.h"
#include "animotion.h"

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

	int	a_NodeNum;
	EdgeList a_Edge;
	bool a_Visited;
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

	bool searchDFS(GraphNode* a_Start, GraphNode* a_End);
	Sprite * sprite;

private:
	
	NodeList Node;
	int NodeNumbers;
};

#endif
