#include "UndirectedGraph.h"



UndirectedGraph::UndirectedGraph()
{
}


UndirectedGraph::~UndirectedGraph()
{
}

void UndirectedGraph::AddVerticesAndEdgeRange(list<pair<int, int>> edgeList)
{
   Vertex source, target;
   for (auto const &edge : edgeList)
   {
	  try
	  {
		 source = this->vertexList.at(edge.first);
	  }
	  catch (out_of_range)
	  {
		 source = boost::add_vertex(this->graph);
		 this->graph[source].id = edge.first;
		 this->vertexList.emplace(edge.first, source);
	  }

	  try
	  {
		 target = this->vertexList.at(edge.second);
	  }
	  catch (out_of_range)
	  {
		 target = boost::add_vertex(this->graph);
		 this->graph[target].id = edge.second;
		 this->vertexList.emplace(edge.second, target);
	  }
	  boost::add_edge(source, target, this->graph);
   }
}

vector<int> UndirectedGraph::GetDegreeSequence()
{
   vector<int> result;
   pair<VertexIter, VertexIter> itr = boost::vertices(this->graph);
   for (itr.first; itr.first != itr.second; itr.first++)
   {
	  result.push_back(boost::out_degree(*itr.first, this->graph));
   }
   sort(result.begin(), result.end(), greater<int>());
   return result;
}

list<int> UndirectedGraph::GetNeighbors(int sourceId)
{
   list<int> neighborList;
   Vertex source = this->vertexList[sourceId];
   pair<AdjaIter, AdjaIter> itr = adjacent_vertices(source, this->graph);
   for (itr.first; itr.first != itr.second; itr.first++)
   {
	  neighborList.push_back(this->graph[*itr.first].id);
   }
   return neighborList;
}

list<pair<int, int>> UndirectedGraph::GetEdgeList()
{
   list<pair<int, int>> edgeList;
   int source, target;
   auto edgeRange = boost::edges(this->graph);
   for (auto edgeItr = edgeRange.first; edgeItr != edgeRange.second; edgeItr++)
   {
	  source = this->graph[boost::source(*edgeItr, this->graph)].id;
	  target = this->graph[boost::target(*edgeItr, this->graph)].id;
	  edgeList.emplace_back(source, target);
   }
   return edgeList;
}


vector<int> UndirectedGraph::GetNodesSortedByDegree(int count)
{
   int vertexCount = boost::num_vertices(this->graph);
   if (count > vertexCount)
	  count = vertexCount;
   vector<pair<int, int>> degreeOfNode;
   vector<int> result;
   pair<VertexIter, VertexIter> itr = boost::vertices(this->graph);
   for (itr.first; itr.first != itr.second; itr.first++)
   {
	  pair<int, int> d_nPair = make_pair(boost::out_degree(*itr.first, this->graph), this->graph[*itr.first].id);
	  degreeOfNode.push_back(d_nPair);
   }
   sort(degreeOfNode.begin(), degreeOfNode.end(), greater<pair<int, int>>());
   auto pos = degreeOfNode.begin();

   for (int i = 0; i < count; i++)
   {
	  result.push_back(pos->second);
	  advance(pos, 1);
   }
   return result;
}

