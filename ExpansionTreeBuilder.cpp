#include "stdafx.h"
#include "ExpansionTreeBuilder.h"
//#include "ExpansionTreeNode.h"



/// <summary>
/// 
/// </summary>
/// <param name="numberOfNodes"></param>
ExpansionTreeBuilder::ExpansionTreeBuilder(int numberOfNodes)
{
	_numberOfNodes = numberOfNodes;
	setNumberOfQueryGraphs(1);
	AdjacencyGraph<ExpansionTreeNode*> tempVar();
	setExpansionTree(&tempVar);

	getExpansionTree()->EdgeAdded += [&](void *e)
	{
		e::Target->ParentNode = e::Source;
	};
}

void Build()
{
	ExpansionTreeNode *rootNode;
	switch (_numberOfNodes)
	{
	case 3:
		rootNode = getExpansionTree()->BuildThreeNodesTree();
		setNumberOfQueryGraphs(2);
		break;
	case 4:
		rootNode = getExpansionTree()->BuildFourNodesTree();
		setNumberOfQueryGraphs(6);
		break;
	case 5:
		rootNode = getExpansionTree()->BuildFiveNodesTree();
		setNumberOfQueryGraphs(21);
		break;
	default:
		//throw /*NotSupported*/Exception("Subgraph sizes below 3 and above 5 are not supported, unless you supply a query graph.");
	}
	//TODO: Construct the tree.
	// It turns out there's yet no formula to determine the number of isomorphic trees that can be formed
	// from n nodes; hence no way(?) of writing a general code
	auto bfs = new BreadthFirstSearchAlgorithm<ExpansionTreeNode*>(getExpansionTree());
	bfs->SetRootVertex(rootNode);
	bfs->Compute();

	setVerticesSorted(std::deque<ExpansionTreeNode*>(bfs->VertexColors->Count));
	for (auto item : bfs->VertexColors)
	{
		getVerticesSorted().push_back(item->Key);
	}
	bfs->VertexColors->Clear();
	bfs = nullptr;
	getVerticesSorted().pop_front(); // remove the root
}