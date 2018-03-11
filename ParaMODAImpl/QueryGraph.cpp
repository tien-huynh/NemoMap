#include "QueryGraph.h"


ParaMODAImpl::QueryGraph::QueryGraph()
{
}

ParaMODAImpl::QueryGraph::QueryGraph(string label)
{
   this->identifier = label;
}

ParaMODAImpl::QueryGraph::~QueryGraph()
{
}

bool ParaMODAImpl::QueryGraph::isComplete(int subgraphSize)
{
   if (subgraphSize <= 1)
	  subgraphSize = boost::num_vertices(this->graph);
   int edgeCount = boost::num_edges(this->graph);
   return edgeCount == ((subgraphSize *(subgraphSize - 1)) / 2);
}

bool ParaMODAImpl::QueryGraph::isTree(int subgraphSize)
{
   if (subgraphSize <= 1)
	  subgraphSize = boost::num_vertices(this->graph);
   int edgeCount = boost::num_edges(this->graph);
   return edgeCount == (subgraphSize - 1);
}

//CHECK mappings might need to be reference or pointer
list<ParaMODAImpl::Mapping> ParaMODAImpl::QueryGraph::removeNonApplicableMappings(list<Mapping> mappings, UndirectedGraph & inputGraph, bool checkInducedMappingOnly)
{
   if (mappings.size() < 2)
	  return mappings;
   int subgraphSize = boost::num_vertices(this->graph);
   list<pair<list<int>,list<Mapping>>> mapGroups;
   for (auto const & itr : mappings)
   {
	  list<int> valueList;
	  for (auto const & func : itr.getFunction())
	  {		 
		 valueList.push_back(func.second);
	  }
	  if (mapGroups.size() == 0)
		 mapGroups.emplace_back(valueList, list<Mapping>(1, itr));
	  else
	  {
		 bool exist = false;
		 for (auto & mapped : mapGroups)
		 {
			if (EqualList(valueList, mapped.first))
			{
			   mapped.second.push_back(itr);
			   exist = true;
			   break;
			}
		 }
		 if(!exist)
			mapGroups.emplace_back(valueList, list<Mapping>(1, itr));
	  }
   }

   list<Mapping> toAdd;
   list<pair<int, int>> queryGraphEdges = this->GetEdgeList();

   for (auto const & group : mapGroups)
   {
	  list<int> g_nodes = group.first;
	  list<pair<int, int>> inducedSubGraphEdges;
	  pair<UndirGraph::edge_descriptor, bool> g_edge;
	  for (int i = 0; i < subgraphSize - 1; i++)
	  {
		 for (int j = (i + 1); j < subgraphSize; j++)
		 {
			g_edge = boost::edge(inputGraph.vertexList[i], inputGraph.vertexList[j], inputGraph.graph);
			if (g_edge.second)
			{
			   inducedSubGraphEdges.push_back(make_pair(i, j));
			}
		 }
	  }

	  UndirectedGraph *subgraph = new UndirectedGraph();
	  subgraph->AddVerticesAndEdgeRange(inducedSubGraphEdges);

	  for (auto const & item: group.second)
	  {
		 MappingTestResult result = MappingTestResult().IsMappingCorrect2(item.getFunction(), *subgraph, queryGraphEdges, checkInducedMappingOnly);
		 if (result.IsCorrectMapping)
		 {
			toAdd.push_back(item);
			break;
		 }		
	  }
	  delete subgraph;	  
   }

   mappings = list<Mapping>();	 //CHECK mapping might need to be reference
   if (toAdd.size() > 0)
   {
	  for (auto const & item : toAdd)
	  {
		 mappings.push_back(item);
	  }
   }
   return mappings;
}



