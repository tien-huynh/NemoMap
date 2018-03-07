#include <deque>
//#include "exceptionhelper.h"
#include "ExpansionTreeNode.h"
#include "AdjacencyGraph.h"
#include "BreadthFirstSearchAlgorithm.h"
template <typename TVertex>
class ExpansionTreeBuilder
{
private:
	int privateNumberOfQueryGraphs = 0;
	std::deque<ExpansionTreeNode*> privateVerticesSorted;
	AdjacencyGraph<ExpansionTreeNode*> *privateExpansionTree;
	void setNumberOfQueryGraphs(const int &value)
	{
		privateNumberOfQueryGraphs = value;
	}
	void setVerticesSorted(const std::deque<ExpansionTreeNode*> &value)
	{
		privateVerticesSorted = value;
	}
	void setExpansionTree(AdjacencyGraph<ExpansionTreeNode*> *value)
	{
		privateExpansionTree = value;
	}
	int _numberOfNodes = 0;

public:
	int getNumberOfQueryGraphs() const
	{
		return privateNumberOfQueryGraphs;
	}

	std::deque<ExpansionTreeNode*> getVerticesSorted() const
	{
		return privateVerticesSorted;
	}

	AdjacencyGraph<ExpansionTreeNode*> *getExpansionTree() const
	{
		return privateExpansionTree;
	}
	ExpansionTreeBuilder();
	ExpansionTreeBuilder(int numberOfNodes);
	void Build();
};