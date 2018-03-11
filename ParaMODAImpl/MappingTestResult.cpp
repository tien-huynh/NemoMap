#include "MappingTestResult.h"


ParaMODAImpl::MappingTestResult::MappingTestResult()
{
}


ParaMODAImpl::MappingTestResult::~MappingTestResult()
{
}

ParaMODAImpl::MappingTestResult ParaMODAImpl::MappingTestResult::IsMappingCorrect(map<int, int> function, list<pair<int, int>> queryGraphEdges, UndirectedGraph & inputGraph, bool checkInducedMappingOnly, int subGraphEdgeCount)
{
   vector<int> g_nodes;
   for (auto const & itr : function)
   {
	  g_nodes.push_back(itr.second);
   }
   UndirectedGraph* subgraph = GetSubgraph(inputGraph, g_nodes);
   return IsMappingCorrect2(function, *subgraph, queryGraphEdges, checkInducedMappingOnly);
}


ParaMODAImpl::MappingTestResult ParaMODAImpl::MappingTestResult::IsMappingCorrect2(map<int, int> function, UndirectedGraph & subgraph, list<pair<int, int>> queryGraphEdges, bool checkInducedMappingOnly)
{
   int qgLen = queryGraphEdges.size();
   list<pair<int, int>> edgeImages;

   for (auto const & qEdge : queryGraphEdges)
   {
	  try
	  {
		 edgeImages.push_back(make_pair(function.at(qEdge.first), function.at(qEdge.second)));
	  }
	  catch (out_of_range)
	  {
	  }
   }

   MappingTestResult result;
   result.SubgraphEdgeCount = boost::num_edges(subgraph.graph);

   vector<int> subgraphDegrees = subgraph.GetDegreeSequence();
   int subgLen = subgraphDegrees.size();
   UndirectedGraph testG = UndirectedGraph();
   testG.AddVerticesAndEdgeRange(edgeImages);
   vector<int> testGdeg = testG.GetDegreeSequence();

   if (result.SubgraphEdgeCount < qgLen)
   {
	  result.IsCorrectMapping = false;
	  return result; //CHECK result.IsCorrectMapping flag
   }
   else if (result.SubgraphEdgeCount == qgLen)
   {
	  for (int i = subgLen - 1; i >= 0; i--)
	  {
		 if (subgraphDegrees[i] != testGdeg[i])
		 {
			result.IsCorrectMapping = false;
			return result;
		 }
	  }
	  result.IsCorrectMapping = true;
	  return result;
   }
   else
   {
	  if (checkInducedMappingOnly)
	  {
		 result.IsCorrectMapping = false;
		 return result;
	  }
	  for (int i = subgLen - 1; i >= 0; i--)
	  {
		 if (subgraphDegrees[i] < testGdeg[i])
		 {
			result.IsCorrectMapping = false;
			return result;
		 }
	  }
	  result.IsCorrectMapping = true;
	  return result;
   }

   return result;
}

UndirectedGraph * ParaMODAImpl::MappingTestResult::GetSubgraph(UndirectedGraph & inputGraph, vector<int> g_nodes)
{
   UndirectedGraph *subgraph = new UndirectedGraph();
   list<pair<int, int>> inducedSubgraphEdges;
   int subgraphSize = g_nodes.size();
   pair<UndirGraph::edge_descriptor, bool> g_edge;
   for (int i = 0; i < subgraphSize - 1; i++)
   {
	  for (int j = (i + 1); j < subgraphSize; j++)
	  {
		 g_edge = boost::edge(inputGraph.vertexList[g_nodes[i]], inputGraph.vertexList[g_nodes[j]], inputGraph.graph);
		 if (g_edge.second)
		 {
			inducedSubgraphEdges.push_back(make_pair(i, j));
		 }
	  }
   }

   subgraph->AddVerticesAndEdgeRange(inducedSubgraphEdges);
   return subgraph;
}
