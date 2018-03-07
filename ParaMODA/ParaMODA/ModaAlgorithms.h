#include <stdio.h>
//#include <System.Runtime.CompilerServices>

#pragma once
#include "ExpansionTreeBuilder.h"
#include "MappingNodesComparer.h"
#include "UndirectedGraph.h"
#include "QueryGraph.h"
#include <map>
#include <list>
class ModaAlgorithms
{
public:
	ModaAlgorithms();
	~ModaAlgorithms();

	bool getUseModifiedGrochow();
    void setUseModifiedGrochow(bool ModifiedGrochow);
	void BuildTree(int subgraphSize);

	//Algo1
	//map<QueryGraph, string> Algorithm1_C(UndirectedGraph<int> inputGraph, QueryGraph qGraph, int subgraphSize, int thresholdValue);
	//map<QueryGraph, list<Mapping>> Algorithm1(UndirectedGraph<int> inputGraph, QueryGraph qGraph, int subgraphSize = -1, int thresholdValue = 0);

	////Algo2
	//list<Mapping> Algorithm2(QueryGraph queryGraph, UndirectedGraph<int> inputGraphClone, int numberOfSamples, bool getInducedMappingsOnly);
	////Algo2 mod
	//list<Mapping> Algorithm2_Modified(QueryGraph queryGraph, UndirectedGraph<int> inputGraph, int numberOfSamples, bool getInducedMappingsOnly);
	////static HashSet<Mapping> GetSet(map<int[], list<Mapping>> theMappings);
	

private:
	bool UseModifiedGrochow;
	ExpansionTreeBuilder<int> *_builder;// = new ExpansionTreeBuilder<int>();
	MappingNodesComparer *MappingNodesComparer;
	ExpansionTreeNode GetNextNode();
	//Algo3
	//list<Mapping>
	//	Algorithm3(map<QueryGraph, list<Mapping>> allMappings, UndirectedGraph<int> inputGraph, QueryGraph queryGraph,
	//		AdjacencyGraph<ExpansionTreeNode> expansionTree,
	//		QueryGraph parentQueryGraph, string &newFileName, string fileName = nullptr);
	//QueryGraph GetParent(QueryGraph queryGraph, AdjacencyGraph<ExpansionTreeNode> expansionTree);
	//static Edge<int> GetEdgeDifference(QueryGraph currentQueryGraph, QueryGraph parentQueryGraph, HashSet<Edge<int>> parentQueryGraphEdges);

};
