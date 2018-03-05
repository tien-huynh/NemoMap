#ifndef MappingNodesComparer_hpp
#define MappingNodesComparer_hpp

#include <stdio.h>
#include <System.Collections.Generic>;
#include <System.Linq>;

using namespace ParaMODAImpl;

class MappingNodesComparer
{

public:
    bool Equals(IList<int> x, IList<int> y);
    int GetHashCode(IList<int> obj);
}

#endif /* MappingNodesComparer_hpp */
