#pragma once
#include "UndirectedGraph.h"
#include "Mapping.h"
#include <string>
#include <vector>
using namespace std;
class QueryGraph: public UndirectedGraph<int>
{
public:
	QueryGraph();
	QueryGraph(string label);
	QueryGraph(string label, bool allowParralelEdges);
	~QueryGraph();

	string getIdentifier() const;
	bool getIsFrequentSubgraph() const;
	void setIsFrequentSubgraph(bool temp);

	bool IsComplete(int subgraphSize = -1);
	bool IsTree(int subgraphSize = -1);

	vector<Mapping> ReadMappingsFromFile(string filename);
	string WriteMappingsToFile(vector<Mapping> mappings);
	void RemoveNonApplicableMappings(vector<Mapping> mappings, UndirectedGraph<int> inputGraph, bool checkInducedMappingOnly = true);
private:
	string identifier = "";
	bool isFrequentSubgraph = false;
};

