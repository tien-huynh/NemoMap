#pragma once
#include "boost_1_66_0\boost\graph\adjacency_list.hpp"
#include <map>
#include <vector>

using namespace std;

struct VertexProperty
{
   int id;
};

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

   void AddVerticesAndEdgeRange(list<pair<int, int>> edgeList);
   vector<int> GetDegreeSequence();
   list<int> GetNeighbors(int sourceId);
   list<pair<int, int>> GetEdgeList();
   vector<int> GetNodesSortedByDegree(int count);


   UndirGraph graph;
   map<int, UndirGraph::vertex_descriptor> vertexList;
};


//static bool sortDescend(const pair<int, int> &a, const pair<int, int> &b)
//{
//   if (a.first > b.first)
//	  return true;
//   if (a.first == b.first)
//	  return (a.second > b.second);
//   return false;
//};