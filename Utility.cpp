/*	Filename:		Utility.cpp
	Description:	Implementation of utility methods to support the main function of NemoMap
	Author:			Tien Huynh
*/
#include "Utility.h"


int ParaMODAImpl::GetMostConstrainedNeighbour(vector<int>& domain, Graph & queryGraph)	//might need to check if all neighbor is mapped
{
	//get all neighbors of already-mapped nodes - NO DUPLICATES
	vector<int> neighborList;
	ChooseNeighboursOfRange(domain, queryGraph, neighborList);

	int neighborListSize = neighborList.size();

	if (neighborListSize == 1)
	{
		return neighborList[0];
	}
	else if (neighborListSize == 0)
	{
		return -1;
	}

	vector<pair<int, int>> constraintRank;
	constraintRank.resize(neighborListSize, { 0,0 });

	for (int i = 0; i < neighborListSize; i++)
	{
		constraintRank[i].second = neighborList[i];
		vector<int> local(queryGraph.GetNeighbors(neighborList[i]));
		for (auto const & loc : local)
		{
			if (binary_search(domain.begin(), domain.end(), loc))
			{
				constraintRank[i].first++;
			}
		}
	}

	vector<pair<int, int>>::iterator constraintRankBegin = constraintRank.begin();
	//Rank neighbor nodes with most already-mapped neighbors
	sort(constraintRankBegin, constraintRank.end(), greater<pair<int, int>>());

	int highestNeighborMapped = constraintRank[0].first;
	int count = neighborListSize;
	for (int i = 1; i < neighborListSize; i++)
	{
		if (constraintRank[i].first < highestNeighborMapped)
		{
			if (i == 1)
				return constraintRank[0].second;
			count = i;
			break;
		}
	}


	//Rank neighbor nodes with highest degree
	for (int i = 0; i < count; i++)
	{
		constraintRank[i].first = queryGraph.GetOutDegree(constraintRank[i].second);
	}

	sort(constraintRankBegin, constraintRankBegin + count, greater<pair<int, int>>());


	int highestDegree = constraintRank[0].first;
	for (int i = 1; i < count; i++)
	{
		if (constraintRank[i].first < highestDegree)
		{
			if (i == 1)
				return constraintRank[0].second;
			count = i;
			break;
		}
	}

	//Rank neighbor nodes with largest neighbor degree sequence
	for (int i = 0; i < count; i++)
	{
		int temp = 0;
		for (auto const & neighborOfPotential : queryGraph.GetNeighbors(constraintRank[i].second))
		{
			temp += queryGraph.GetOutDegree(neighborOfPotential);
		}
		constraintRank[i].first = temp;
	}

	int largestNeighborDegree = constraintRank[0].first;
	for (int i = 1; i < count; i++)
	{
		if (constraintRank[i].first < largestNeighborDegree)
		{
			if (i == 1)
				return constraintRank[0].second;
			break;
		}
	}

	return constraintRank[0].second;
}


void ParaMODAImpl::ChooseNeighboursOfRange(vector<int>& usedRange, Graph & inputGraph, vector<int> & neighborList)
{
	for (auto const &range : usedRange)
	{
		vector<int> local(inputGraph.GetNeighbors(range));
		for (auto const &loc : local)
		{
			if (!binary_search(usedRange.begin(), usedRange.end(), loc))
			{
				neighborList.push_back(loc);
			}
		}
	}

	vector<int>::iterator itrNeighborListBegin = neighborList.begin();
	vector<int>::iterator itrNeighborListEnd = neighborList.end();
	sort(itrNeighborListBegin, itrNeighborListEnd);
	neighborList.erase(unique(itrNeighborListBegin, itrNeighborListEnd), itrNeighborListEnd);
	//neighborList.shrink_to_fit();
}


bool ParaMODAImpl::IsNeighbourIncompatible(Graph & inputGraph, const int & n, tsl::hopscotch_map<int, int>& partialMap, vector<int>& neighborsOfM)
{
	for (auto const & d : partialMap)
	{
		vector<int> neighborsOfFd(inputGraph.GetNeighbors(d.second));
		if (binary_search(neighborsOfM.begin(), neighborsOfM.end(), d.first))
		{
			if (!binary_search(neighborsOfFd.begin(), neighborsOfFd.end(), n))
				return true;
		}
		else
		{
			if (binary_search(neighborsOfFd.begin(), neighborsOfFd.end(), n))
				return true;
		}
	}
	return false;
}


