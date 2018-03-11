#include "Utils.h"



ParaMODAImpl::Utils::Utils()
{
}


ParaMODAImpl::Utils::~Utils()
{
}

//ParaMODAImpl::MappingTestResult ParaMODAImpl::Utils::IsMappingCorrect(map<int, int> function, list<pair<int, int>> queryGraphEdges, UndirectedGraph & inputGraph, bool checkInducedMappingOnly, int subGraphEdgeCount)
//{
//   list<int> g_nodes;
//   for (auto const & itr : function)
//   {
//	  g_nodes.push_back(itr.second);
//   }
//   UndirectedGraph* subgraph = GetSubgraph(inputGraph, g_nodes);
//   return IsMappingCorrect2(function, *subgraph, queryGraphEdges, checkInducedMappingOnly);
//}

//ParaMODAImpl::MappingTestResult ParaMODAImpl::Utils::IsMappingCorrect2(map<int, int> function, UndirectedGraph & subgraph, list<pair<int, int>> queryGraphEdges, bool checkInducedMappingOnly)
//{
//   int qgLen = queryGraphEdges.size();
//   list<pair<int, int>> edgeImages;
//
//   for (auto const & qEdge: queryGraphEdges)
//   {
//	  try
//	  {
//		 edgeImages.push_back(make_pair(function.at(qEdge.first), function.at(qEdge.second)));
//	  }
//	  catch(out_of_range)
//	  { }
//   }
//
//   MappingTestResult result;
//   result.SubgraphEdgeCount = boost::num_edges(subgraph.graph);
//
//   vector<int> subgraphDegrees = subgraph.GetDegreeSequence();
//   int subgLen = subgraphDegrees.size();
//   UndirectedGraph testG = UndirectedGraph();
//   testG.AddVerticesAndEdgeRange(edgeImages);
//   vector<int> testGdeg = testG.GetDegreeSequence();
//
//   if (result.SubgraphEdgeCount < qgLen)
//   {
//	  return result; //CHECK result.IsCorrectMapping flag
//   }
//   else if (result.SubgraphEdgeCount == qgLen)
//   {
//	  for (int i = subgLen - 1; i >= 0; i--)
//	  {
//		 if (subgraphDegrees[i] != testGdeg[i])
//		 {
//			result.IsCorrectMapping = false;
//			return result;
//		 }
//	  }
//	  result.IsCorrectMapping = true;
//	  return result;
//   }
//   else
//   {
//	  if (checkInducedMappingOnly)
//	  {
//		 result.IsCorrectMapping = false;
//		 return result;
//	  }
//	  for (int i = subgLen - 1; i >= 0; i--)
//	  {
//		 if (subgraphDegrees[i] < testGdeg[i])
//		 {
//			result.IsCorrectMapping = false;
//			return result;
//		 }
//	  }
//	  result.IsCorrectMapping = true;
//	  return result;
//   }
//
//   return result;
//}

//UndirectedGraph* ParaMODAImpl::Utils::GetSubgraph(UndirectedGraph &inputGraph, list<int> g_nodes)
//{
//   UndirectedGraph *subgraph = new UndirectedGraph();
//   list<pair<int, int>> inducedSubgraphEdges;
//   int subgraphSize = g_nodes.size();
//   pair<UndirGraph::edge_descriptor, bool> g_edge;
//   for (int i = 0; i < subgraphSize - 1; i++)
//   {
//	  for (int j = (i + 1); j < subgraphSize; j++)
//	  {
//		 g_edge = boost::edge(inputGraph.vertexList[i], inputGraph.vertexList[j], inputGraph.graph);
//		 if (g_edge.second)
//		 {
//			inducedSubgraphEdges.push_back(make_pair(i,j));
//		 }
//	  }
//   }
//
//   subgraph->AddVerticesAndEdgeRange(inducedSubgraphEdges);
//   return subgraph;
//}

int ParaMODAImpl::Utils::GetMostConstrainedNeighbour(list<int> domain, UndirectedGraph & queryGraph)
{
   for (auto const &dom : domain)
   {
	  list<int> local = queryGraph.GetNeighbors(dom);
	  if (local.size() > 0)
	  {
		 for (auto const &loc : local)
		 {
			if (find(domain.begin(), domain.end(), loc) == domain.end())
			{
			   return loc;
			}
		 }
	  }
   }

   return -1;
}

list<int> ParaMODAImpl::Utils::ChooseNeighboursOfRange(list<int> usedRange, UndirectedGraph &inputGraph)
{
   list<int> toReturn;
   for (auto const &range : usedRange)
   {
	  list<int> local = inputGraph.GetNeighbors(range);
	  if (local.size() > 0)
	  {
		 for (auto const &loc : local)
		 {
			if (find(usedRange.begin(), usedRange.end(), loc) == usedRange.end())
			{
			   toReturn.push_back(loc);
			}
		 }
	  }
	  else
		 break;
   }

   return toReturn;
}

