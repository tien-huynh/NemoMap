#include "MappingNodesComparer.h"

	/// <summary>
	/// This compares two <see cref="Mapping"/> nodes are equal. Used in dictionary where these nodes form the key.
	/// The node set of interest is that of the mapping images on G; i.e. the set that form the nodes in the Mapping's InducedSubGraph.
	/// The parameters to be compared are guaranteed to be distinct and of the same length.
	/// </summary>

bool MappingNodesComparer::Equals(vector<int>& x, vector<int>& y)
{
	int count = x.size();
	if (count != y.size())
		return false;
	for (int i = 0; i < count; i++)
	{
		if (find(y.begin(), y.end(), x[i]) != y.end() == false)
			return false;
	}
	return true;
}
