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

	  list<Mapping> Algorithm2_Modified(QueryGraph queryGraph, UndirectedGraph inputGraph, int numberOfSamples, bool getInducedMappingsOnly);
	  list<Mapping> GetSet(list<pair<list<int>, list<Mapping>>> theMappings);

   };
}
