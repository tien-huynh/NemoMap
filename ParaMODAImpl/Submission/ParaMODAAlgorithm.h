#pragma once
#include "Mapping.h"
#include "UndirectedGraph.h"
#include "QueryGraph.h"
#include "Utils.h"
#include <iostream>
using namespace std; 

namespace ParaMODAImpl
{
   class ParaMODAAlgorithm
   {
   public:
	  ParaMODAAlgorithm();
	  ~ParaMODAAlgorithm();

	  //Method to use ParaMODA algorithm (i.e. Algorithm 5 from the paper)
	  // Modified from Grochow-Kelis algorithm
	  // The modification:
	  //     Instead of traversing all nodes in the query graph (H) for each node in the input graph (G),
	  //     we simply use just one node h in H to traverse G. This makes it much easier to parallelize 
	  //     unlike the original algorithm, and eliminate the need for removing visited g from G.
	  list<Mapping> Algorithm2_Modified(QueryGraph queryGraph, UndirectedGraph inputGraph, int numberOfSamples, bool getInducedMappingsOnly);

	  //Method to flatten sequences into one sequence and remove duplicate
	  list<Mapping> GetSet(list<pair<list<int>, list<Mapping>>> theMappings);

   };
}
