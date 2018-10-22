/*	Filename:		Graph.h
	Description:	Declaration of a Graph class
	Author:			Tien Huynh
*/

#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include "hopscotch_map.h"

using namespace std;

class Graph
{
public:
	Graph();
	~Graph();

	int getNumberOfVertices() { return vertexList.size(); };
	int getNumberOfEdges() { return edgeList.size(); };


	/*	Method to get a list of all edges in the graph
		@return
			Each entry of the return list is an edge (pair of <sourceId, targetId>)*/
	vector<pair<int, int>>& GetEdgeList() { return edgeList; };


	/*	Method to get a list of all vertices in the graph
		@return
			Each entry of the return list is a vertex and a list of its neighbors*/
	tsl::hopscotch_map<int, vector<int>>& GetVertexList() { return vertexList; };
	

	/*	Method to add a vertex to the graph
		@param 
			id: the id number of the vertex
		@return
			A pair of <iterator to the added vertex entry, boolean (True if that successfully added new vertex; 
				False if such vertex already exist)>*/		
	pair<tsl::hopscotch_map<int, vector<int>>::iterator, bool> add_vertex(const int &id);


	/*	Method to add an edge to the graph (update the edgeList)
		@param 
			source & target: the id number of the source and target vertex
		@return
			True if successfully added new edge, False if such edge already exist in the graph*/
	bool add_edge(const int &source, const int &target);
	

	/*	Method to add vertices and edges to this graph
		@param
			edgeList: list of edges to be added, each pair entry is 1 edge as <sourceId, targetId>
				if source and/or target vertex is not in the graph yet, will add them*/
	void AddVerticesAndEdgeRange(vector<pair<int, int>> &edgeList);


	/*	Method to get the degree sequence of all vertices in descending order
			This only give the degree sequence, not the vertex ID
			To get vertex ID sorted by degree sequence use GetNodesSortedByDegree()
		@return
			The degree sequence of all vertices in descending order*/
	vector<int> GetDegreeSequence();


	/*	Method to get a list of all neighboring/adjacent vertex ID
		@param
			sourceId: ID of the source vertex which you want to find its neighbors
		@return
			List of IDs of all of source's neighbors*/
	vector<int>& GetNeighbors(const int &sourceId);


	/*	Method to get the out degree of a vertex
		@param
			sourceId: ID of the source vertex which you want to find its out degree
		@return
			Out degree of the vertex*/
	int GetOutDegree(const int &sourceId) { return vertexList.at(sourceId).size(); };


	/*	Method to check if an edge exists in the graph
		@param
			source & target: the id number of the source and target vertex
		@return
			True if the edge exists, False otherwise*/
	bool TryGetEdge(const int &source, const int &target);
	

	/*	Method to get a list of vertices sorted by their degree sequence in ascending order
		@param
			degreeCutOff: the threshold of out degree that we want to check
				For example, threshold = 5 means only vertices with out degree >= 5 will be checked and sorted
		@return
			A list of nodes' IDs sorted by out degree in ascending order*/
	vector<int> GetNodesSortedByDegree(const int & degreeCutOff);

private:
	tsl::hopscotch_map<int, vector<int>> vertexList;	 //list of vertices
	vector<pair<int, int>> edgeList;	//list of edges
};


