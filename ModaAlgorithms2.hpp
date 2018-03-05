#ifndef ModaAlgorithms2_hpp
#define ModaAlgorithms2_hpp

#include <stdio.h>
#include <QuickGraph.h>;
#include <System>;
#include <System.Collections.Generic>;
#include <System.Linq>;

using namespace ParaMODAImpl;

class ModaAlgorithms2
{
private:
public:
    static ICollection<Mapping> Algorithm2(QueryGraph queryGraph, UndirectedGraph<int> inputGraphClone, int numberOfSamples, bool getInducedMappingsOnly);
    
    
}

#endif /* ModaAlgorithms2_hpp */
