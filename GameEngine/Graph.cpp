#include "graph.h"

Graph::Graph()
{

}

GraphNode::GraphNode()
{

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