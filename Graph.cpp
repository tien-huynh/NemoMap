#include "Graph.h"



Graph::Graph()
{
}


Graph::~Graph()
{
}


pair<tsl::hopscotch_map<int, vector<int>>::iterator, bool> Graph::add_vertex(const int &id)
{
	//pair<int, vector<int>> item(id, vector<int>());
	//return vertexList.insert(item);
	
	
	return vertexList.insert(make_pair(id, vector<int>()));


	//pair<tsl::hopscotch_map<int, vector<int>>::iterator, bool> result(vertexList.insert(make_pair(id, vector<int>())));
	//if (result.second)
	//	vertexLabeledList.insert(make_pair(id, id));
	//return result;
}


bool Graph::add_edge(const int &source, const int &target)
{
	//pair<int, int> edge(source, target);

	tsl::hopscotch_map<int, vector<int>>::iterator itrSource = add_vertex(source).first;
	if (binary_search(itrSource->second.begin(), itrSource->second.end(), target))
		return false;
	itrSource.value().push_back(target);
	sort(itrSource.value().begin(), itrSource.value().end());

	tsl::hopscotch_map<int, vector<int>>::iterator itrTarget = add_vertex(target).first;
	itrTarget.value().push_back(source);
	sort(itrTarget.value().begin(), itrTarget.value().end());

	edgeList.push_back(make_pair(source, target));
	return true;
}


/*Method to add vertices and edges to this graph
Parameter:
edgeList: list of edges to be added, each pair entry is 1 edge as <sourceId, targetId>
if source or target vertex is not in the graph yet, will add them*/
void Graph::AddVerticesAndEdgeRange(vector<pair<int, int>>& edgeList)
{
	//int source, target;
	for (auto const &edge : edgeList)
	{
		//source = edge.first;
		//target = edge.second;
		//add_edge(source, target);	  //add edge
		add_edge(edge.first, edge.second);	  //add edge
	}
}


/*Method to get the degree sequence of all vertices in descending order
This only give the degree sequence, not the vertex ID
To get vertex ID sorted by degree sequence use GetNodesSortedByDegree(int count)*/
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


/*Method to get a list of all neighboring/adjacent vertex ID
Parameter:
sourceId: ID of the source vertex which you want to find its neighbors*/
vector<int>& Graph::GetNeighbors(const int &sourceId)
{
	return vertexList.at(sourceId);	//may need to catch out_of_range exception
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


/*Method to get a list of vertices sorted by their degree sequence in descending order
Parameter:
count: the number of expected vertices (start with highest degree sequence) to return
For example, there are 10 vertices in the graph, but you only want the top 4
of the vertices sorted by degree other, then count = 4. If count > # of vertices
in the graph, count = # of vertices*/
vector<int> Graph::GetNodesSortedByDegree(const int & degreeCutOff)
{
	int vertexCount = getNumberOfVertices();
	////check for over estimation of # of vertices in the graph
	//if (count > vertexCount)
	//	count = vertexCount;

	vector<pair<int, int>> degreeOfNode;	  //list of <vertexDegree, vertexID>
	degreeOfNode.reserve(vertexCount);
	vector<int> result;
	result.reserve(vertexCount);

	//get all vertex degrees and corresponding IDs
	for (auto const &vertex : this->vertexList)
	{
		if (vertex.second.size() >= degreeCutOff)
			//pair<int, int> d_nPair = make_pair(vertex.second.size(), vertex.first);
			degreeOfNode.push_back(make_pair(vertex.second.size(), vertex.first));
	}

	//sort by degree, descending order
	//sort(degreeOfNode.begin(), degreeOfNode.end(), greater<pair<int, int>>());
	sort(degreeOfNode.begin(), degreeOfNode.end());

	auto pos = degreeOfNode.begin();

	////get the sorted vertexID sorted by degree
	//for (auto const &iter : degreeOfNode)
	//{
	//	result.push_back(iter.second);
	//}

	//get the sorted vertexID sorted by degree
	for (int i = degreeOfNode.size(); i != 0; i--)
	{
		result.push_back(pos->second);
		advance(pos, 1);
	}

	return result;
}
