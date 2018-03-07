#include "QueryGraph.h"


QueryGraph::QueryGraph()
{
	identifier = "";
	isFrequentSubgraph = false;
}

QueryGraph::QueryGraph(string label) : UndirectedGraph<int>()
{
	identifier = label;
}

QueryGraph::QueryGraph(string label, bool allowParralelEdges) : UndirectedGraph<int>(allowParralelEdges)
{
	identifier = label;
}


string QueryGraph::getIdentifier() const
{
	return identifier;
}

bool QueryGraph::getIsFrequentSubgraph() const
{
	return isFrequentSubgraph;
}

void QueryGraph::setIsFrequentSubgraph(bool temp) 
{
	isFrequentSubgraph = temp;
}

bool QueryGraph::IsComplete(int subgraphSize)
{
	if (subgraphSize <= 1)
		subgraphSize = getVertexCount();	//from UndirectedGraph
	return getEdgeCount() == ((subgraphSize * (subgraphSize - 1)) / 2);
}

bool QueryGraph::IsTree(int subgraphSize)
{
	if (subgraphSize <= 1)
		subgraphSize = getVertexCount();	//from UndirectedGraph
	return getEdgeCount() == (subgraphSize - 1);
}

vector<Mapping> QueryGraph::ReadMappingsFromFile(string filename)
{
	return vector<Mapping>();
}

string QueryGraph::WriteMappingsToFile(vector<Mapping> mappings)
{
	return string();
}

void QueryGraph::RemoveNonApplicableMappings(vector<Mapping> mappings, UndirectedGraph<int> inputGraph, bool checkInducedMappingOnly)
{
	if (mappings.size() < 2)
		return;
	int subgraphSize = getVertexCount();

}
