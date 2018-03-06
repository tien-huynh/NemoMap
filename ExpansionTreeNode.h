
#include <string>

using namespace QuickGraph;

namespace ParaMODAImpl
{

	class ExpansionTreeNode
	{
	private:
		int privateLevel = 0;
		ExpansionTreeNode *privateParentNode;
		QueryGraph *privateQueryGraph;

	public:
		int getLevel() const;
		void setLevel(const int &value);
		/// <summary>
		/// A name to identify this node, especially useful
		/// </summary>
		std::string getNodeName() const;
		ExpansionTreeNode *getParentNode() const;
		void setParentNode(ExpansionTreeNode *value);
		bool getIsRootNode() const;

		QueryGraph *getQueryGraph() const;
		void setQueryGraph(QueryGraph *value);

		bool Equals(ExpansionTreeNode *obj); //override;

		int GetHashCode();// override;

		std::string ToString();// override;
	};
}
