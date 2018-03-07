#pragma once
#include "Edge.h"
#include "UndirectedGraph.h"
#include<string>
#include<map>
#include<iostream>
#include<iterator>

#define DefaultEdgeNodeVal -999

using namespace std;

class Mapping
{
public:
	Mapping();
	Mapping(const Mapping &mapping);
	Mapping(map<int, int> function, int subGraphEdgeCount);
	~Mapping();

	//Accessors
	int getId() const { return Id; };
	void setId(int id) { Id = id; };
	int getSubGraphEdgeCount() const { return SubGraphEdgeCount; };
	void setSubGraphEdgeCount(int subGraphEdgeCount) { SubGraphEdgeCount = subGraphEdgeCount; };
	map<int, int> getFunction() const { return Function; };
	void setFunction(map<int, int> function) { Function = function; };

	//Methods

	Edge<int>* GetImage(UndirectedGraph<int>* inputGraph, Edge<int>* newlyAddedEdge);
	bool Mapping::operator==(const Mapping &other) const;
	bool Mapping::operator!=(const Mapping &comp) const { return !(*this == comp); };
	string GetMappedNodes();

private:
	int Id;
	int SubGraphEdgeCount;
	map<int, int> Function;
};
ostream& operator<<(ostream& outStream, const Mapping& data);
