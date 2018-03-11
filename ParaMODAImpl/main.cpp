#include "GraphProcessor.h"
#include "ParaMODAAlgorithm.h"
#include <iostream>
using namespace std;
using namespace ParaMODAImpl;

void main()
{
   int hold;
   UndirectedGraph inputGraph = GraphProcessor().LoadGraph("InputGraph.txt");
   cout << "Input Graph (G): Nodes - " << boost::num_vertices(inputGraph.graph) << "; Edges: " << boost::num_edges(inputGraph.graph) << endl;

   QueryGraph queryGraph = GraphProcessor().LoadGraph("QueryGraph4.txt", true);
   cout << "Query Graph (H): Nodes - " << boost::num_vertices(queryGraph.graph) << "; Edges: " << boost::num_edges(queryGraph.graph) << endl;

   cout << endl << "Completed. Result Summary" << endl;
   cout << "-----------------------------------------------------" << endl << endl;

   list<Mapping> frequentSubgraphs = ParaMODAAlgorithm().Algorithm2_Modified(queryGraph, inputGraph, -1, true);











   cin >> hold;
}

//for (int i = 0; i < 6; i++)
//{
//Vertex temp = add_vertex(g.graph);
//g.graph[temp].id = i;
//g.vertexList.emplace(i, temp);
//}
//add_edge(g.vertexList[0], g.vertexList[3], g.graph);
//add_edge(g.vertexList[1], g.vertexList[2], g.graph);
//add_edge(g.vertexList[3], g.vertexList[5], g.graph);

//list<pair<int, int>> edgeList = g.GetEdgeList();

////for (auto const & edge : edgeList)
////{
////cout << edge.first << "--" << edge.second << endl;
////}

//vector<int> dNodeList = g.GetNodesSortedByDegree(15);
//for (auto const & node : dNodeList)
//{
//cout << node << endl;
//}