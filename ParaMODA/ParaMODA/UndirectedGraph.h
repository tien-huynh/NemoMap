#pragma once
#include <list>
#include <map>
#include <vector>
#include <string>
#include "Edge.h"
using namespace std;
template<typename TVertex>
class UndirectedGraph
{
public:
	UndirectedGraph();
	UndirectedGraph(bool allowParallelEdges);
	bool AddVerticesAndEdge(TVertex source, TVertex target);

	int getEdgeCapacity();
	void setEdgeCapacity(int capacity);

	list<TVertex> GetNeighbors(TVertex vertex);
	list<TVertex> GetNodesSortedByDegree(int count);
	vector<int> GetDegreeSequence();
	//UndirectedGraph* Clone();
	string ToString();
	bool IsDirected();
	bool getAllowParallelEdges();

	bool RemoveVertex(TVertex v);
	void ClearAdjacentEdges(TVertex v);

	bool TryGetEdge(TVertex source, TVertex target, Edge<TVertex> &edge);
	bool ContainsEdge(TVertex source, TVertex target);
	bool getIsVerticesEmpty();
	int getVertexCount();
	vector<TVertex> getVertices();
	bool ContainsVertex(TVertex vertex);
	bool getIsEdgesEmpty();
	int getEdgeCount();
	int AdjacentDegree(TVertex v);
	bool IsAdjacentEdgesEmpty(TVertex v);

private:
	map<TVertex, list<TVertex>> edges;
	map<int, list<int>>::iterator it;
	int edgeCount = 0;
	int edgeCapacity = 4;
	bool isVertex(TVertex value);
	bool allowParallelEdges = true;

};

template<typename TVertex>
inline UndirectedGraph<TVertex>::UndirectedGraph()
{
	edgeCount = 0; 
	edgeCapacity = 4;
	allowParallelEdges = true;
}

template<typename TVertex>
inline UndirectedGraph<TVertex>::UndirectedGraph(bool allowParallelEdges)
{
	edgeCount = 0;
	edgeCapacity = 4;
	this->allowParallelEdges = allowParallelEdges;
}

template<typename TVertex>
inline bool UndirectedGraph<TVertex>::AddVerticesAndEdge(TVertex source, TVertex target)
{
	list<TVertex> nodesConnectedToSource, nodesConnectedToTarget;
	if (isVertex(source))	//is an edge 
	{
		nodesConnectedToSource = edges.find(source)->second;	//add source to nodesConnect 
																//found source in nodesConnect <int>
		if (find(nodesConnectedToSource.begin(), nodesConnectedToSource.end(), target) != nodesConnectedToSource.end())
		{
			return false;
		}
		else
		{
			nodesConnectedToSource.push_back(target);   //add target to nodes Connected 
			edges[source] = nodesConnectedToSource;
			if (isVertex(target))		//target is an edge 
			{
				nodesConnectedToTarget = edges.find(target)->second;
				if ((find(nodesConnectedToTarget.begin(), nodesConnectedToTarget.end(), source) != nodesConnectedToTarget.end()) == false)	//not found
				{
					nodesConnectedToTarget.push_back(source);
					edges[target] = nodesConnectedToTarget;

				}
			}
			else
			{
				list<TVertex> temp;
				temp.push_back(source);
				edges[target] = temp;
			}
		}
	}
	else if (isVertex(target))
	{
		nodesConnectedToTarget = edges.find(target)->second;
		if (find(nodesConnectedToTarget.begin(), nodesConnectedToTarget.end(), source) != nodesConnectedToTarget.end())
			return false;
		else
		{
			nodesConnectedToTarget.push_back(source);
			edges[target] = nodesConnectedToTarget;
			if (isVertex(source))
			{
				nodesConnectedToSource = edges.find(source)->second;
				if (find(nodesConnectedToSource.begin(), nodesConnectedToSource.end(), target) != nodesConnectedToSource.end() == false)
				{
					nodesConnectedToSource.push_back(target);
					edges[source] = nodesConnectedToSource;
				}
			}
			else
			{
				list<TVertex> temp;
				temp.push_back(target);
				edges[source] = temp;
			}
		}
	}
	else  //neither exist 
	{
		list<TVertex> a, b;
		a.push_back(target);
		b.push_back(source);
		edges[source] = a;
		edges[target] = b;
	}
	edgeCount++;
	return true;
}



template<typename TVertex>
inline int UndirectedGraph<TVertex>::getEdgeCapacity()
{
	return edgeCapacity;
}

template<typename TVertex>
inline void UndirectedGraph<TVertex>::setEdgeCapacity(int capacity)
{
	edgeCapacity = capacity;
}

