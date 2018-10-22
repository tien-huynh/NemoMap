/*	Filename:		Graph.cpp
	Description:	Implementation of a Graph class
	Author:			Tien Huynh
*/

#include "Graph.h"

Graph::Graph()
{
}


Graph::~Graph()
{
}


pair<tsl::hopscotch_map<int, vector<int>>::iterator, bool> Graph::add_vertex(const int &id)
{
	return vertexList.insert(make_pair(id, vector<int>()));
}


bool Graph::add_edge(const int &source, const int &target)
{
	tsl::hopscotch_map<int, vector<int>>::iterator itrSource = add_vertex(source).first;
	//Check if edge already exist
	if (binary_search(itrSource->second.begin(), itrSource->second.end(), target))
		return false;
	itrSource.value().push_back(target);
	sort(itrSource.value().begin(), itrSource.value().end());	//sort needed for binary search in other methods

	tsl::hopscotch_map<int, vector<int>>::iterator itrTarget = add_vertex(target).first;
	itrTarget.value().push_back(source);
	sort(itrTarget.value().begin(), itrTarget.value().end());	//sort needed for binary search in other methods

	edgeList.push_back(make_pair(source, target));	//update edgeList
	return true;
}


void Graph::AddVerticesAndEdgeRange(vector<pair<int, int>>& edgeList)
{
	for (auto const &edge : edgeList)
	{
		add_edge(edge.first, edge.second);	  //add edge
	}
}


vector<int> Graph::GetDegreeSequence()
{
	vector<int> result;
	result.reserve(this->vertexList.size());

	//get out degree of all vertices
	for (auto const &vertex : this->vertexList)
	{
		result.push_back(vertex.second.size());
	}
	sort(result.begin(), result.end(), greater<int>());	 //sort degree sequence, descending order
	return result;
}


vector<int>& Graph::GetNeighbors(const int &sourceId)
{
	return vertexList.at(sourceId);		//may need to catch out_of_range exception
}


bool Graph::TryGetEdge(const int &source, const int &target)
{
	vector<pair<int, int>>::iterator edgeListBegin = edgeList.begin();
	vector<pair<int, int>>::iterator edgeListEnd = edgeList.end();

	if ((find(edgeListBegin, edgeListEnd, make_pair(source, target)) == edgeListEnd)
		&& (find(edgeListBegin, edgeListEnd, make_pair(target, source)) == edgeListEnd))
		return false;
	return true;
}


vector<int> Graph::GetNodesSortedByDegree(const int & degreeCutOff)
{
	int vertexCount = getNumberOfVertices();

	vector<pair<int, int>> degreeOfNode;	  //list of <vertexDegree, vertexID>
	degreeOfNode.reserve(vertexCount);
	vector<int> result;
	result.reserve(vertexCount);

	//get all vertex degrees and corresponding IDs
	for (auto const &vertex : this->vertexList)
	{
		if (vertex.second.size() >= degreeCutOff)
			degreeOfNode.push_back(make_pair(vertex.second.size(), vertex.first));
	}

	//sort by degree, ascending order
	sort(degreeOfNode.begin(), degreeOfNode.end());
	auto pos = degreeOfNode.begin();

	//get the sorted vertexID sorted by degree
	for (int i = degreeOfNode.size(); i != 0; i--)
	{
		result.push_back(pos->second);
		advance(pos, 1);
	}

	return result;
}
