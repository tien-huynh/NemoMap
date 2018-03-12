#include "UndirectedGraph.h"



UndirectedGraph::UndirectedGraph()
{
}


UndirectedGraph::~UndirectedGraph()
{
}


/*Method to add vertices and edges to this graph
Parameter:
			edgeList: list of edges to be added, each pair entry is 1 edge as <sourceId, targetId>
						if source or target vertex is not in the graph yet, will add them*/
void UndirectedGraph::AddVerticesAndEdgeRange(list<pair<int, int>> edgeList)
{
   Vertex source, target;
   for (auto const &edge : edgeList)
   {
	  //Check if source vertex exists, if not add to graph
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

	  //Check if target vertex exists, if not add to graph
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
	  boost::add_edge(source, target, this->graph);	  //add edge
   }
}


/*Method to get the degree sequence of all vertices in descending order
	  This only give the degree sequence, not the vertex ID
To get vertex ID sorted by degree sequence use GetNodesSortedByDegree(int count)*/
vector<int> UndirectedGraph::GetDegreeSequence()
{
   vector<int> result;
   pair<VertexIter, VertexIter> itr = boost::vertices(this->graph);
   //get out degree of all vertices
   for (itr.first; itr.first != itr.second; itr.first++)
   {
	  result.push_back(boost::out_degree(*itr.first, this->graph));
   }
   sort(result.begin(), result.end(), greater<int>());	 //sort degree sequence, descending order
   return result;
}


/*Method to get a list of all neighboring/adjacent vertex ID
Parameter:
			sourceId: ID of the source vertex which you want to find its neighbors*/
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


/*Method to get a list of all edges in the graph
	  Each entry of the return list is an edge (pair of <sourceId, targetId>)*/
list<pair<int, int>> UndirectedGraph::GetEdgeList()
{
   list<pair<int, int>> edgeList;
   int source, target;
   auto edgeRange = boost::edges(this->graph);	//get all edges
   for (auto edgeItr = edgeRange.first; edgeItr != edgeRange.second; edgeItr++)
   {  
	  //get vertex_descriptors and their ID from each edge
	  source = this->graph[boost::source(*edgeItr, this->graph)].id;
	  target = this->graph[boost::target(*edgeItr, this->graph)].id;
	  edgeList.emplace_back(source, target);
   }
   return edgeList;
}



/*Method to get a list of vertices sorted by their degree sequence in descending order
Parameter:
			count: the number of expected vertices (start with highest degree sequence) to return
					 For example, there are 10 vertices in the graph, but you only want the top 4
					 of the vertices sorted by degree other, then count = 4. If count > # of vertices
					 in the graph, count = # of vertices*/
vector<int> UndirectedGraph::GetNodesSortedByDegree(int count)
{
   int vertexCount = boost::num_vertices(this->graph);
   //check for over estimation of # of vertices in the graph
   if (count > vertexCount)
	  count = vertexCount;
   vector<pair<int, int>> degreeOfNode;	  //vector of <vertexDegree, vertexID>
   vector<int> result;
   pair<VertexIter, VertexIter> itr = boost::vertices(this->graph);
   //get all vertex degrees and corresponding IDs
   for (itr.first; itr.first != itr.second; itr.first++)
   {
	  pair<int, int> d_nPair = make_pair(boost::out_degree(*itr.first, this->graph), this->graph[*itr.first].id);
	  degreeOfNode.push_back(d_nPair);
   }
   //sort by degree, descending order
   sort(degreeOfNode.begin(), degreeOfNode.end(), greater<pair<int, int>>());
   auto pos = degreeOfNode.begin();
   //get the sorted vertexID sorted by degree
   for (int i = 0; i < count; i++)
   {
	  result.push_back(pos->second);
	  advance(pos, 1);
   }
   return result;
}

