#pragma once
#include "Graph.h"

class NodeExpansion
{
public:
	NodeExpansion();
	~NodeExpansion();

	vector<Graph>& getListOfGraphs() { return listOfGraphs; };

	void threeExpand();
	void fourExpand();
	void fiveExpand();

private:
	vector<Graph> listOfGraphs;
};

