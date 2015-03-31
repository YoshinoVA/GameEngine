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
			(*nodeIter)->data = 0;
		}
		else
		{
			(*nodeIter)->data = 4;
		}
	}
}

void Graph::drawNodes()
{
	for (int i = 0; i < Node.size(); i++)
	{
		if (Node[i]->a_Visited)
		{
			visitedSprite->x = Node[i]->x;
			visitedSprite->y = Node[i]->y;

			visitedSprite->Draw();
		}
		else
		{
			sprite->x = Node[i]->x;
			sprite->y = Node[i]->y;

			sprite->Draw();
		}
	}
}

void Graph::generateNodes(int Rows, int Cols)
{
	int NodeNum = 0;

	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			Node.push_back(new GraphNode());
			Node.back()->x = i * 64;
			Node.back()->y = j * 64;
			Node.back()->a_NodeNum = NodeNum;
			NodeNum += 1;
		}
	}
	Edge newEdge;
	for (int i = 0; i < Node.size(); i++)
	{
		//check top side
		if (i % Cols != 0)
		{
			newEdge.a_Start = Node[i];
			newEdge.a_End = Node[i-1];
			newEdge.a_Cost = 1;
			Node[i]->a_Edge.push_back(newEdge);
		}
		// check right side
		if (i < Rows * Cols - Cols)
		{
			newEdge.a_Start = Node[i];
			newEdge.a_End = Node[i+Rows];
			newEdge.a_Cost = 1;
			Node[i]->a_Edge.push_back(newEdge);
		}
		//check left
		if (i > Rows-1)
		{
			newEdge.a_Start = Node[i];
			newEdge.a_End = Node[i-1];
			newEdge.a_Cost = 1;
			Node[i]->a_Edge.push_back(newEdge);
		}
		//check bottom
		if (((i+1) % Rows) != 0)
		{
			newEdge.a_Start = Node[i];
			newEdge.a_End = Node[i+1];
			newEdge.a_Cost = 1;
			Node[i]->a_Edge.push_back(newEdge);
		}
	}
}

std::vector<GraphNode*> Graph::returnPath()
{
	GraphNode * currentNode = lastDestination;

	std::vector<GraphNode*> nodeVec;

	//loop until we get to the beginning
	while (currentNode != lastStart)
	{
		nodeVec.push_back(currentNode->LastNode);
		currentNode = currentNode->LastNode;
	}
	std::reverse(nodeVec.begin(), nodeVec.end());
	return nodeVec;
}

bool Graph::searchDFS(GraphNode* a_Start, GraphNode* a_End)
{
	lastStart = a_Start;
	lastDestination = a_End;

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
		for (int i = 0; i < pCurrent->a_Edge.size(); i++)
		{
			if (pCurrent->a_Edge[i].a_End->LastNode == NULL)
				pCurrent->a_Edge[i].a_End->LastNode = pCurrent;

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

bool Graph::searchAStar(GraphNode* a_Start, GraphNode* a_End, float inAdmissible)
{
	std::list<GraphNode*> NodeQueue;
	for (NodeList::iterator nodeIter = Node.begin(); nodeIter != Node.end(); nodeIter++)
	{
		(*nodeIter)->LastNode = NULL;
		(*nodeIter)->gScore = INFINITY;
		(*nodeIter)->fScore = INFINITY;
	}
	NodeQueue.push_back(a_Start);
	a_Start->LastNode = NodeQueue.back();
	a_Start->gScore = 0;
	a_Start->fScore = 0;
	int checkCount = 0;
	while (!NodeQueue.empty())
	{
		GraphNode* Current = NodeQueue.front();
		NodeQueue.pop_front();

		Current->data = 2;
		Current->a_Visited = true;
		if (Current == a_End)
		{
			GraphNode* Retrace = a_End;
			while (Retrace != a_Start)
			{
				Retrace->data = 1;

				Retrace = Retrace->LastNode;
			}
			a_Start->data = 3;
			a_End->data = 3;
			return true;
		}
		for (int i = 0; i < Current->a_Edge.size(); i++)
		{
			if (Current->a_Edge[i].a_End->a_Visited == false && Current->a_Edge[i].a_End->lock == false)
			{
				int Hx = 0;
				int Hy = 0;
				NodeQueue.push_back(Current->a_Edge[i].a_End);
				Current->a_Edge[i].a_End->gScore = (Current->gScore + Current->a_Edge[i].a_Cost);
				Hx = abs(a_End->x - Current->a_Edge[i].a_End->x);
				Hy = abs(a_End->y - Current->a_Edge[i].a_End->y);
				Current->a_Edge[i].a_End->fScore = Current->a_Edge[i].a_End->gScore + ((Hx + Hy) * (inAdmissible + 1));
				Current->a_Edge[i].a_End->LastNode = Current;
			}
		}
	}
	return false;
}

bool Graph::searchThetaStar(GraphNode* a_Start, GraphNode* a_End, float inadmissible)
{
	std::list<GraphNode*> NodeQueue;
	for (NodeList::iterator nodeIter = Node.begin(); nodeIter != Node.end(); nodeIter++)
	{
		(*nodeIter)->LastNode = NULL;
		(*nodeIter)->gScore = INFINITY;
		(*nodeIter)->fScore = INFINITY;
	}
	NodeQueue.push_back(a_Start);
	a_Start->gScore = 0;
	a_Start->fScore = 0;
	int checkCount = 0;
	while (!NodeQueue.empty()) {
		GraphNode* Current = NodeQueue.front();
		NodeQueue.pop_front();

		checkCount++;
		Current->data = 2;
		Current->a_Visited = true;
		if (Current == a_End)
		{
			GraphNode* Retrace = a_End;
			while (Retrace != a_Start)
			{
				Retrace->data = 1;

				Retrace = Retrace->LastNode;
			}
			a_Start->data = 3;
			a_End->data = 3;
			return true;
		}
		for (int i = 0; i < Current->a_Edge.size(); i++)
		{
			if (Current->a_Edge[i].a_End->a_Visited == false)
			{
				int Hx = 0;
				int Hy = 0;
				NodeQueue.push_back(Current->a_Edge[i].a_End);
				Current->a_Edge[i].a_End->gScore = (Current->gScore + Current->a_Edge[i].a_Cost);
				Hx = abs(a_End->x - Current->a_Edge[i].a_End->x);
				Hy = abs(a_End->y - Current->a_Edge[i].a_End->y);
				Current->a_Edge[i].a_End->fScore = Current->a_Edge[i].a_End->gScore + ((Hx + Hy) * (inadmissible + 1));
			}
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