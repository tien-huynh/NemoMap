#include "ParaMODAAlgorithm.h"



ParaMODAImpl::ParaMODAAlgorithm::ParaMODAAlgorithm()
{
}


ParaMODAImpl::ParaMODAAlgorithm::~ParaMODAAlgorithm()
{
}

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
			   for (auto const & themap : theMappings)
			   {
				  if (EqualList(item.first, themap.first))
				  {
					 maps = list<Mapping>(item.second);
					 found = true;
					 break;
				  }
			   }
			   if (!found) //need CHECK in this and Utils.cpp
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
			}
		 }
	  }
   }
   
   list<Mapping> toReturn = GetSet(theMappings);
   cout << "ParaMODA Algorithm (i.e. Algo 2-Modified)\nAll iteration tasks completed. Number of mappings found:" << toReturn.size() << endl;
   return toReturn;
}

//NOT NEEDED: used to check vertex print out
bool vecComp(const vector<int> &a, const vector<int> &b)
{
   for (int i = 0; i < a.size(); i++)
   {
	  if (a[i] != b[i])
		 return a[i] < b[i];
	  if (i == a.size() - 1 && a[i] == b[i])
		 return false;
   }
   return (a.front() < b.front());
}

list<ParaMODAImpl::Mapping> ParaMODAImpl::ParaMODAAlgorithm::GetSet(list<pair<list<int>, list<Mapping>>> theMappings)
{
   list<Mapping> toReturn;
   vector<vector<int>> vec;
   for (auto & map : theMappings)
   {
	  toReturn.splice(toReturn.end(), map.second);
   }
   toReturn.unique();
   /*for (auto const &itr : toReturn)
   {
	  for (auto const & map : itr.getFunction())
	  {
		 cout << map.second << "--";
	  }
	  cout << endl;
   }
   for (auto const &itr : toReturn)
   {
	  vec.push_back(vector<int>());
	  for (auto const & map : itr.getFunction())
	  {
		 vec.back().push_back(map.second);
	  }
	  sort(vec.back().begin(), vec.back().end());
   }
   sort(vec.begin(), vec.end(), vecComp);

   for (auto const &itr : vec)
   {
   for (auto const & map : itr)
   {
   cout << map << "--";
   }
   cout << endl;
   }*/

   return toReturn;
}
