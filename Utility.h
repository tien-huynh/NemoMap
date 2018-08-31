#pragma once
#include "Graph.h"
//#include "Mapping.h"
#include "hopscotch_set.h"
#include <string>
#include <chrono>

using namespace std::chrono;
using namespace std;

//struct Mapping_Hash {
//	inline size_t operator()(const ParaMODAImpl::Mapping & map) const {
//		size_t result = 0;
//		for (auto const & itr : map.getFunction())
//		{
//			result += hash<int>()(itr.second);
//		}
//		return result;
//	}
//};

struct Vector_Int_Hash
{
	inline size_t operator()(const vector<int> & obj) const
	{
		size_t result = 0;
		for (auto const & itr : obj)
		{
			result += hash<int>()(itr);
		}
		return result;
	}
};


struct Set_Int_Hash
{
	inline size_t operator()(const tsl::hopscotch_set<int> & obj) const
	{
		size_t result = 0;
		for (auto const & itr : obj)
		{
			result += hash<int>()(itr);
		}
		return result;
	}
};


struct Vector_Int_Comparator
{
	inline bool operator()(const vector<int> & obj1, const vector<int> & obj2) const
	{
		if (obj1.size() != obj2.size())  //different size = not equal
			return false;
		//check for presence of elements of object 1 in object 2
		for (auto const& itr1 : obj1)
		{
			if (!binary_search(obj2.begin(), obj2.end(), itr1))
				return false;
		}
		return true;
	}
};


namespace ParaMODAImpl
{
	int GetMostConstrainedNeighbour(vector<int> &domain, Graph &queryGraph);

	void ChooseNeighboursOfRange(vector<int> &usedRange, Graph &inputGraph, vector<int> &neighborList);

	bool IsNeighbourIncompatible(Graph &inputGraph, const int &n, tsl::hopscotch_map<int, int> &partialMap,
		vector<int> &neighborsOfM);


	bool CanSupport(Graph &queryGraph, int &node_H, Graph &inputGraph, int &node_G);

	int IsomorphicExtension(tsl::hopscotch_map<int, int> &partialMap, Graph &queryGraph
		, Graph &inputGraph, tsl::hopscotch_map<int, vector<int>> & symBreakCondition);
	/*tsl::hopscotch_set<vector<int>, Vector_Int_Hash, Vector_Int_Comparator>	IsomorphicExtension(tsl::hopscotch_map<int, int> &partialMap, 
		Graph &queryGraph, Graph &inputGraph);*/


	vector<vector<int>> IsomorphicExtensionForEquivalenceClass(tsl::hopscotch_map<int, int>& partialMap,
		Graph & queryGraph, Graph & inputGraph, vector<int> & MappedHNodes);


	/*Helper function to compare 2 list objects
	Equal if all elements of object 1 are present in object 2,
	and the elements don't have to be in the same order between objects*/
	bool EqualList(vector<int> const &obj1, vector<int> const &obj2);

	bool EqualDtoH(tsl::hopscotch_map<int, vector<int>> const &obj1, vector<int> const &obj2);

	//Method to use ParaMODA algorithm (i.e. Algorithm 5 from the paper)
	// Modified from Grochow-Kelis algorithm
	// The modification:
	//     Instead of traversing all nodes in the query graph (H) for each node in the input graph (G),
	//     we simply use just one node h in H to traverse G. This makes it much easier to parallelize 
	//     unlike the original algorithm, and eliminate the need for removing visited g from G.
	/*list<Mapping> Algorithm2_Modified(QueryGraph &queryGraph, Graph &inputGraph, int numberOfSamples, bool getInducedMappingsOnly);*/
	long Algorithm2_Modified(Graph &queryGraph, Graph &inputGraph, const int & h);


	//tsl::hopscotch_set<tsl::hopscotch_set<int>, Set_Int_Hash> Algorithm2_Modified_For_Equivalence_Class(Graph & queryGraph, Graph & inputGraph);
	tsl::hopscotch_map<int, vector<int>> Algorithm2_Modified_For_Equivalence_Class(Graph & queryGraph, Graph & inputGraph, const int & fixedNode);

	//tsl::hopscotch_map<int, int> FindCondition(tsl::hopscotch_set<tsl::hopscotch_set<int>, Set_Int_Hash> & equivalenceClass);
	tsl::hopscotch_map<int, vector<int>> FindCondition(vector<int> &mappedHNodes, vector<vector<int>> &theMappings,
		tsl::hopscotch_map<int, vector<int>> &condition, tsl::hopscotch_set<tsl::hopscotch_set<int>, Set_Int_Hash> &equivalenceClass);

	bool CheckSymmetryBreak(const int & fixed, const vector<int> & nodesToCheck, tsl::hopscotch_map<int, int>& partialMap, int & m, int & n);


	long Algorithm_GK(Graph & queryGraph, Graph & inputGraph);

	long FindBestH(Graph & queryGraph);
}