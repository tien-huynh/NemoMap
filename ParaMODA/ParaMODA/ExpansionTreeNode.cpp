#include "ExpansionTreeNode.h"

int ExpansionTreeNode::getLevel() const
{
	return privateLevel;
}

void ExpansionTreeNode::setLevel(const int &value)
{
	privateLevel = value;
}

std::string ExpansionTreeNode::getNodeName() const
{
	return getQueryGraph() == nullptr ? "" : getQueryGraph()->getIdentifier();
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
	//if (getIsRootNode()) {
	//	return GetHashCode();
	//}
	//return getQueryGraph()->GetHashCode();
	return 0;
}

std::string ExpansionTreeNode::ToString()
{
	std::string retVal = "Node: Name: " + getNodeName() + "; Level - " + to_string(getLevel())  + "; Is Root - " + to_string(getIsRootNode()) + "; Number of Query Graph edges -  " + to_string(privateQueryGraph->getEdgeCount());
	return retVal;
}

ExpansionTreeNode ExpansionTreeNode::BuildThreeNodesTree()
{
	return ExpansionTreeNode();
}
