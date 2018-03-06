#include <deque>
//#include "exceptionhelper.h"
#include "ExpansionTreeNode.h"

using namespace QuickGraph;
using namespace QuickGraph::Algorithms::Search;
using namespace ParaMODAImpl;
	class ExpansionTreeBuilder
	{
	private:
		int privateNumberOfQueryGraphs = 0;
		std::deque<ExpansionTreeNode*> privateVerticesSorted;
		AdjacencyGraph<ExpansionTreeNode*> *privateExpansionTree;

		int _numberOfNodes = 0;
	public:
		int getNumberOfQueryGraphs() const
		{
			return privateNumberOfQueryGraphs;
		}
		void setNumberOfQueryGraphs(const int &value)
		{
			privateNumberOfQueryGraphs = value;
		}
		std::deque<ExpansionTreeNode*> getVerticesSorted() const
		{
			return privateVerticesSorted;
		}
		void setVerticesSorted(const std::deque<ExpansionTreeNode*> &value)
		{
			privateVerticesSorted = value;
		}
		AdjacencyGraph<ExpansionTreeNode*> *getExpansionTree() const
		{
			return privateExpansionTree;
		}
		void setExpansionTree(AdjacencyGraph<ExpansionTreeNode*> *value)
		{
			privateExpansionTree = value;
		}


		ExpansionTreeBuilder(int numberOfNodes);
		ExpansionTreeBuilder();

		void Build();
	};

