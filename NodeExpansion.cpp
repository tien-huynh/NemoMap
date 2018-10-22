/*	Filename:		NodeExpansion.cpp
	Description:	Implementation of a class to enumerate all possible graph pattern of size n (up to size 5 graph)
					*****NOTE*****: current implementation is crude as enumaration is manually entered
					_____TO DO_____: research and implement an algorithm to generate all possible pattern of size n graph
	Author:			Tien Huynh
*/

#include "NodeExpansion.h"


NodeExpansion::NodeExpansion()
{
}


NodeExpansion::~NodeExpansion()
{
}


void NodeExpansion::threeExpand()
{
	vector < vector<pair<int, int>>> graphEdgeList = { {{1,2}, {2,3}},
														{{1,2}, {2,3}, {1,3}} };
	listOfGraphs = vector<Graph>(graphEdgeList.size(), Graph());
	for (int i = 0; i < graphEdgeList.size(); i++)
	{
		listOfGraphs[i].AddVerticesAndEdgeRange(graphEdgeList[i]);
	}
}


void NodeExpansion::fourExpand()
{
	vector < vector<pair<int, int>>> graphEdgeList = { { {1,2}, {2,3}, {3,4} },
														{ {1,2}, {2,3}, {2,4} },
														{ {1,2}, {2,3}, {2,4}, {3,4} },
														{ {1,2}, {1,4}, {2,3}, {3,4} },
														{ {1,2}, {1,3}, {2,3}, {2,4}, {3,4} },
														{ {1,2}, {1,3}, {1,4}, {2,3}, {2,4}, {3,4} } };
	listOfGraphs = vector<Graph>(graphEdgeList.size(), Graph());
	for (int i = 0; i < graphEdgeList.size(); i++)
	{
		listOfGraphs[i].AddVerticesAndEdgeRange(graphEdgeList[i]);
	}
}


void NodeExpansion::fiveExpand()
{
	vector < vector<pair<int, int>>> graphEdgeList = { { { 2,1 },{ 3,1 },{ 4,1 },{ 5,1 } },
														{ { 2,1 },{ 3,1 },{ 4,1 },{ 2,5 } },
														{ { 2,1 },{ 3,1 },{ 2,4 },{ 3,5 } },
														{ { 2,1 },{ 3,1 },{ 4,1 },{ 5,1 },{ 2,5 } },
														{ { 2,1 },{ 3,5 },{ 4,1 },{ 5,1 },{ 2,5 } },
														{ { 2,1 },{ 3,1 },{ 4,1 },{ 3,5 },{ 2,5 } },
														{ { 3,1 },{ 4,1 },{ 2,4 },{ 2,5 },{ 3,5 } },
														{ { 2,1 },{ 3,1 },{ 4,1 },{ 3,5 },{ 2,4 } },
														{ { 2,1 },{ 3,1 },{ 4,1 },{ 5,1 },{ 2,5 },{ 3,5 } },
														{ { 2,1 },{ 3,1 },{ 4,1 },{ 3,5 },{ 2,5 },{ 4,5 } },
														{ { 2,1 },{ 3,1 },{ 4,1 },{ 2,4 },{ 2,5 },{ 3,5 } },														
														{ { 2,1 },{ 3,1 },{ 4,1 },{ 5,1 },{ 2,4 },{ 3,5 } },
														{ { 2,1 },{ 3,1 },{ 4,1 },{ 2,5 },{ 2,4 },{ 4,5 } },
														{ { 2,1 },{ 3,1 },{ 4,1 },{ 5,1 },{ 2,5 },{ 2,4 },{ 4,5 } },
														{ { 2,1 },{ 3,1 },{ 4,1 },{ 5,1 },{ 2,5 },{ 3,5 },{ 4,5 } },														
														{ { 2,1 },{ 3,1 },{ 4,1 },{ 5,1 },{ 2,4 },{ 2,5 },{ 3,5 } },
														{ { 2,1 },{ 3,1 },{ 4,1 },{ 2,4 },{ 2,5 },{ 3,5 },{ 3,4 } },
														{ { 2,1 },{ 3,1 },{ 4,1 },{ 5,1 },{ 2,4 },{ 2,5 },{ 3,5 },{ 4,5 } },														
														{ { 2,1 },{ 3,1 },{ 4,1 },{ 5,1 },{ 2,4 },{ 2,5 },{ 3,5 },{ 3,4 } },
														{ { 2,1 },{ 3,1 },{ 4,1 },{ 5,1 },{ 2,4 },{ 2,5 },{ 3,5 },{ 3,4 },{ 4,5 } },
														{ { 2,1 },{ 3,1 },{ 4,1 },{ 5,1 },{ 2,4 },{ 2,5 },{ 3,5 },{ 3,4 },{ 4,5 },{ 2,3 } } };
	listOfGraphs = vector<Graph>(graphEdgeList.size(), Graph());
	for (int i = 0; i < graphEdgeList.size(); i++)
	{
		listOfGraphs[i].AddVerticesAndEdgeRange(graphEdgeList[i]);
	}
}
