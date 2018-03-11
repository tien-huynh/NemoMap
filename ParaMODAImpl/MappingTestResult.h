#pragma once
#include "UndirectedGraph.h"
#include <iostream>

using namespace std;

namespace ParaMODAImpl
{
   class MappingTestResult
   {
   public:
	  MappingTestResult();
	  ~MappingTestResult();

	  MappingTestResult IsMappingCorrect(map<int, int> function, list<pair<int, int>> queryGraphEdges, UndirectedGraph &inputGraph, bool checkInducedMappingOnly, int subGraphEdgeCount = 0);
	  MappingTestResult IsMappingCorrect2(map<int, int> function, UndirectedGraph &subgraph, list<pair<int, int>> queryGraphEdges, bool checkInducedMappingOnly);
	  UndirectedGraph* GetSubgraph(UndirectedGraph &inputGraph, vector<int> g_nodes);

	  bool IsCorrectMapping;
	  int SubgraphEdgeCount;
   };
}
