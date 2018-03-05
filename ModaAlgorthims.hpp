#ifndef ModaAlgorthims_hpp
#define ModaAlgorthims_hpp

#include <stdio.h>
#include <System.Runtime.CompilerServices>

class ModaAlgorthims
{
    internal static MappingNodesComparer MappingNodesComparer;
    static ModaAlgorithms();
private:
    private static ExpansionTreeBuilder<int> _builder;
    private static ExpansionTreeNode GetNextNode();

public:
    public static void BuildTree(int subgraphSize);
    public static bool UseModifiedGrochow();

};
#endif /* ModaAlgorthims_hpp */