template<typename TVertex>
inline list<TVertex> UndirectedGraph<TVertex>::GetNeighbors(TVertex vertex)
{
	list<TVertex> adjEdges;
	if (isVertex(vertex))
		return edges.find(vertex)->second;
	return adjEdges;
}
/// <summary>
/// NB: The degree sequence of an undirected graph is the non-increasing sequence of its vertex degrees;
/// We return the vertices 
/// </summary>
/// <param name="count">The expected number of items to return. This value is usually less than the <see cref="VertexCount"/></param>
/// <returns></returns>
template<typename TVertex>
inline list<TVertex> UndirectedGraph<TVertex>::GetNodesSortedByDegree(int count)
{
	auto tempList = new map<TVertex, int>;
	//Need to finish 
	list<TVertex> listToReturn;
	return listToReturn;
}
/// <summary>
/// NB: The degree sequence of an undirected graph is the non-increasing sequence of its vertex degrees;
/// </summary>
/// <returns></returns>
template<typename TVertex>
inline vector<int> UndirectedGraph<TVertex>::GetDegreeSequence()
{
	return vector<int>();
}



template<typename TVertex>
inline string UndirectedGraph<TVertex>::ToString()
{
	if (getIsEdgesEmpty())
		return "";
	string sb = "Graph_Edges_";
	for (auto edge : edges)
	{
		//sb += "[" +(edge  + "]";
	}
	return sb;
}

template<typename TVertex>
inline bool UndirectedGraph<TVertex>::IsDirected()
{
	return false;
}

template<typename TVertex>
inline bool UndirectedGraph<TVertex>::getAllowParallelEdges()
{
	return allowParallelEdges;
}

template<typename TVertex>
inline bool UndirectedGraph<TVertex>::RemoveVertex(TVertex v)
{
	ClearAdjacentEdges(v);
	int val = edges.erase(v);
	if (val > 0)
		return true;
	else
		return false;
}

template<typename TVertex>
inline void UndirectedGraph<TVertex>::ClearAdjacentEdges(TVertex v)
{
	list<TVertex> ends = edges[v];
	edgeCount -= ends.size();
	for (auto end : ends)
	{
		list<TVertex> otherEnds;
		if (isVertex(end))
		{
			otherEnds = edges.find(end)->second;
			otherEnds.remove(v);
		}
	}
	ends.clear();
}

template<typename TVertex>
inline bool UndirectedGraph<TVertex>::TryGetEdge(TVertex source, TVertex target, Edge<TVertex>& edge)
{
	return false;
}

template<typename TVertex>
inline bool UndirectedGraph<TVertex>::ContainsEdge(TVertex source, TVertex target)
{
	if (isVertex(source) && isVertex(target))
		return true;
	return false;
}

template<typename TVertex>
inline bool UndirectedGraph<TVertex>::getIsVerticesEmpty()
{
	return edges.size() == 0;
}

template<typename TVertex>
inline int UndirectedGraph<TVertex>::getVertexCount()
{
	return edges.size();
}

template<typename TVertex>
inline vector<TVertex> UndirectedGraph<TVertex>::getVertices()
{
	vector<TVertex> retval;
	for (auto const& element : edges)
	{
		retval.push_back(element.first);
	}
	return retval;
}

template<typename TVertex>
inline bool UndirectedGraph<TVertex>::ContainsVertex(TVertex vertex)
{
	return isVertex(vertex);
}

template<typename TVertex>
inline bool UndirectedGraph<TVertex>::getIsEdgesEmpty()
{
	return (getEdgeCount() == 0);
}

template<typename TVertex>
inline int UndirectedGraph<TVertex>::getEdgeCount()
{
	return edgeCount;
}

template<typename TVertex>
inline int UndirectedGraph<TVertex>::AdjacentDegree(TVertex v)
{
	list<TVertex> _edges;
	if (isVertex(v))
	{
		_edges = edges.find(v)->second;
		return _edges.size();
	}
	return 0;
}

template<typename TVertex>
inline bool UndirectedGraph<TVertex>::IsAdjacentEdgesEmpty(TVertex v)
{
	list<TVertex> _edges;
	if (isVertex(v))
	{
		_edges = edges.find(v)->second;
		return (edges.size() == 0);
	}
	return true;
}

template<typename TVertex>
inline bool UndirectedGraph<TVertex>::isVertex(TVertex value)
{
	it = edges.find(value);
	if (it != edges.end())	//is not an int in map<int, list>
		return true;
	else
		return false;
}