bool ParaMODAImpl::CanSupport(Graph & queryGraph, int &node_H, Graph & inputGraph, int &node_G)
{
	int degreeG = inputGraph.GetOutDegree(node_G);
	int degreeH = queryGraph.GetOutDegree(node_H);
	return degreeG >= degreeH;
}


int ParaMODAImpl::IsomorphicExtension(tsl::hopscotch_map<int, int>& partialMap, Graph & queryGraph, Graph & inputGraph, tsl::hopscotch_map<int, vector<int>> & symBreakCondition)
{

	int listOfIsomorphisms = 0;
	vector<int> partialMapValuesG, partialMapKeysH;;
	//extract list of keys and list of values from partialMap
	for (auto const & map : partialMap)
	{
		partialMapValuesG.push_back(map.second);
		partialMapKeysH.push_back(map.first);
	}
	vector<int> mapValueOriginal(partialMapValuesG);
	vector<int> mapKeyOriginal(partialMapKeysH);

	sort(partialMapKeysH.begin(), partialMapKeysH.end());
	sort(partialMapValuesG.begin(), partialMapValuesG.end());

	if (EqualDtoH(queryGraph.GetVertexList(), partialMapKeysH))
	{
		return 1;
	}

	int m = GetMostConstrainedNeighbour(partialMapKeysH, queryGraph);
	if (m < 0)
		return 0;

	vector<int> neighborsOfM(queryGraph.GetNeighbors(m));

	int bestMappedNeighborOfM;
	for (auto const & neighbor : neighborsOfM)
	{
		if (partialMap.find(neighbor) != partialMap.end())
		{
			bestMappedNeighborOfM = neighbor;
			break;
		}
	}

	vector<int> possibleMappingNodes;
	possibleMappingNodes.reserve(partialMapValuesG.size());

	for (auto const & node : inputGraph.GetNeighbors(partialMap[bestMappedNeighborOfM]))
	{
		if (!binary_search(partialMapValuesG.begin(), partialMapValuesG.end(), node))
		{
			possibleMappingNodes.push_back(node);
		}
	}

	int partialMapKeysHSize(partialMapKeysH.size());
	for (int i = 0; i < partialMapKeysHSize; i++)
	{
		vector<int> neighborsOfmappedGNode(inputGraph.GetNeighbors(mapValueOriginal[i]));
		vector<int> temp;
		if (binary_search(neighborsOfM.begin(), neighborsOfM.end(), mapKeyOriginal[i]))
		{
			for (auto const & node : possibleMappingNodes)
			{
				if (binary_search(neighborsOfmappedGNode.begin(), neighborsOfmappedGNode.end(), node))
				{
					temp.push_back(node);
				}
			}
			possibleMappingNodes = temp;
		}
		else
		{
			for (auto const & node : possibleMappingNodes)
			{
				if (!binary_search(neighborsOfmappedGNode.begin(), neighborsOfmappedGNode.end(), node))
				{
					temp.push_back(node);
				}
			}
			possibleMappingNodes = temp;
		}
	}
	
	for (auto & n : possibleMappingNodes)
	{
		if (!IsNeighbourIncompatible(inputGraph, n, partialMap, neighborsOfM))
		{
			bool skip = false;
			for (auto & condition : symBreakCondition)
			{
				if (!CheckSymmetryBreak(condition.first, condition.second, partialMap, m, n))
				{
					skip = true;
					break;
				}
			}
			if (skip)
				continue;

			tsl::hopscotch_map<int, int> newPartialMap(partialMap);
			newPartialMap[m] = n;

			int subList(IsomorphicExtension(newPartialMap, queryGraph, inputGraph, symBreakCondition));
			listOfIsomorphisms += subList;
		}
	}
	return listOfIsomorphisms;
}