bool ParaMODAImpl::Utils::IsNeighbourIncompatible(UndirectedGraph & inputGraph, int n, map<int, int> partialMap, QueryGraph & queryGraph, list<int> neighborsOfM)
{
   for (auto const &itr : partialMap)
   {
	  if (itr.second == n)
		 return true;
   }
   
   list<int> neighborsOfN = inputGraph.GetNeighbors(n);

   bool doNext = false;
   int val;
   for (auto const &d : neighborsOfM)
   {
	  try
	  {
		 val = partialMap.at(d);
	  }
	  catch (out_of_range)
	  {
		 doNext = true;
		 break;
	  }

	  if (find(neighborsOfN.begin(), neighborsOfN.end(), val) == neighborsOfN.end())
	  {
		 return true;
	  }
   }

   if (doNext && (boost::num_vertices(queryGraph.graph) > 4))
   {
	  list<int> queryDifferNeighborsM;
	  pair<VertexIter, VertexIter> itr = boost::vertices(queryGraph.graph);
	  for (itr.first; itr.first != itr.second; itr.first++)
	  {
		 if (find(neighborsOfM.begin(), neighborsOfM.end(), queryGraph.graph[*itr.first].id) == neighborsOfM.end())
			queryDifferNeighborsM.push_back(queryGraph.graph[*itr.first].id);
	  }

	  for (auto const &d : queryDifferNeighborsM)
	  {
		 try
		 {
			val = partialMap.at(d);
		 }
		 catch (out_of_range)
		 {
			return false;
		 }

		 if (find(neighborsOfN.begin(), neighborsOfN.end(), val) == neighborsOfN.end())
		 {
			return true;
		 }
	  }
   }

   return false;
}

bool ParaMODAImpl::Utils::CanSupport(QueryGraph & queryGraph, int node_H, UndirectedGraph & inputGraph, int node_G)
{
   int degreeG = int(boost::out_degree(inputGraph.vertexList[node_G], inputGraph.graph));
   int degreeH = boost::out_degree(queryGraph.vertexList[node_H], queryGraph.graph);
   return degreeG >= degreeH;
}

list<pair<list<int>, list<ParaMODAImpl::Mapping>>> ParaMODAImpl::Utils::IsomorphicExtension(map<int, int> partialMap, QueryGraph & queryGraph, list<pair<int, int>> queryGraphEdges, UndirectedGraph & inputGraph, bool getInducedMappingsOnly)
{
   list<pair<list<int>, list<Mapping>>> listOfIsomorphisms;
   list<int> partialMapValues, partialMapKeys;;

   for (auto const & map : partialMap)
   {
	  partialMapValues.push_back(map.second);
	  partialMapKeys.push_back(map.first);
   }
   if(partialMap.size() == boost::num_vertices(queryGraph.graph))
   { 
	  MappingTestResult result = MappingTestResult().IsMappingCorrect(partialMap, queryGraphEdges, inputGraph, getInducedMappingsOnly);
	  if (result.IsCorrectMapping)
	  {
		 listOfIsomorphisms.push_back(make_pair(partialMapValues, list<Mapping>(1, Mapping(partialMap,result.SubgraphEdgeCount) )));
		 return listOfIsomorphisms;
	  }
	  return  list<pair<list<int>, list<Mapping>>>();
   }
   
   int m = GetMostConstrainedNeighbour(partialMapKeys, queryGraph);
   if (m < 0)
	  return  list<pair<list<int>, list<Mapping>>>();
   list<int> neighbourRange = ChooseNeighboursOfRange(partialMapValues, inputGraph);
   list<int> neighborsOfM = queryGraph.GetNeighbors(m);
   int newPartialMapCount = partialMap.size() + 1;

   for (auto const & i: neighbourRange)
   {
	  if (IsNeighbourIncompatible(inputGraph, i, partialMap, queryGraph, neighborsOfM) == false)
	  {
		 map<int, int> newPartialMap;
		 for (auto const & item : partialMap)
		 {
			newPartialMap.emplace(item.first, item.second);
		 }
		 newPartialMap[m] = i;
		 list<pair<list<int>, list<Mapping>>> subList = IsomorphicExtension(newPartialMap, queryGraph, queryGraphEdges, inputGraph, getInducedMappingsOnly);

		 if (subList.size() > 0) //CHECK
		 {
			for (auto & item : subList)
			{
			   if (item.second.size() > 1)
			   {
				  item.second = queryGraph.removeNonApplicableMappings(item.second, inputGraph, getInducedMappingsOnly);
			   }
			   list<Mapping> maps;
			   bool found = false;
			   for (auto const & isomorph : listOfIsomorphisms)
			   {
				  if (EqualList(item.first, isomorph.first))
				  {
					 maps = list<Mapping>(item.second);
					 found = true;
					 break;
				  }
			   }
			   if (!found)
			   {
				  for (auto & isomorph : listOfIsomorphisms)
				  {
					 if (EqualList(item.first, isomorph.first))
					 {
						isomorph.second = item.second;
						found = true;
						break;
					 }
				  }
				  if (!found)
				  {
					 listOfIsomorphisms.push_back(make_pair(item.first, item.second));
				  }
			   }
			}
		 }
	  }
   }

   return listOfIsomorphisms;
}
