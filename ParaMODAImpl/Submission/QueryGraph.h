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
	  //public IList<Mapping> ReadMappingsFromFile(string filename)			  NOT IMPLEMENTED YET
	  //public string WriteMappingsToFile(ICollection<Mapping> mappings)	  NOT IMPLEMENTED YET

	  /*Method to remove incorrect mappings between Query graph & Input graph
	  Parameter:
				  mappings: list of mappings to be checked
				  inputGraph: input graph
				  checkInducedMappingOnly: not sure
	  Return: list of mappings with incorrect map removed*/
	  list<Mapping> removeNonApplicableMappings(list<Mapping> mappings, UndirectedGraph &inputGraph, bool checkInducedMappingOnly = true); //NOT DONE

   private:
	  string identifier;
	  //bool allowParallelEdges;
	  bool isFrequentSubgraph;
   };
}

//class HashList				 NOT NEEDED NOW
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


/*Helper function to compare 2 list objects
	  Equal if all elements of object 1 are present in object 2,
	  and the elements don't have to be in the same order between objects*/
static bool EqualList(list<int> const &obj1, list<int> const &obj2)
{
	  int size1 = obj1.size();
	  if (obj1.size() != obj2.size())  //different size = not equal
		 return false;
	  //check for presence of elements of object 1 in object 2
	  for (auto const& itr1 : obj1)
	  {
		 if (find(obj2.begin(), obj2.end(), itr1) == obj2.end())
			return false;
	  }
	  return true;
};
