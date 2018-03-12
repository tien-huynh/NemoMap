#include "Utils.h"



ParaMODAImpl::Utils::Utils()
{
}


ParaMODAImpl::Utils::~Utils()
{
}


int ParaMODAImpl::Utils::GetMostConstrainedNeighbour(list<int> domain, UndirectedGraph & queryGraph)
{
   for (auto const &dom : domain)
   {
	  list<int> local = queryGraph.GetNeighbors(dom);

	  if (local.size() > 0)
	  {
		 for (auto const &loc : local)
		 {
			//equivalent to this in C#
			//		 if (!domain.Contains(loc))
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
			//equivalent to this in C#
			//		 if (!usedRange.Contains(loc))
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
   //equivalent to this in C#
   //		if (partialMap.ContainsValue(n))
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
	  //equivalent to this in C#
	  //		if (!partialMap.TryGetValue(d, out val))
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
	  //following block equivalent to this in C#
	  //		queryGraph.Vertices.Except(neighborsOfM)
	  //---------------------------------------------------------
	  for (itr.first; itr.first != itr.second; itr.first++)
	  {
		 if (find(neighborsOfM.begin(), neighborsOfM.end(), queryGraph.graph[*itr.first].id) == neighborsOfM.end())
			queryDifferNeighborsM.push_back(queryGraph.graph[*itr.first].id);
	  }
	  //---------------------------------------------------------

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
   //extract list of keys and list of values from partialMap
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

		 if (subList.size() > 0)
		 {
			for (auto & item : subList)
			{
			   if (item.second.size() > 1)
			   {
				  item.second = queryGraph.removeNonApplicableMappings(item.second, inputGraph, getInducedMappingsOnly);
			   }

			   list<Mapping> maps;
			   bool found = false;
			   //following block equivalent to this in C#
			   //		if (listOfIsomorphisms.TryGetValue(item.Key, out maps))
			   //---------------------------------------------------------
			   for (auto const & isomorph : listOfIsomorphisms)
			   {
				  if (EqualList(item.first, isomorph.first))
				  {
					 maps = list<Mapping>(item.second);
					 found = true;
					 //break;
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
			   //---------------------------------------------------------
			}
		 }
	  }
   }

   return listOfIsomorphisms;
}