vector<vector<int>> ParaMODAImpl::IsomorphicExtensionForEquivalenceClass(tsl::hopscotch_map<int, int>& partialMap, Graph & queryGraph, Graph & inputGraph, vector<int> & MappedHNodes)
{
	vector<vector<int>> listOfIsomorphisms;
	vector<int> partialMapValuesG, partialMapKeysH;;
	//extract list of keys and list of values from partialMap
	for (auto const & map : partialMap)
	{
		partialMapValuesG.push_back(map.second);
		partialMapKeysH.push_back(map.first);
	}
	vector<int> mapValueOriginal(partialMapValuesG);
	vector<int> mapKeyOriginal(partialMapKeysH);

	sort(partialMapKeysH.begin(), partialMapKeysH.end());
	sort(partialMapValuesG.begin(), partialMapValuesG.end());

	if (EqualDtoH(queryGraph.GetVertexList(), partialMapKeysH))
	{
		MappedHNodes = mapKeyOriginal;
		return vector<vector<int>>(1, mapValueOriginal);
	}


	int m = GetMostConstrainedNeighbour(partialMapKeysH, queryGraph);
	if (m < 0)
		return listOfIsomorphisms;

	vector<int> neighbourRange;
	ChooseNeighboursOfRange(partialMapValuesG, inputGraph, neighbourRange);

	vector<int> neighborsOfM(queryGraph.GetNeighbors(m));
	for (auto const & n : neighbourRange)
	{
		if (!IsNeighbourIncompatible(inputGraph, n, partialMap, neighborsOfM))
		{
			tsl::hopscotch_map<int, int> newPartialMap(partialMap);
			newPartialMap[m] = n;

			vector<vector<int>> subList(IsomorphicExtensionForEquivalenceClass(newPartialMap, queryGraph, inputGraph, MappedHNodes));
			listOfIsomorphisms.reserve(listOfIsomorphisms.size() + subList.size());
			listOfIsomorphisms.insert(listOfIsomorphisms.end(), subList.begin(), subList.end());
		}
	}

	return listOfIsomorphisms;
}


bool ParaMODAImpl::EqualList(vector<int> const & obj1, vector<int> const & obj2)
{
	if (obj1.size() != obj2.size())  //different size = not equal
		return false;
	//check for presence of elements of object 1 in object 2
	vector<int>::const_iterator obj2Begin(obj2.begin());
	vector<int>::const_iterator obj2End(obj2.end());
	for (auto const& itr1 : obj1)
	{
		if (find(obj2Begin, obj2End, itr1) == obj2End)
			return false;
	}
	return true;
}


bool ParaMODAImpl::EqualDtoH(tsl::hopscotch_map<int, vector<int>> const & obj1, vector<int> const & obj2)
{
	if (obj1.size() != obj2.size())  //different size = not equal
		return false;
	//check for presence of elements of object 1 in object 2
	vector<int>::const_iterator obj2Begin(obj2.begin());
	vector<int>::const_iterator obj2End(obj2.end());
	for (auto const& itr1 : obj1)
	{
		if (!binary_search(obj2Begin, obj2End, itr1.first))
			return false;
	}
	return true;
}


long ParaMODAImpl::Algorithm2_Modified(Graph & queryGraph, Graph & inputGraph, const int & h)
{
	tsl::hopscotch_map<int, vector<int>> condition(Algorithm2_Modified_For_Equivalence_Class(queryGraph, queryGraph, h));

	cout << "size condition: " << condition.size() << endl;
	int totalCondition = 0;
	for (auto const & con : condition)
	{
		cout << con.first << " => ";
		for (auto const & i : con.second)
		{
			cout << i << " - ";
		}
		cout << endl;
	}
	cout << endl;

	vector<int> inputGraphDegSeq(inputGraph.GetNodesSortedByDegree(queryGraph.GetOutDegree(h)));

	cout << "h Neighbor size: " << queryGraph.GetNeighbors(h).size() << endl;
	
	tsl::hopscotch_map<int, int> f;
	unsigned long mappingCount(0);

	int inputGraphDegSeqSize(inputGraphDegSeq.size());

	for (int i = 0; i < inputGraphDegSeqSize; i++)
	{
		f[h] = inputGraphDegSeq[i];
		mappingCount += IsomorphicExtension(f, queryGraph, inputGraph, condition);
	}

	cout << "total nodes check: " << findMCount << endl;
	
	string result = "\nSub-graph: Graph Edges:\t";
	vector<pair<int, int>> qGraphs(queryGraph.GetEdgeList());
	int count(0);
	int numgraphs(qGraphs.size());
	//list all edges from query graph 
	for (auto q : qGraphs)
	{
		count++;
		result += "[" + to_string(q.first) + "->" + to_string(q.second) + "]";
		if (count != numgraphs)
			result += ",";
	}
	result += "\tMappings: " + to_string(mappingCount) + "\n";

	cout << result;

	return mappingCount;
}


