#pragma once
#include<string>
#include<map>
#include<iostream>
#include<iterator>
#include "hopscotch_map.h"

#define DefaultEdgeNodeVal -999

using namespace std;

namespace ParaMODAImpl
{
   class Mapping
   {
   public:
	  Mapping();
	  Mapping(const Mapping &mapping);
	  //Mapping(tsl::hopscotch_map<int, int> function, int subGraphEdgeCount);
	  Mapping(tsl::hopscotch_map<int, int> function);
	  ~Mapping();

	  //Accessors
	  int getId() const { return Id; };
	  void setId(int id) { Id = id; };
	  int getSubGraphEdgeCount() const { return SubGraphEdgeCount; };
	  void setSubGraphEdgeCount(int subGraphEdgeCount) { SubGraphEdgeCount = subGraphEdgeCount; };
	  tsl::hopscotch_map<int, int> getFunction() const { return Function; };
	  void setFunction(tsl::hopscotch_map<int, int> function) { Function = function; };

	  //Methods
	  //QuickGraph::Edge<int>^ GetImage(QuickGraph::UndirectedGraph<int>^ inputGraph, QuickGraph::Edge<int>^ newlyAddedEdge);		NEED FURTHER IMPLEMENT

	  //Overload equal operator for comparing Mapping objects
	  //	  all <key,value> pairs must be the same in both objects
	  bool operator==(const Mapping &other) const;

	  //Overload not equal operator for comparing Mapping objects
	  bool operator!=(const Mapping &comp) const { return !(*this == comp); };
	  string GetMappedNodes();

   private:
	  int Id;
	  int SubGraphEdgeCount;
	  tsl::hopscotch_map<int, int> Function;
   };

   //overload output operators
   ostream& operator<<(ostream& outStream, const Mapping& data);
}
