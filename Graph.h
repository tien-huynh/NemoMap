#pragma once
//#include <iterator>
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include "hopscotch_map.h"

using namespace std;

//struct int_pair_hash {
//	inline size_t operator()(const std::pair<int, int> & pair) const {
//		return hash<int>()(pair.first) + hash<int>()(pair.second);
//	}
//};

class Graph
{
public:
	Graph();
	~Graph();

	int getNumberOfVertices() { return vertexList.size(); };
	int getNumberOfEdges() { return edgeList.size(); };

	/*Method to get a list of all edges in the graph
	Each entry of the return list is an edge (pair of <sourceId, targetId>)*/
	vector<pair<int, int>>& GetEdgeList() { return edgeList; };
	tsl::hopscotch_map<int, vector<int>>& GetVertexList() { return vertexList; };
	//tsl::hopscotch_map<int, int> GetVertexLabeledList() { return vertexLabeledList; };


	pair<tsl::hopscotch_map<int, vector<int>>::iterator, bool> add_vertex(const int &id);
	bool add_edge(const int &source, const int &target);


	/*Method to add vertices and edges to this graph
	Parameter:
	edgeList: list of edges to be added, each pair entry is 1 edge as <sourceId, targetId>
	if source or target vertex is not in the graph yet, will add them*/
	void AddVerticesAndEdgeRange(vector<pair<int, int>> &edgeList);

	/*Method to get the degree sequence of all vertices in descending order
	This only give the degree sequence, not the vertex ID
	To get vertex ID sorted by degree sequence use GetNodesSortedByDegree(int count)*/
	vector<int> GetDegreeSequence();

	/*Method to get a list of all neighboring/adjacent vertex ID
	Parameter:
	sourceId: ID of the source vertex which you want to find its neighbors*/
	vector<int>& GetNeighbors(const int &sourceId);

	int GetOutDegree(const int &sourceId) { return vertexList.at(sourceId).size(); };

	bool TryGetEdge(const int &source, const int &target);


	/*Method to get a list of vertices sorted by their degree sequence in descending order
	Parameter:
	count: the number of expected vertices (start with highest degree sequence) to return
	For example, there are 10 vertices in the graph, but you only want the top 4
	of the vertices sorted by degree other, then count = 4. If count > # of vertices
	in the graph, count = # of vertices*/
	vector<int> GetNodesSortedByDegree(const int & degreeCutOff);

private:
	tsl::hopscotch_map<int, vector<int>> vertexList;	 //list of vertices
	//tsl::hopscotch_map<int, int> vertexLabeledList;
	vector<pair<int, int>> edgeList;
};


