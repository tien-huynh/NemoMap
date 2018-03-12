#include "ParaMODAAlgorithm.h"



ParaMODAImpl::ParaMODAAlgorithm::ParaMODAAlgorithm()
{
}


ParaMODAImpl::ParaMODAAlgorithm::~ParaMODAAlgorithm()
{
}


//Method to use ParaMODA algorithm (i.e. Algorithm 5 from the paper)
// Modified from Grochow-Kelis algorithm
// The modification:
//     Instead of traversing all nodes in the query graph (H) for each node in the input graph (G),
//     we simply use just one node h in H to traverse G. This makes it much easier to parallelize 
//     unlike the original algorithm, and eliminate the need for removing visited g from G.
list<ParaMODAImpl::Mapping> ParaMODAImpl::ParaMODAAlgorithm::Algorithm2_Modified(QueryGraph queryGraph, UndirectedGraph inputGraph, int numberOfSamples, bool getInducedMappingsOnly)
{
   if (numberOfSamples <= 0)
	  numberOfSamples = boost::num_vertices(inputGraph.graph);

   list<pair<list<int>, list<Mapping>>> theMappings;
   vector<int> inputGraphDegSeq = inputGraph.GetNodesSortedByDegree(numberOfSamples);

   cout << "Calling ParaMODA Algorithm (i.e. Algo 2-Modified):" << endl;

   list<pair<int,int>>queryGraphEdges = queryGraph.GetEdgeList();
   int h = queryGraph.graph[boost::vertex(0, queryGraph.graph)].id;
   map<int, int> f;

   for (int i = 0; i < inputGraphDegSeq.size(); i++)
   {
	  int g = inputGraphDegSeq[i];

	  if (Utils().CanSupport(queryGraph, h, inputGraph, g))
	  {
		 f[h] = g;
		 list<pair<list<int>, list<Mapping>>> mappings = Utils().IsomorphicExtension(f, queryGraph, queryGraphEdges, inputGraph, getInducedMappingsOnly);

		 if (mappings.size() > 0)
		 {
			for (auto & item : mappings)
			{
			   if (item.second.size() > 1)
			   {
				  item.second = queryGraph.removeNonApplicableMappings(item.second, inputGraph, getInducedMappingsOnly);
			   }
			   list<Mapping> maps;
			   bool found = false;

			   //following block equivalent to this in C#
			   //		if (theMappings.TryGetValue(item.Key, out maps))
			   //---------------------------------------------------------
			   for (auto const & themap : theMappings)
			   {
				  if (EqualList(item.first, themap.first))
				  {
					 maps = list<Mapping>(item.second);
					 found = true;
					 break;
				  }
			   }
			   if (!found)
			   {
				  for (auto & themap : theMappings)
				  {
					 if (EqualList(item.first, themap.first))
					 {
						themap.second = item.second;
						found = true;
						break;
					 }
				  }
				  if (!found)
				  {
					 theMappings.push_back(make_pair(item.first, item.second));
				  }
			   }
			   //---------------------------------------------------------
			}
		 }
	  }
   }
   
   list<Mapping> toReturn = GetSet(theMappings);
   cout << "\nAll iteration tasks completed. Number of mappings found:" << toReturn.size() << endl;
   return toReturn;
}



//Method to flatten sequences into one sequence and remove duplicate
list<ParaMODAImpl::Mapping> ParaMODAImpl::ParaMODAAlgorithm::GetSet(list<pair<list<int>, list<Mapping>>> theMappings)
{
   list<Mapping> toReturn;
   vector<vector<int>> vec;
   for (auto & map : theMappings)
   {
	  toReturn.splice(toReturn.end(), map.second);
   }
   toReturn.unique();
   return toReturn;
}
