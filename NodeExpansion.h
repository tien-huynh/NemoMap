/*	Filename:		NodeExpansion.h
	Description:	Declaration of a class to enumerate all possible graph pattern of size n (up to size 5 graph)
					*****NOTE*****: current implementation is crude as enumaration is manually entered
					_____TO DO_____: research and implement an algorithm to generate all possible pattern of size n graph
	Author:			Tien Huynh
*/
#pragma once
#include "Graph.h"

class NodeExpansion
{
public:
	NodeExpansion();
	~NodeExpansion();

	vector<Graph>& getListOfGraphs() { return listOfGraphs; };

	void threeExpand();		//expand all patterns of 3-node graph
	void fourExpand();		//expand all patterns of 4-node graph
	void fiveExpand();		//expand all patterns of 5-node graph

private:
	vector<Graph> listOfGraphs;		//list of all possible patterns of size n graph
};

