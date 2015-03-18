#include "graph.h"

Graph::Graph()
{

}

GraphNode::GraphNode()
{

}

bool NodeCompareG(const GraphNode* left, const GraphNode* right)
{
	return (left->gScore < right->gScore);
}

bool NodeComparef(const GraphNode* left, const GraphNode* right)
{
	return (left->fScore < right->fScore);
}

void Graph::AddNode(GraphNode* a_Node)
{
	Node.push_back(a_Node);
	Node.back()->a_NodeNum = NodeNumbers;
	NodeNumbers++;
}

void Graph::RemoveNode(GraphNode* a_Node)
{
	NodeList::iterator deleteTarget = Node.end();

	for (NodeList::iterator nodeIter = Node.begin(); nodeIter != Node.end(); nodeIter++)
	{
		if ((*nodeIter) == a_Node)
		{
			deleteTarget = nodeIter;
		}
		if ((*nodeIter)->a_NodeNum > a_Node->a_NodeNum)
		{
			((*nodeIter)->a_NodeNum -= 1);
		}

		EdgeList::iterator toDelete = (*nodeIter)->a_Edge.end();

		for (EdgeList::iterator edgeIter = (*nodeIter)->a_Edge.begin(); edgeIter != (*nodeIter)->a_Edge.end(); edgeIter++)
		{
			if ((*edgeIter).a_End == a_Node)
			{
				toDelete = edgeIter;
			}
		}
		if (toDelete != (*nodeIter)->a_Edge.end())
		{
			(*nodeIter)->a_Edge.erase(toDelete);
		}
	}

	if (deleteTarget != Node.end())
	{
		Node.erase(deleteTarget);
	}
	delete a_Node;
	NodeNumbers--;
}

void Graph::resetVisited()
{
	for (NodeList::iterator nodeIter = Node.begin(); nodeIter != Node.end(); nodeIter++)
	{
		(*nodeIter)->a_Visited = false;
		if ((*nodeIter)->lock == false)
		{
			(*nodeIter)->numbers = 0;
		}
		else
		{
			(*nodeIter)->numbers = 4;
		}
	}
}

bool Graph::searchDFS(GraphNode* a_Start, GraphNode* a_End)
{
	std::stack<GraphNode*> oNodeStack;
	oNodeStack.push(a_Start);

	while (!oNodeStack.empty())
	{
		GraphNode* pCurrent = oNodeStack.top();
		oNodeStack.pop();

		if (pCurrent->a_Visited == true)
		{
			continue;
		}
		pCurrent->a_Visited = true;

		if (pCurrent == a_End)
		{
			return true;
		}
		for (int i = 0; i < pCurrent->a_Edge.size(); ++i)
		{
			oNodeStack.push(pCurrent->a_Edge[i].a_End);
		}
	}
	return false;
}

bool Graph::searchDijkstra(GraphNode* a_Start, GraphNode* a_End)
{
	std::list<GraphNode*> NodeQueue;
	for (NodeList::iterator nodeIter = Node.begin(); nodeIter != Node.end(); nodeIter++)
	{
		(*nodeIter)->LastNode = NULL;
		(*nodeIter)->gScore = INFINITY;
	}
	NodeQueue.push_back(a_Start);
	a_Start->LastNode = NodeQueue.back();
	a_Start->gScore = 0;
	int checkCount = 0;
	while (!NodeQueue.empty())
	{
		GraphNode* Current = NodeQueue.front();
		NodeQueue.pop_front();
		if (Current == a_End)
		{
			GraphNode* Retrace = a_End;
			while (Retrace != a_Start)
			{
				Retrace = Retrace->LastNode;
			}
			resetVisited();
			return true;
		}
		for (int i = 0; i < Current->a_Edge.size(); i++)
		{
			if (Current->a_Edge[i].a_End->a_Visited == false)
			{
				NodeQueue.push_back(Current->a_Edge[i].a_End);
				Current->a_Edge[i].a_End->gScore = (Current->gScore + Current->a_Edge[i].a_Cost);
				Current->a_Edge[i].a_End->LastNode = Current;
			}
		}
		//NodeQueue.sort(NodeCompareG);
	}
	return false;
}

GraphNode::GraphNode(int a_Num)
{
	a_NodeNum = a_Num;
}

void GraphNode::PrintNeigh()
{
	for (int i = 0; i < a_Edge.size(); ++i)
	{
		std::cout << a_Edge[i].a_End->a_NodeNum << std::endl;
	}
}