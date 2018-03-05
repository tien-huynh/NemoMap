#include "MappingNodesComparer.hpp"

namespace ParaMODA.Impl
{
    /// <summary>
    /// This compares two <see cref="Mapping"/> nodes are equal. Used in dictionary where these nodes form the key.
    /// The node set of interest is that of the mapping images on G; i.e. the set that form the nodes in the Mapping's InducedSubGraph.
    /// The parameters to be compared are guaranteed to be distinct and of the same length.
    /// </summary>
    class MappingNodesComparer : EqualityComparer<IList<int>>
    {
        public bool Equals(IList<int> x, IList<int> y)
        {
            int count = x.Count;
            if (count != y.Count) return false;
            
            for (int i = 0; i < count; i++)
            {
                if (!y.Contains(x[i]))
                {
                    return false;
                }
            }
            return true;
        }
        
        public int GetHashCode(IList<int> obj)
        {
            int hash = 0;
            for (int i = obj.Count - 1; i > -1; i--)
            {
                hash += obj[i].GetHashCode();
            }
            return hash;
        }
    }
}