tsl::hopscotch_map<int, vector<int>> ParaMODAImpl::Algorithm2_Modified_For_Equivalence_Class(Graph & queryGraph, Graph & inputGraph, const int & fixedNode)
{
	//Just choose the first element of queryGraph
	int h(queryGraph.GetVertexList().begin()->first);

	vector<int> inputGraphDegSeq(inputGraph.GetNodesSortedByDegree(queryGraph.GetOutDegree(h)));
	vector<vector<int>> theMappings;
	tsl::hopscotch_map<int, int> f;
	vector<int> mappedHNodes;

	int inputGraphDegSeqSize(inputGraphDegSeq.size());
	for (int i = 0; i < inputGraphDegSeqSize; i++)
	{
		f[h] = inputGraphDegSeq[i];
		vector<vector<int>> mappings(IsomorphicExtensionForEquivalenceClass(f, queryGraph, inputGraph, mappedHNodes));
		theMappings.insert(theMappings.end(), mappings.begin(), mappings.end());
	}

	tsl::hopscotch_map<int, vector<int>> condition;
	tsl::hopscotch_set<tsl::hopscotch_set<int>, Set_Int_Hash> equivalenceClass;

	return FindCondition(mappedHNodes, theMappings, condition, equivalenceClass);
}


tsl::hopscotch_map<int, vector<int>> ParaMODAImpl::FindCondition(vector<int> &mappedHNodes, vector<vector<int>> &theMappings,
	tsl::hopscotch_map<int, vector<int>> &condition, tsl::hopscotch_set<tsl::hopscotch_set<int>, Set_Int_Hash> &equivalenceClass)
{
	if (theMappings.size() == 1)
	{
		return condition;
	}

	vector<tsl::hopscotch_set<int>> equivalenceFilter(mappedHNodes.size(), tsl::hopscotch_set<int>());

	for (auto const & map : theMappings)
	{
		for (int i = 0; i < map.size(); i++)
		{
			equivalenceFilter[i].insert(map[i]);
		}
	}

	int maxSize = equivalenceFilter.begin()->size();
	tsl::hopscotch_set<int> temp;

	if (equivalenceClass.empty())				//MIGHT NEED CHECK----------
		temp = *equivalenceFilter.begin();
	else
		temp = *equivalenceClass.begin();		//---------------------------

	for (auto const & entry : equivalenceFilter)
	{
		if (entry.size() > 1)
		{
			equivalenceClass.insert(entry);
			if (entry.size() > maxSize)
			{
				maxSize = entry.size();
				temp = entry;
			}
		}
	}

	equivalenceClass.erase(temp);

	vector<int> sortedTemp(temp.begin(), temp.end());
	sort(sortedTemp.begin(), sortedTemp.end());

	int fixedNode = sortedTemp[0];

	condition.insert({ fixedNode, sortedTemp });

	vector<vector<int>> newMappings;

	for (auto & map : theMappings)
	{
		for (int i = 0; i < map.size(); i++)
		{
			if (map[i] == fixedNode && map[i] == mappedHNodes[i])
			{
				newMappings.push_back(map);
			}
		}
	}
	
	FindCondition(mappedHNodes, newMappings, condition, equivalenceClass);

	return condition;
}

bool ParaMODAImpl::CheckSymmetryBreak(const int & fixed, const vector<int> & nodesToCheck, tsl::hopscotch_map<int, int> & partialMap, int & m, int & n)
{
	if (!binary_search(nodesToCheck.begin(), nodesToCheck.end(), m)
		|| ((m != fixed) && partialMap.find(fixed) == partialMap.end()))
	{
		return true;
	}

	int fixedLabel = (m == fixed) ? n : partialMap[fixed];

	if (m == fixed)
	{
		for (auto const & node : nodesToCheck)
		{
			if (partialMap.find(node) != partialMap.end())
			{
				if (partialMap[node] < fixedLabel)
					return false;
			}
		}
		return true;
	}
	else
		return n >= fixedLabel;
}