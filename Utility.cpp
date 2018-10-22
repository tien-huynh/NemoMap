#include "Utility.h"

int findMCount = 0;


int ParaMODAImpl::GetMostConstrainedNeighbour(vector<int>& domain, Graph & queryGraph)	//might need to check if all neighbor is mapped
{
	//get all neighbors of already-mapped nodes - NO DUPLICATES
	vector<int> neighborList;
	ChooseNeighboursOfRange(domain, queryGraph, neighborList);
	//findMCount -= neighborList.size();

	int neighborListSize = neighborList.size();

	if (neighborListSize == 1)
	{
		//findMCount += 4;
		return neighborList[0];
	}
	else if (neighborListSize == 0)
	{
		//findMCount += 4;
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
	//int count = 0;
	int count = neighborListSize;
	for (int i = 1; i < neighborListSize; i++)
	{
		if (constraintRank[i].first < highestNeighborMapped)
		{
			if (i == 1)
				//findMCount += 3;
				return constraintRank[0].second;
			//count = i - 1;
			count = i;
			break;
		}
	}


	//Rank neighbor nodes with highest degree
	for (int i = 0; i < count; i++)
	{
		//int temp = queryGraph.GetOutDegree(constraintRank[i].second);
		//constraintRank[i].first = temp;
		constraintRank[i].first = queryGraph.GetOutDegree(constraintRank[i].second);
	}

	sort(constraintRankBegin, constraintRankBegin + count, greater<pair<int, int>>());
	//sort(constraintRankBegin, constraintRankBegin + count);


	int highestDegree = constraintRank[0].first;
	for (int i = 1; i < count; i++)
	{
		if (constraintRank[i].first < highestDegree)
		{
			if (i == 1)
				//findMCount += 2;
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
		//constraintRank[i].first = queryGraph.GetOutDegree(constraintRank[i].second);
	}

	int largestNeighborDegree = constraintRank[0].first;
	for (int i = 1; i < count; i++)
	{
		if (constraintRank[i].first < largestNeighborDegree)
		{
			if (i == 1)
				//findMCount += 2;
				return constraintRank[0].second;
			//count = i;
			break;
		}
	}

	//findMCount += 1;
	return constraintRank[0].second;
}


void ParaMODAImpl::ChooseNeighboursOfRange(vector<int>& usedRange, Graph & inputGraph, vector<int> & neighborList)
{
	//vector<int>::iterator itrUsedRangeBegin = usedRange.begin();
	//vector<int>::iterator itrUsedRangeEnd = usedRange.end();

	for (auto const &range : usedRange)
	{
		vector<int> local(inputGraph.GetNeighbors(range));
		for (auto const &loc : local)
		{
			//equivalent to this in C#
			//		 if (!usedRange.Contains(loc))
			//if (!binary_search(itrUsedRangeBegin, itrUsedRangeEnd, loc
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
	//vector<int>::iterator itrNeighborsOfMBegin = neighborsOfM.begin();
	//vector<int>::iterator itrNeighborsOfMEnd = neighborsOfM.end();

	for (auto const & d : partialMap)
	{
		vector<int> neighborsOfFd(inputGraph.GetNeighbors(d.second));
		//if (binary_search(itrNeighborsOfMBegin, itrNeighborsOfMEnd, d.first))
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
//tsl::hopscotch_set<vector<int>, Vector_Int_Hash, Vector_Int_Comparator> ParaMODAImpl::IsomorphicExtension(tsl::hopscotch_map<int, int>& partialMap, Graph & queryGraph, Graph & inputGraph)
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
		//cout << endl;
		return 1;

		//for (int i = 0; i < mapKeyOriginal.size(); i++)
		//{
		//	cout << mapKeyOriginal[i] << "->" << mapValueOriginal[i] << "  --  ";
		//}
		//cout << endl;

		//return vector<vector<int>>(1, mapValueOriginal);

		//return tsl::hopscotch_set<vector<int>, Vector_Int_Hash, Vector_Int_Comparator>({ partialMapValuesG });
	}


	int m = GetMostConstrainedNeighbour(partialMapKeysH, queryGraph);
	if (m < 0)
		return 0;


	//int bestMappedNeighborOfM;
	//for (auto const & neighbor : queryGraph.GetNeighbors(m))
	//{
	//	if (partialMap.find(neighbor) != partialMap.end())
	//	{
	//		bestMappedNeighborOfM = neighbor;
	//		break;
	//	}
	//}

	//vector<int> possibleMappingNodes;

	//for (auto const & neighbor : inputGraph.GetNeighbors(partialMap[bestMappedNeighborOfM]))
	//{
	//	if (!binary_search(partialMapValuesG.begin(), partialMapValuesG.end(), neighbor))
	//	{
	//		possibleMappingNodes.push_back(neighbor);
	//	}
	//}

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
	//for (int i = 0; i < partialMapKeysH.size(); i++)
	{
		vector<int> neighborsOfmappedGNode(inputGraph.GetNeighbors(mapValueOriginal[i]));
		vector<int> temp;
		if (binary_search(neighborsOfM.begin(), neighborsOfM.end(), mapKeyOriginal[i]))
		{
			//set_intersection(possibleMappingNodes.begin(), possibleMappingNodes.end(), 
			//	neighborsOfmappedGNode.begin(), neighborsOfmappedGNode.end(), back_inserter(temp));

			//possibleMappingNodes = temp;

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
			//set_difference(possibleMappingNodes.begin(), possibleMappingNodes.end(), 
			//	neighborsOfmappedGNode.begin(), neighborsOfmappedGNode.end(), back_inserter(temp));

			//possibleMappingNodes = temp;

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



	//ChooseNeighboursOfRange(partialMapValuesG, inputGraph, possibleMappingNodes);


	//findMCount -= neighbourRange.size();

	//partialMapValuesG.clear();
	//partialMapValuesG.shrink_to_fit();
	//partialMapKeysH.clear();
	//partialMapKeysH.shrink_to_fit();

	//cout << mapKeyOriginal[0] << " - "<<mapValueOriginal[0] << endl;

	//vector<int> neighborsOfM(queryGraph.GetNeighbors(m));
	//cout << "neighborRange Size: "<<neighbourRange.size() << endl;
	
	//tsl::hopscotch_map<int, int> inputGraphLabeled(inputGraph.GetVertexLabeledList());

	//cout << "Labeled Size: "<<inputGraphLabeled.size() << endl;
	//for (auto const & i : inputGraphLabeled)
	//{
	//	cout << i.first << " == " << i.second << endl;
	//}


	//for (auto & i : symBreakCondition)
	//{
	//	cout << i.first << "<" << i.second << endl;
	//}
	//try {
	//	cout << "test = " << symBreakCondition.at(abs(-6));
	//}
	//catch (out_of_range)
	//{
	//	cout << "ERROR with map" << endl;
	//}

	//findMCount += possibleMappingNodes.size();

	//cout << "Possible neighbor = " << possibleMappingNodes.size() << endl;

	//for (auto & n : neighbourRange)


	//if (symBreakCondition.size() != 0)	//To save time for non-symmetry query graphs
	//{
		for (auto & n : possibleMappingNodes)
		{
			if (!IsNeighbourIncompatible(inputGraph, n, partialMap, neighborsOfM))
			{

				//try
				//{
				//	int compareNodeOfH = symBreakCondition.at(m);
				//	//cout <<endl<< "m = " << m << ": n = " << n << endl;
				//	//cout << "compareNodeOfH = " << compareNodeOfH << endl;
				//	//cout << "Partial Map: " << endl;

				//	//for (auto const & i : partialMap)
				//	//{
				//	//	cout << i.first << "->" << i.second << endl;
				//	//}

				//	//cout << compareNodeOfH <<" BREAKING " << m << endl;
				//	try
				//	{
				//		int compareNodeOfG = partialMap.at(compareNodeOfH);
				//		//cout << "BREAKING_2" << endl;
				//		//cout << "compareNodeOfG = " << compareNodeOfG << endl;
				//		if (inputGraphLabeled[compareNodeOfG] < inputGraphLabeled[n])
				//			continue;

				//	}
				//	catch (out_of_range)
				//	{
				//		//cout << "BREAKING_2_OUT" << endl;
				//		//if (inputGraphLabeled[m] > inputGraphLabeled[n])
				//		//	continue;
				//		//cout << "BREAKING_2_OUT" << endl;
				//		//if (inputGraphLabeled[mapValueOriginal[0]] > inputGraphLabeled[n])
				//		//	continue;
				//	}
				//}
				//catch (out_of_range)
				//{
				//	//cout << "OUT: m = " << m <<  ": n = " << n <<endl;
				//	try 
				//	{
				//		int compareNodeOfH = symBreakCondition.at(-m);
				//		try
				//		{
				//			int compareNodeOfG = partialMap.at(compareNodeOfH);
				//			//cout << "BREAKING_2" << endl;
				//			//cout << "compareNodeOfG = " << compareNodeOfG << endl;
				//			if (inputGraphLabeled[compareNodeOfG] > inputGraphLabeled[n])
				//				continue;

				//		}
				//		catch (out_of_range)
				//		{
				//		}
				//	}
				//	catch (out_of_range)
				//	{
				//	}
				//}

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
				//cout << m << " - ";
				//cout << m << " - " << n <<endl;

				int subList(IsomorphicExtension(newPartialMap, queryGraph, inputGraph, symBreakCondition));
				listOfIsomorphisms += subList;
			}
		}
		return listOfIsomorphisms;
	//}
	//else
	//{
	//	for (auto & n : possibleMappingNodes)
	//	{
	//		if (!IsNeighbourIncompatible(inputGraph, n, partialMap, neighborsOfM))
	//		{
	//			tsl::hopscotch_map<int, int> newPartialMap(partialMap);
	//			newPartialMap[m] = n;

	//			//cout << m << " - " << n <<endl;

	//			int subList(IsomorphicExtension(newPartialMap, queryGraph, inputGraph, symBreakCondition));
	//			listOfIsomorphisms += subList;
	//		}
	//	}
	//	return listOfIsomorphisms;
	//}
	//return listOfIsomorphisms;
}


vector<vector<int>> ParaMODAImpl::IsomorphicExtensionForEquivalenceClass(tsl::hopscotch_map<int, int>& partialMap, Graph & queryGraph, Graph & inputGraph, vector<int> & MappedHNodes)
//tsl::hopscotch_set<vector<int>, Vector_Int_Hash, Vector_Int_Comparator> ParaMODAImpl::IsomorphicExtension(tsl::hopscotch_map<int, int>& partialMap, Graph & queryGraph, Graph & inputGraph)
{
	//tsl::hopscotch_set<vector<int>, Vector_Int_Hash, Vector_Int_Comparator> listOfIsomorphisms;
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
		//return vector<vector<int>>(1, partialMapValuesG);

		//for (int i = 0; i < mapKeyOriginal.size(); i++)
		//{
		//	cout << mapKeyOriginal[i] << "->" << mapValueOriginal[i] << "  --  ";
		//}
		//cout << endl;

		MappedHNodes = mapKeyOriginal;
		return vector<vector<int>>(1, mapValueOriginal);

		//return tsl::hopscotch_set<vector<int>, Vector_Int_Hash, Vector_Int_Comparator>({ partialMapValuesG });
	}


	int m = GetMostConstrainedNeighbour(partialMapKeysH, queryGraph);
	if (m < 0)
		return listOfIsomorphisms;

	vector<int> neighbourRange;
	ChooseNeighboursOfRange(partialMapValuesG, inputGraph, neighbourRange);
	//findMCount -= neighbourRange.size();

	//partialMapValuesG.clear();
	//partialMapValuesG.shrink_to_fit();
	//partialMapKeysH.clear();
	//partialMapKeysH.shrink_to_fit();

	vector<int> neighborsOfM(queryGraph.GetNeighbors(m));
	//cout << "neighborRange Size: "<<neighbourRange.size() << endl;
	for (auto const & n : neighbourRange)
	{
		if (!IsNeighbourIncompatible(inputGraph, n, partialMap, neighborsOfM))
		{
			tsl::hopscotch_map<int, int> newPartialMap(partialMap);
			newPartialMap[m] = n;

			//cout << m << " - " << n <<endl;

			//findMCount -= 1;
			vector<vector<int>> subList(IsomorphicExtensionForEquivalenceClass(newPartialMap, queryGraph, inputGraph, MappedHNodes));
			listOfIsomorphisms.reserve(listOfIsomorphisms.size() + subList.size());
			listOfIsomorphisms.insert(listOfIsomorphisms.end(), subList.begin(), subList.end());
			//tsl::hopscotch_set<vector<int>, Vector_Int_Hash, Vector_Int_Comparator> subList(IsomorphicExtension(newPartialMap, queryGraph, inputGraph));
			//listOfIsomorphisms.reserve(listOfIsomorphisms.size() + subList.size());
			//listOfIsomorphisms.insert(subList.begin(), subList.end());
		}
		//findMCount += 1;
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
		//if (find(obj2.begin(), obj2.end(), itr1) == obj2.end())
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
	//int i = 0;
	vector<int>::const_iterator obj2Begin(obj2.begin());
	vector<int>::const_iterator obj2End(obj2.end());
	for (auto const& itr1 : obj1)
	{
		if (!binary_search(obj2Begin, obj2End, itr1.first))
			return false;
	}
	return true;
}


//long ParaMODAImpl::FindBestH(Graph & queryGraph)
//{
//	//Just choose the first element of queryGraph
//	//int h = queryGraph.GetVertexList().begin()->first;
//	//int h = 5;
//	//int h = queryGraph.GetNodesSortedByDegree(0).back();
//	//vector<int> hList = queryGraph.GetNodesSortedByDegree(0);
//	//cout << queryGraph.getNumberOfVertices() << endl;
//	//cout << "h = " << h << endl;
//	//for (auto const & itrH : hList)
//	//{
//	//	cout << itrH << endl;
//	//}
//
//	vector<int> queryGraphDegSeq(queryGraph.GetNodesSortedByDegree(0));
//	//cout << "sice sequence: " << inputGraphDegSeq.size() << endl;;
//	cout << "Calling ParaMODA Algorithm (i.e. Algo 2-Modified):" << endl;
//	for (auto const & h : queryGraphDegSeq)
//	{
//		vector<vector<int>> theMappings;
//		tsl::hopscotch_map<int, int> f;
//		for (int i = 0; i < queryGraphDegSeq.size(); i++)
//		{
//			int g = queryGraphDegSeq[i];
//			//cout << "Processing: " << i << "  ---Node: " << g << "  ---Neighbor Count: " << inputGraph.GetNeighbors(g).size() << endl;
//			//if (CanSupport(queryGraph, h, inputGraph, g))
//			//{
//			//cout << "CAN SUPPORT" << endl;
//			f[h] = g;
//			vector<vector<int>> mappings = IsomorphicExtension(f, queryGraph, queryGraph);
//			//cout << "ISOMORPHIC EXTENDED" << endl;
//
//			theMappings.insert(theMappings.begin(), mappings.begin(), mappings.end());
//			//cout <<"theMappings Size: "<< theMappings.size() << endl;
//			/*}*/
//		}
//
//		cout << "h = " << h << "  ---  " << endl;
//		findMCount = 0;
//	}
//	//cout << "\nAll iteration tasks completed. Number of mappings found:" << theMappings.size() << endl;
//
//	return 0;
//}


long ParaMODAImpl::Algorithm2_Modified(Graph & queryGraph, Graph & inputGraph, const int & h)
{
	//Just choose the first element of queryGraph
	//int h = queryGraph.GetVertexList().begin()->first;
	//int h = 4;
	//int h = queryGraph.GetNodesSortedByDegree(0).back();
	//vector<int> hList = queryGraph.GetNodesSortedByDegree(0);
	//cout << queryGraph.getNumberOfVertices() << endl;
	
	
	//cout << "h = " << h << endl;


	//for (auto const & itrH : hList)
	//{
	//	cout << itrH << endl;
	//}

	//high_resolution_clock::time_point t1 = high_resolution_clock::now();
	//cout << "start condition" << endl;
	//tsl::hopscotch_set<tsl::hopscotch_set<int>, Set_Int_Hash> EquivClass = Algorithm2_Modified_For_Equivalence_Class(queryGraph, queryGraph);
	//tsl::hopscotch_map<int, int> condition = FindCondition(EquivClass);
	tsl::hopscotch_map<int, vector<int>> condition(Algorithm2_Modified_For_Equivalence_Class(queryGraph, queryGraph, h));
	//condition.clear();

	//condition.erase(-4);
	//condition.erase(2);
	//condition.insert({ 3,2 });
	//condition.insert({ 2,1 });

	//condition.insert({ 1,3 });
	//condition.insert({ -3,1 });
	//condition.insert({ 4,2 });
	//condition.insert({ -2,4 });

	//condition.insert({ 1,2 });
	//condition.insert({ -2,1 });
	////condition.insert({ 2,3 });
	////condition.insert({ -3,2 });
	//condition.insert({ 4,2 });
	////condition.insert({ -2,4 });
	//condition.insert({ 3,4 });
	//condition.insert({ -4,3 });

	//for (auto & i : condition)
	//{
	//	cout << "condition: " << i.first << "=>";
	//	for (auto const & itr : i.second)
	//	{
	//		cout << itr << ", ";
	//	}
	//	cout << endl;
	//}

	//cout << "end condition" << endl;

	//high_resolution_clock::time_point t2 = high_resolution_clock::now();

	//auto duration = duration_cast<microseconds>(t2 - t1).count();

	//string time = "\nTime Taken: " + to_string(float(duration) / float(1000000)) + " seconds (" + to_string(duration / 1000) + "ms)\n";

	//cout << time;

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
	//cout << "totalCondition: " << totalCondition << endl;



	vector<int> inputGraphDegSeq(inputGraph.GetNodesSortedByDegree(queryGraph.GetOutDegree(h)));

	cout << "h Neighbor size: " << queryGraph.GetNeighbors(h).size() << endl;
	//cout << "g Neighbor size: " << inputGraph.GetNeighbors(inputGraphDegSeq[0]).size() << endl;
	//cout << "inputGraphDegSeq " << inputGraphDegSeq.size() << endl;

	//cout << "size sequence: " << inputGraphDegSeq.size() << endl;;
	
	//cout << "Calling ParaMODA Algorithm (i.e. Algo 2-Modified):" << endl;

	//tsl::hopscotch_set<vector<int>, Vector_Int_Hash, Vector_Int_Comparator> theMappings;
	//vector<vector<int>> theMappings;

	tsl::hopscotch_map<int, int> f;
	//int g = 0;
	unsigned long mappingCount(0);

	int inputGraphDegSeqSize(inputGraphDegSeq.size());

	for (int i = 0; i < inputGraphDegSeqSize; i++)
	{
		//g = inputGraphDegSeq[i];
		//cout << "Processing: " << i << "  ---Node: " << g /*<< "  ---Neighbor Count: " << inputGraph.GetNeighbors(g).size()*/ << endl;
		//if (CanSupport(queryGraph, h, inputGraph, g))
		//{
			//cout << "CAN SUPPORT" << endl;
		//f[h] = g;
		f[h] = inputGraphDegSeq[i];
		//long mappings(IsomorphicExtension(f, queryGraph, inputGraph, condition));

		//tsl::hopscotch_set<vector<int>, Vector_Int_Hash, Vector_Int_Comparator> mappings(IsomorphicExtension(f, queryGraph, inputGraph));

		//cout << "ISOMORPHIC EXTENDED" << endl;

		//theMappings.insert(mappings.begin(), mappings.end());
		//theMappings.insert(theMappings.end(), mappings.begin(), mappings.end());

		//mappingCount += mappings;
		mappingCount += IsomorphicExtension(f, queryGraph, inputGraph, condition);

		//mappingCount += theMappings.size();
		//mappingCount += mappings.size();
		//theMappings = tsl::hopscotch_set<vector<int>, Vector_Int_Hash, Vector_Int_Comparator>();
		//cout <<"theMappings Size: "<< theMappings.size() << endl;
		//cout << "theMappings Size: " << mappingCount << endl;
	}

	//cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	//for (auto & map : theMappings)
	//{
	//	for (auto & point : map)
	//	{
	//		cout << point << " - ";
	//	}
	//	cout << endl;
	//}

	//cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;



	//cout << "\nAll iteration tasks completed. Number of mappings found:" << theMappings.size() << endl;
	//cout << "\nAll iteration tasks completed. Number of mappings found:" << mappingCount << endl;

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

	//return theMappings.size();
	return mappingCount;
}


//tsl::hopscotch_set<tsl::hopscotch_set<int>, Set_Int_Hash> ParaMODAImpl::Algorithm2_Modified_For_Equivalence_Class(Graph & queryGraph, Graph & inputGraph)
tsl::hopscotch_map<int, vector<int>> ParaMODAImpl::Algorithm2_Modified_For_Equivalence_Class(Graph & queryGraph, Graph & inputGraph, const int & fixedNode)
{
	//Just choose the first element of queryGraph
	int h(queryGraph.GetVertexList().begin()->first);
	//int h = 22;
	//int h = queryGraph.GetNodesSortedByDegree(0).back();
	//vector<int> hList = queryGraph.GetNodesSortedByDegree(0);
	//cout << queryGraph.getNumberOfVertices() << endl;
	//cout << "h = " << h << endl;
	//for (auto const & itrH : hList)
	//{
	//	cout << itrH << endl;
	//}

	vector<int> inputGraphDegSeq(inputGraph.GetNodesSortedByDegree(queryGraph.GetOutDegree(h)));
	//cout << "size sequence: " << inputGraphDegSeq.size() << endl;;
	//cout << "Calling ParaMODA Algorithm (i.e. Algo 2-Modified):" << endl;

	//tsl::hopscotch_set<vector<int>, Vector_Int_Hash, Vector_Int_Comparator> theMappings;
	vector<vector<int>> theMappings;

	tsl::hopscotch_map<int, int> f;

	//unsigned long mappingCount = 0;
	//int g = 0;
	vector<int> mappedHNodes;

	int inputGraphDegSeqSize(inputGraphDegSeq.size());
	for (int i = 0; i < inputGraphDegSeqSize; i++)
	{
		//g = inputGraphDegSeq[i];
		//cout << "Processing: " << i << "  ---Node: " << g /*<< "  ---Neighbor Count: " << inputGraph.GetNeighbors(g).size()*/ << endl;
		//if (CanSupport(queryGraph, h, inputGraph, g))
		//{
		//cout << "CAN SUPPORT" << endl;
		//f[h] = g;
		f[h] = inputGraphDegSeq[i];
		vector<vector<int>> mappings(IsomorphicExtensionForEquivalenceClass(f, queryGraph, inputGraph, mappedHNodes));
		//tsl::hopscotch_set<vector<int>, Vector_Int_Hash, Vector_Int_Comparator> mappings(IsomorphicExtension(f, queryGraph, inputGraph));

		//cout << "ISOMORPHIC EXTENDED" << endl;

		//theMappings.insert(mappings.begin(), mappings.end());
		theMappings.insert(theMappings.end(), mappings.begin(), mappings.end());

		//mappingCount += theMappings.size();
		//mappingCount += mappings.size();
		//theMappings = tsl::hopscotch_set<vector<int>, Vector_Int_Hash, Vector_Int_Comparator>();
		//cout <<"theMappings Size: "<< theMappings.size() << endl;
		//cout << "theMappings Size: " << mappingCount << endl;
	}

	//cout << "START FINDING COND" << endl;

	//for (auto const & i : mappedHNodes)
	//{
	//	cout << i << " -- ";
	//}

	//vector<tsl::hopscotch_set<int>> equivalenceFilter(queryGraph.getNumberOfVertices(), tsl::hopscotch_set<int>());

	//for (auto const & map : theMappings)
	//{
	//	for (int i = 0; i < map.size(); i++)
	//	{
	//		equivalenceFilter[i].insert(map[i]);
	//	}
	//}

	//tsl::hopscotch_set<tsl::hopscotch_set<int>, Set_Int_Hash> equivalenceClass;

	//for (auto const & entry : equivalenceFilter)
	//{
	//	equivalenceClass.insert(entry);
	//}


	//for (auto const & equiv : equivalenceClass)
	//{
	//	for (auto const & itr : equiv)
	//	{
	//		cout << itr << " - ";
	//	}
	//	cout << endl;
	//}

	//vector<vector<int>> newMappings;

	//for (auto & map : theMappings)
	//{
	//	for (int i = 0; i < map.size(); i++)
	//	{
	//		if (map[i] == fixedNode && map[i] == mappedHNodes[i])
	//		{
	//			newMappings.push_back(map);
	//		}
	//	}
	//}

	tsl::hopscotch_map<int, vector<int>> condition;
	//cout << endl << "SiZE: " << condition.size() << endl;
	tsl::hopscotch_set<tsl::hopscotch_set<int>, Set_Int_Hash> equivalenceClass;

	//return FindCondition(mappedHNodes, newMappings, condition, equivalenceClass);
	return FindCondition(mappedHNodes, theMappings, condition, equivalenceClass);

	//string result = "\nSub-graph: Graph Edges:\t";
	//vector<pair<int, int>> qGraphs = queryGraph.GetEdgeList();
	//int count = 0;
	//int numgraphs = qGraphs.size();
	////list all edges from query graph 
	//for (auto q : qGraphs)
	//{
	//	count++;
	//	result += "[" + to_string(q.first) + "->" + to_string(q.second) + "]";
	//	if (count != numgraphs)
	//		result += ",";
	//}
	//result += "\tMappings: " + to_string(theMappings.size()) + "\n";

	//cout << result;


	//return theMappings.size();

	//return equivalenceClass;
}


//tsl::hopscotch_map<int, int> ParaMODAImpl::FindCondition(tsl::hopscotch_set<tsl::hopscotch_set<int>, Set_Int_Hash>& equivalenceClass)
//{
//	//for (auto const & entry : equivalenceClass)
//	//{
//	//	if (entry.find(h) != entry.end())
//	//	{
//	//		tsl::hopscotch_set<int> condition(entry);
//	//		condition.erase(h);
//	//		return condition;
//	//	}
//	//}
//	////throw exception if not found ??
//	//throw "Node NOT FOUND in QueryGraph!!!";
//
//
//	tsl::hopscotch_map<int, int> condition;
//	//for (auto const & subclass : equivalenceClass)
//	//{
//	//	if (subclass.size() > 1)
//	//	{
//	//		for (auto itr = subclass.begin(); itr != subclass.end(); itr++)
//	//		{
//	//			if (next(itr) != subclass.end())
//	//				//condition.insert({ *itr, *next(itr) });
//	//				condition.insert({ *next(itr), *itr });
//	//			//else
//	//			//	//condition.insert({ *itr, *subclass.begin()});
//	//			//	condition.insert({ *subclass.begin(), *itr });
//	//		}
//	//	}
//	//}
//
//	vector<vector<int>> sortedClass;
//	for (auto const & subclass : equivalenceClass)
//	{
//		if (subclass.size() > 1)
//			sortedClass.push_back(vector<int>(subclass.begin(), subclass.end()));
//	}
//
//	for (auto & subSortedClass : sortedClass)
//	{
//		sort(subSortedClass.begin(), subSortedClass.end());
//		for (int i = 0; i < subSortedClass.size()-1; i++)
//		{
//			condition.insert({ subSortedClass[i], subSortedClass[i+1] });
//		}
//	}
//
//	condition.erase(2);
//
//	for (auto const & i : condition)
//	{
//		cout << i.first << " < " << i.second << endl;
//	}
//
//	return condition;
//}


tsl::hopscotch_map<int, vector<int>> ParaMODAImpl::FindCondition(vector<int> &mappedHNodes, vector<vector<int>> &theMappings,
	tsl::hopscotch_map<int, vector<int>> &condition, tsl::hopscotch_set<tsl::hopscotch_set<int>, Set_Int_Hash> &equivalenceClass)
{
	if (theMappings.size() == 1)
	{
		//cout << "FOUND" << endl;
		return condition;
	}

	//cout << endl << "mappedHNode size = " << mappedHNodes.size() << endl;
	vector<tsl::hopscotch_set<int>> equivalenceFilter(mappedHNodes.size(), tsl::hopscotch_set<int>());

	for (auto const & map : theMappings)
	{
		for (int i = 0; i < map.size(); i++)
		{
			equivalenceFilter[i].insert(map[i]);
		}
	}

	//tsl::hopscotch_set<tsl::hopscotch_set<int>, Set_Int_Hash> equivalenceClass;

	int maxSize = equivalenceFilter.begin()->size();
	tsl::hopscotch_set<int> temp;

	if (equivalenceClass.empty())				//MIGHT NEED CHECK----------
		temp = *equivalenceFilter.begin();
	else
		temp = *equivalenceClass.begin();		//---------------------------

	//cout << "maxSize = " << maxSize << endl;


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

	//for (auto & i : equivalenceClass)
	//{
	//	for (auto & j : i)
	//	{
	//		cout << j << " --";
	//	}
	//	cout << endl;
	//}

	equivalenceClass.erase(temp);

	vector<int> sortedTemp(temp.begin(), temp.end());
	sort(sortedTemp.begin(), sortedTemp.end());

	//cout << "temp = ";
	//for (auto & i : temp)
	//{
	//	cout << i << " -- ";
	//}
	//cout << endl;

	/*int fixedNode = *temp.begin();
	int comparedNode = *next(temp.begin());*/

	//int fixedNode, comparedNode;
	//vector<int> sortedTemp;

	int fixedNode = sortedTemp[0];
	//int comparedNode = sortedTemp[1];

	/*cout << "FIRST TEST" << endl;

	if (condition.size() == 0)
	{
		cout << "FIRST" << endl;
		fixedNode = mappedHNodes[0];
		for (auto & subclass : equivalenceClass)
		{
			if (subclass.find(fixedNode) != subclass.end())
			{
				temp = subclass;
				equivalenceClass.erase(subclass);
				break;
			}
		}
		temp.erase(fixedNode);
		sortedTemp = vector<int>(temp.begin(), temp.end());
		sort(sortedTemp.begin(), sortedTemp.end());
		comparedNode = sortedTemp[0];
	}
	else
	{
		fixedNode = sortedTemp[0];
		comparedNode = sortedTemp[1];

		equivalenceClass.erase(temp);
	}*/

	//fixedNode = sortedTemp[0];
	//comparedNode = sortedTemp[1];
	//
	//equivalenceClass.erase(temp);


	//equivalenceClass.erase(temp);
	//temp.erase(fixedNode);
	//equivalenceClass.insert(temp);

	//cout << "fixed = " << fixedNode << " comp = " << comparedNode << endl;
	/*cout << "fixed = " << fixedNode << "  ****  sortedTemp = ";

	for (auto const& i : sortedTemp)
	{
		cout << i << " - ";
	}
	cout << endl;*/

	condition.insert({ fixedNode, sortedTemp });
	//condition.insert({ -comparedNode, fixedNode });

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

	//for (auto & i : newMappings)
	//{
	//	for (int j = 0; j < i.size(); j++)
	//	{
	//		cout << mappedHNodes[j] << "->" << i[j] << " -- ";
	//	}
	//	cout << endl;
	//}
	
	FindCondition(mappedHNodes, newMappings, condition, equivalenceClass);

	return condition;

	//for (auto const & equiv : equivalenceClass)
	//{
	//	for (auto const & itr : equiv)
	//	{
	//		cout << itr << " - ";
	//	}
	//	cout << endl;
	//}
}

bool ParaMODAImpl::CheckSymmetryBreak(const int & fixed, const vector<int> & nodesToCheck, tsl::hopscotch_map<int, int> & partialMap, int & m, int & n)
{
	//cout << "check break" << endl;

	if (!binary_search(nodesToCheck.begin(), nodesToCheck.end(), m)
		|| ((m != fixed) && partialMap.find(fixed) == partialMap.end()))
	{
		return true;
	}

	int fixedLabel = (m == fixed) ? n : partialMap[fixed];

	//cout << "fixed = " << fixed << " fixedLabel = " << fixedLabel << " n = " << n << endl;

	if (m == fixed)
	{
		for (auto const & node : nodesToCheck)
		{
/*			try
			{
				if (partialMap.at(node) < fixedLabel)
					return false;
			}
			catch (out_of_range)
			{
			}*/

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


	//try 
	//{
	//	vector<int> nodesToCheck(symBreakCondition.at(m));
	//	for (auto const & node : nodesToCheck)
	//	{
	//		try
	//		{
	//			if (partialMap.at(node) < n)
	//				return false;
	//		}
	//		catch (out_of_range)
	//		{
	//		}	//		
	//	}
	//	return true;
	//}
	//catch (out_of_range)
	//{
	//	for (auto const & map : partialMap)
	//	{
	//		if (n >= map.second)
	//			return true;
	//	}
	//	return false;
	//}
}


//long ParaMODAImpl::Algorithm_GK(Graph & queryGraph, Graph & inputGraph)
//{
//	vector<int> inputGraphDegSeq(inputGraph.GetNodesSortedByDegree(0));
//	vector<int> queryGraphDegSeq(queryGraph.GetNodesSortedByDegree(0));
//
//	//cout << "sice sequence: " << inputGraphDegSeq.size() << endl;;
//	cout << "Calling GK Algorithm:" << endl;
//
//	tsl::hopscotch_set<vector<int>, Vector_Int_Hash, Vector_Int_Comparator> theMappings;
//	tsl::hopscotch_map<int, int> f;
//	for (int i = 0; i < inputGraphDegSeq.size(); i++)
//	{
//		int g = inputGraphDegSeq[i];
//		for (auto & h : queryGraphDegSeq)
//		{			
//			cout << "Processing: " << i << "  ---Node: " << g << "  ---Neighbor Count: " << inputGraph.GetNeighbors(g).size() << endl;
//			if (CanSupport(queryGraph, h, inputGraph, g))
//			{
//			//cout << "CAN SUPPORT" << endl;
//			f[h] = g;
//			vector<vector<int>> mappings = IsomorphicExtension(f, queryGraph, inputGraph);
//			//cout << "ISOMORPHIC EXTENDED" << endl;
//
//			theMappings.insert(mappings.begin(), mappings.end());
//			//cout <<"theMappings Size: "<< theMappings.size() << endl;
//			}
//		}
//		queryGraph.GetVertexList().erase(g);
//	}
//	cout << "\nAll iteration tasks completed. Number of mappings found:" << theMappings.size() << endl;
//
//	return theMappings.size();
//}
