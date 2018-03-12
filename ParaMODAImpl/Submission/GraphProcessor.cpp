#include "GraphProcessor.h"



ParaMODAImpl::GraphProcessor::GraphProcessor()
{
}

ParaMODAImpl::GraphProcessor::~GraphProcessor()
{
}


//Method to read graph input from file and construct inputGraph
UndirectedGraph ParaMODAImpl::GraphProcessor::LoadGraph(string filename)
{
   string line;
   ifstream inFile(filename);
   UndirectedGraph newGraphInstance = UndirectedGraph();
   list<pair<int, int>> edgeList;

   if (inFile.is_open())
   {
	  while (getline(inFile, line))
	  {
		 if (size_t index = line.find_first_not_of(" ") != string::npos)
		 {
			if (line[index] != '#')
			{
			   int source, target;

			   istringstream iss(line);
				  iss >> source >> target;
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


//Overload method to read graph input from file and construct queryGraph
ParaMODAImpl::QueryGraph ParaMODAImpl::GraphProcessor::LoadGraph(string filename, bool isQueryGraph)
{
   string line;
   ifstream inFile(filename);
   QueryGraph newGraphInstance = QueryGraph();
   list<pair<int, int>> edgeList;

   if (inFile.is_open())
   {
	  while (getline(inFile, line))
	  {
		 if (size_t index = line.find_first_not_of(" ") != string::npos)
		 {
			if (line[index] != '#')
			{
			   int source, target;

			   istringstream iss(line);
			   iss >> source >> target;
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
