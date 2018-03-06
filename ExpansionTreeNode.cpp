#include "ExpansionTreeNode.h";
using namespace QuickGraph;
using namespace ParaMODAImpl;


	int ExpansionTreeNode::getLevel() const
	{
		return privateLevel;
	}

	void ExpansionTreeNode::setLevel(const int &value)
	{
		privateLevel = value;
	}

	std::wstring ExpansionTreeNode::getNodeName() const
	{
		return getQueryGraph() == nullptr ? L"" : getQueryGraph()->Identifier;
	}

	ExpansionTreeNode *ExpansionTreeNode::getParentNode() const
	{
		return privateParentNode;
	}

	void ExpansionTreeNode::setParentNode(ExpansionTreeNode *value)
	{
		privateParentNode = value;
	}

	bool ExpansionTreeNode::getIsRootNode() const
	{
		return getQueryGraph() == nullptr;
	}

	QueryGraph *ExpansionTreeNode::getQueryGraph() const
	{
		return privateQueryGraph;
	}

	void ExpansionTreeNode::setQueryGraph(QueryGraph *value)
	{
		privateQueryGraph = value;
	}

	bool ExpansionTreeNode::Equals(ExpansionTreeNode *obj)
	{
		auto theObj = dynamic_cast<ExpansionTreeNode*>(obj);
		if (theObj->getIsRootNode() && this->getIsRootNode())
		{
			return true;
		}
		
		std::string str1 = getNodeName();
		std::string str2 = theObj->getNodeName();

		if (getNodeName() == theObj->getNodeName())
			return true;
		return false;
	}

	int ExpansionTreeNode::GetHashCode()
	{
		if (getIsRootNode()) {
			return GetHashCode();
		}
		return getQueryGraph->GetHashCode();
	}

	std::string ExpansionTreeNode::ToString()
	{
		std::string retVal = "Node: Name: " + getNodeName() + "; Level - " + getLevel() + "; Is Root - " + getIsRootNode() + "; Number of Query Graph edges -  " + privatQueryGraph.EdgeCount;
		return retVal;
	}

