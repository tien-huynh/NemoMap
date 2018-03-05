#include "ModaAlgorthims.hpp"

static ModaAlgorthims()
{
    MappingNodesComparer = new MappingNodesComparer();
}

bool UseModifiedGrochow()
{
    //TODO: This method says "If true, the program will
    //use my modified Growchow's algorithm (Algo 2)", and
    //then it has "{get; set;}" after the method header.
    //Need to figure out how to implement this...
}

void BuildTree(int subgraphSize)
{
    _builder = new ExpansionTreeBuilder<int>(subgraphSize);
    _builder.Build();
}

static ExpansionTreeNode GetNextNode()
{
    if (_builder.VerticesSorted.Count > 0)
    {
        return _builder.VerticesSorted.Dequeue();
    }
    return null;
}
