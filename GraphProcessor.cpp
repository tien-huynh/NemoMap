#include "GraphProcessor.h"



ParaMODAImpl::GraphProcessor::GraphProcessor()
{
}

ParaMODAImpl::GraphProcessor::~GraphProcessor()
{
}


//Method to read graph input from file and construct inputGraph
Graph ParaMODAImpl::GraphProcessor::LoadGraph(string filename)
{
   string line;
   ifstream inFile(filename);
   Graph newGraphInstance = Graph();
   vector<pair<int, int>> edgeList;

   if (inFile.is_open())
   {
	  while (getline(inFile, line))
	  {
		 if (int index = line.find_first_not_of(" ") != string::npos)
		 {
			if (line[index] != '#')
			{
			   int source, target;

			   istringstream iss(line);
				  iss >> source >> target;
				  if (source != target)
					edgeList.push_back(make_pair(source, target));
			}
		 }
	  }
	  newGraphInstance.AddVerticesAndEdgeRange(edgeList);
	  inFile.close();
   }
   else
	  cerr << "ERROR: Unable to open file" << endl;	  //NEED FURTHER CHECK
   return newGraphInstance;
}

