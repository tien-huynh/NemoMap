#pragma once
#include "boost_1_66_0\boost\graph\adjacency_list.hpp"
#include <map>
#include <vector>

using namespace std;

struct VertexProperty
{
   int id;
};

//use Boost adjacency_list as graph template, undirected
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperty> UndirGraph;
typedef boost::graph_traits<UndirGraph>::vertex_descriptor Vertex;
typedef boost::graph_traits<UndirGraph>::vertex_iterator VertexIter;
typedef boost::graph_traits<UndirGraph>::adjacency_iterator AdjaIter;
typedef boost::graph_traits<UndirGraph>::edge_descriptor Edge;
typedef boost::graph_traits<UndirGraph>::edge_iterator EdgeIter;


class UndirectedGraph
{
public:
   UndirectedGraph::UndirectedGraph();
   UndirectedGraph::~UndirectedGraph();

   /*Method to add vertices and edges to this graph
   Parameter:  
			   edgeList: list of edges to be added, each pair entry is 1 edge as <sourceId, targetId>
						   if source or target vertex is not in the graph yet, will add them*/
   void AddVerticesAndEdgeRange(list<pair<int, int>> edgeList);

   /*Method to get the degree sequence of all vertices in descending order
		 This only give the degree sequence, not the vertex ID
	 To get vertex ID sorted by degree sequence use GetNodesSortedByDegree(int count)*/
   vector<int> GetDegreeSequence();

   /*Method to get a list of all neighboring/adjacent vertex ID
   Parameter:
			   sourceId: ID of the source vertex which you want to find its neighbors*/
   list<int> GetNeighbors(int sourceId);

   /*Method to get a list of all edges in the graph
		 Each entry of the return list is an edge (pair of <sourceId, targetId>)*/
   list<pair<int, int>> GetEdgeList();

   /*Method to get a list of vertices sorted by their degree sequence in descending order
   Parameter:
			   count: the number of expected vertices (start with highest degree sequence) to return
						For example, there are 10 vertices in the graph, but you only want the top 4
						of the vertices sorted by degree other, then count = 4. If count > # of vertices
						in the graph, count = # of vertices*/
   vector<int> GetNodesSortedByDegree(int count);


   UndirGraph graph;	//the Boost graph object
   map<int, UndirGraph::vertex_descriptor> vertexList;	 //list of vertices
};


//static bool sortDescend(const pair<int, int> &a, const pair<int, int> &b)
//{
//   if (a.first > b.first)
//	  return true;
//   if (a.first == b.first)
//	  return (a.second > b.second);
//   return false;
//};