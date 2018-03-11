#pragma once
#include "UndirectedGraph.h"
#include "Mapping.h"
#include "MappingTestResult.h"
#include <string>
using namespace std;

namespace ParaMODAImpl
{
   class QueryGraph : public UndirectedGraph
   {
   public:
	  QueryGraph();
	  QueryGraph(string label);
	  ~QueryGraph();

	  bool isComplete(int subgraphSize = -1);
	  bool isTree(int subgraphSize = -1);
		 //public IList<Mapping> ReadMappingsFromFile(string filename)
		 //public string WriteMappingsToFile(ICollection<Mapping> mappings)
	  list<Mapping> removeNonApplicableMappings(list<Mapping> mappings, UndirectedGraph &inputGraph, bool checkInducedMappingOnly = true); //NOT DONE

   private:
	  string identifier;
	  //bool allowParallelEdges;
	  bool isFrequentSubgraph;
   };
}

//class HashList
//{
//public:
//   int operator()(list<int> const &obj) const
//   {
//	  int hashVal = 0;
//	  int size = obj.size();
//	  for (auto const & itr : obj)
//	  {
//		 hashVal += std::hash<int>()(itr);
//	  }
//
//	  return hashVal;
//   }
//};


static bool EqualList(list<int> const &obj1, list<int> const &obj2)
{
	  int size1 = obj1.size();
	  if (obj1.size() != obj2.size())
		 return false;
	  for (auto const& itr1 : obj1)
	  {
		 if (find(obj2.begin(), obj2.end(), itr1) == obj2.end())
			return false;
	  }
	  return true;
};
