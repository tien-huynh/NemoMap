/*	Filename:		Utility.h
	Description:	Declaration of utility methods to support the main function of NemoMap
	Author:			Tien Huynh
*/

#pragma once

#include "Graph.h"
#include "hopscotch_set.h"
#include <string>
#include <chrono>

using namespace std::chrono;
using namespace std;


/*	Custom hash function for vector<int> to support hash map */
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


/*	Custom hash function for set<int> to support hash map */
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


/*	Custom comparator function for vector<int> to support set data structure
	*****NOTE*****: no longer needed for current implementation */
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
	/*	Method to find the most constrained neighboring node of mapped nodes in the query graph.
			The selected node would be used to start the next mapping round to the target network, since the
			constraints help to reduce possible branching out of the recursive mapping function, thus improve runtime performance
			The selection process involves three ranking levels (if there is no tie with the 1st ranked node, we break and choose that 1st node):
				(1) Rank neighbor nodes with most already-mapped neighbors
				(2) Rank neighbor nodes with highest out degree
				(3) Rank neighbor nodes with largest neighbor degree sequence
			At any level if there is a tie between the top ranked nodes, we move to the next level to find the best node. If there's
			still a tie after level 3, we arbitraliry choose 1 node from the tie group

		@param
			domain: the current partial mapping of query graph to target graph
			queryGraph: reference to the query graph
		@return
			The ID number of the most constrained node to continue the mapping process*/
	int GetMostConstrainedNeighbour(vector<int> &domain, Graph &queryGraph);


	/*	Method to get all neighbors of a set of nodes in a graph (no duplicate neighbors allowed)

		@param
			usedRange: the IDs of the target set of nodess
			inputGraph: the graph in question
			neighborList: reference to the return list of neighbors (used to avoid copy operation in return statement) */
	void ChooseNeighboursOfRange(vector<int> &usedRange, Graph &inputGraph, vector<int> &neighborList);


	/*	Method to check if a neighbor node n of the target graph could be mapped to a node m of the query graph
		For more information please see the research paper of NemoMap and/or Grochow-Kellis' paper
		"Network Motif Discovery Using Subgraph Enumeration and Symmetry-Breaking"

		@param
			inputGraph: the target graph
			n: ID of the node n of the target graph
			partialMap: the current partial mapping from query graph to target graph
			neighborsOfM: the list of neighbors of node m of the query graph
		@return
			True if node n can be mapped to node m; False otherwise*/
	bool IsNeighbourIncompatible(Graph &inputGraph, const int &n, tsl::hopscotch_map<int, int> &partialMap,
		vector<int> &neighborsOfM);


	/*	Method to check if a node g in the target graph can support node h in the query graph using out degree
			This method acts as a preliminary check for the IsNeighbourIncompatible() above as it filter out the
			possible candidate nodes of the target graph to map to a node in the query graph
			For example: Node H of the query graph has out degree = 5
				If node G of the target graph has out degree < 5, G can't be mapped to H for sure
				Else node G would be a candidate to map to node H, but further analysis with neighbor capacity needs
					to be done to confirm a mapping (analyze in IsNeighbourIncompatible())

		@param
			queryGraph: reference to the query graph
			node_H: node h of the query graph
			inputGraph: reference to the target graph
			node_G: node g of the target graph
		@return
			True if node g can support node h; False otherwise*/
	bool CanSupport(Graph &queryGraph, int &node_H, Graph &inputGraph, int &node_G);


	/*	Method to count all of the isomorphic extensions (no duplicates) of a partial map between the query graph and the target graph
			This method INCLUDES Grochow-Kellis' symmetry breaking technique to early-abort recursive calls -> significantly reduced runtime
			and eliminate duplicate mapping 
			For more information please see Grochow-Kellis' paper "Network Motif Discovery Using Subgraph Enumeration and Symmetry-Breaking"

		@param
			partialMap: the current partial mapping from query graph to target graph
			queryGraph: reference to the query graph
			inputGraph: reference to the target graph
			symBreakCondition: set of symmetry-breaking conditions
		@return
			The count of all of the isomorphic extensions*/
	int IsomorphicExtension(tsl::hopscotch_map<int, int> &partialMap, Graph &queryGraph
		, Graph &inputGraph, tsl::hopscotch_map<int, vector<int>> & symBreakCondition);


	/*	Helper method to find all of the isomorphic extensions of a partial map between the query graph and itself
			This method is used to help find the set of symmetry breaking conditions
			For more information please see Grochow-Kellis' paper "Network Motif Discovery Using Subgraph Enumeration and Symmetry-Breaking"

			@param
				partialMap: the current partial mapping from query graph to target graph
				queryGraph: reference to the query graph
				inputGraph: reference to the query graph	*****TO DO*****: not needed, need to adjust from just copy IsomorphicExtension()
				MappedHNodes: variable to hold the initial ordering of nodes in query graph (used to figured out exact mapping)
			@return
				The list of all of the isomorphic extensions between the query graph and itself*/
	vector<vector<int>> IsomorphicExtensionForEquivalenceClass(tsl::hopscotch_map<int, int>& partialMap,
		Graph & queryGraph, Graph & inputGraph, vector<int> & MappedHNodes);


	/*	Helper function to compare 2 vector<int> objects
		Equal if all elements of object 1 are present in object 2,
		and the elements don't have to be in the same order between objects
		*****NOTE*****: not needed in the current implementation, succeed by EqualDtoH()*/
	bool EqualList(vector<int> const &obj1, vector<int> const &obj2);


	/*	Helper function to check if the list of keys of obj1 (D) is equal to obj2 (H)
		Equal if all elements of object 1's keys are present in object 2,
		and the elements don't have to be in the same order between objects*/
	bool EqualDtoH(tsl::hopscotch_map<int, vector<int>> const &obj1, vector<int> const &obj2);

	/*	Method to use NemoMap algorithm (i.e. Algorithm 5 from the NemoMap paper)
		***Modified from Grochow-Kelis algorithm***
		The modification:
			Instead of traversing all nodes in the query graph (H) for each node in the input graph (G),
			we simply use just one node h in H to traverse G. This makes it much easier to parallelize 
			unlike the original algorithm, and eliminate the need for removing visited g from G.
		For more information please see the research paper of NemoMap and/or Grochow-Kellis' paper
		"Network Motif Discovery Using Subgraph Enumeration and Symmetry-Breaking"

		@param
			queryGraph: reference to the query graph H
			inputGraph: reference to the target graph G
			h: the starting node h of H (should be the most constrained node of H -> first rank by out-degree; second rank by neighbor degree sequence)
		@return
			The count of all of possible mappings of the query graph to the target graph*/
	long Algorithm2_Modified(Graph &queryGraph, Graph &inputGraph, const int & h);


	/*	Method to find the symmetry-breaking conditions by Grochow-Kellis. It starts by choosing one node to be the anchor point and create conditions from
			that anchor point using equivalence classes. Each equivalence class contains the nodes which are symmetrical i.e. starting the mapping
			from each of those nodes will create duplicate mapping. So we only need to randomly pick one representative node from each equivalence class to start mapping from
		For more information please see the research paper of NemoMap and/or Grochow-Kellis' paper
		"Network Motif Discovery Using Subgraph Enumeration and Symmetry-Breaking"

		@param
			queryGraph: reference to the query graph
			inputGraph: reference to the query graph	*****TO DO*****: not needed, need to adjust from just copy Algorithm2_Modified()
			fixedNode: the node that we choose to be fixed as the anchor for symmetry
		@return
			a set of symmetry-breaking conditions for each representative node from each equivalence class*/
	tsl::hopscotch_map<int, vector<int>> Algorithm2_Modified_For_Equivalence_Class(Graph & queryGraph, Graph & inputGraph, const int & fixedNode);


	/*	Method to find the symmetry-breaking conditions by Grochow-Kellis.
		For more information please see the research paper of NemoMap and/or Grochow-Kellis' paper
		"Network Motif Discovery Using Subgraph Enumeration and Symmetry-Breaking"
		*****NOTE*****: should combine this with Algorithm2_Modified_For_Equivalence_Class()
		*/
	tsl::hopscotch_map<int, vector<int>> FindCondition(vector<int> &mappedHNodes, vector<vector<int>> &theMappings,
		tsl::hopscotch_map<int, vector<int>> &condition, tsl::hopscotch_set<tsl::hopscotch_set<int>, Set_Int_Hash> &equivalenceClass);


	/*	Method to check if a mapping from node m of query graph to node n of target graph satisfy the symmetry-breaking conditions
		For more information please see the research paper of NemoMap and/or Grochow-Kellis' paper
		"Network Motif Discovery Using Subgraph Enumeration and Symmetry-Breaking"

		@param
			fixed: the representative node from each equivalence class
			nodesToCheck: the symmetry-breaking conditions
			partialMap: the current partial mapping from query graph to target graph
			m: ID number of node m of query graph
			n: ID number of node n of target graph
		@return
			True if the symmetry-breaking condition is satisfied and the mapping is okay, False == mapping not okay*/
	*/
	bool CheckSymmetryBreak(const int & fixed, const vector<int> & nodesToCheck, tsl::hopscotch_map<int, int>& partialMap, int & m, int & n);


	//long FindBestH(Graph & queryGraph);
}