#pragma once
#include "UndirectedGraph.h"
#include "QueryGraph.h"
#include "Mapping.h"
#include "MappingTestResult.h"
#include <list>

using namespace std;
namespace ParaMODAImpl
{
   //MOVED to MappingTestResult class

   /*struct MappingTestResult
   {
	  bool IsCorrectMapping;
	  int SubgraphEdgeCount;
   };*/

   class Utils
   {
   public:
	  Utils();
	  ~Utils();

	  //MOVED to MappingTestResult class

	  /*MappingTestResult IsMappingCorrect(map<int, int> function, list<pair<int, int>> queryGraphEdges, UndirectedGraph &inputGraph, bool checkInducedMappingOnly, int subGraphEdgeCount = 0);
	  MappingTestResult IsMappingCorrect2(map<int, int> function, UndirectedGraph &subgraph, list<pair<int, int>> queryGraphEdges, bool checkInducedMappingOnly);*/
	  /*UndirectedGraph* GetSubgraph(UndirectedGraph &inputGraph, list<int> g_nodes);*/

	  int GetMostConstrainedNeighbour(list<int> domain, UndirectedGraph &queryGraph);

	  list<int> ChooseNeighboursOfRange(list<int> usedRange, UndirectedGraph &inputGraph);

	  bool IsNeighbourIncompatible(UndirectedGraph &inputGraph,
		 int n, map<int, int> partialMap, QueryGraph &queryGraph, list<int> neighborsOfM);

	  bool CanSupport(QueryGraph &queryGraph, int node_H, UndirectedGraph &inputGraph, int node_G);

	  list<pair<list<int>, list<Mapping>>> IsomorphicExtension(map<int, int> partialMap, QueryGraph &queryGraph
		 , list<pair<int, int>> queryGraphEdges, UndirectedGraph &inputGraph, bool getInducedMappingsOnly);
   };
}