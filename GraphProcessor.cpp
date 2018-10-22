/*	Filename:		GraphProcessor.cpp
	Description:	Implementation of a class to read in graph data from a text file an construct the graph
	Author:			Tien Huynh
*/
#include "GraphProcessor.h"


ParaMODAImpl::GraphProcessor::GraphProcessor()
{
}


ParaMODAImpl::GraphProcessor::~GraphProcessor()
{
}


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
			if (line[index] != '#')	//# character marks comment line
			{
			   int source, target;

			   istringstream iss(line);
				  iss >> source >> target;
				  if (source != target)	//Don't allow self-edge
					edgeList.push_back(make_pair(source, target));
			}
		 }
	  }
	  newGraphInstance.AddVerticesAndEdgeRange(edgeList);
	  inFile.close();
   }
   else
	  cerr << "ERROR: Unable to open file" << endl;
   return newGraphInstance;
}

