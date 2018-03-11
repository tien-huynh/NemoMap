#include "GraphProcessor.h"



ParaMODAImpl::GraphProcessor::GraphProcessor()
{
}

ParaMODAImpl::GraphProcessor::~GraphProcessor()
{
}

UndirectedGraph ParaMODAImpl::GraphProcessor::LoadGraph(string filename)
{
   string line;
   ifstream inFile(filename);
   UndirectedGraph newGraphInstance = UndirectedGraph();
   list<pair<int, int>> edgeList;

   //if (isQueryGraph) //NEED WORK
   //{
	  //newGraphInstance = QueryGraph(filename);
   //}
   //else
   //{
	  //newGraphInstance = UndirectedGraph();
   //}

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
				  //cout << source << "  --  " << target << endl;
				  edgeList.push_back(make_pair(source, target));
			   //newGraphInstance->AddVerticesAndEdge(source, target);
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

ParaMODAImpl::QueryGraph ParaMODAImpl::GraphProcessor::LoadGraph(string filename, bool isQueryGraph)
{
   string line;
   ifstream inFile(filename);
   QueryGraph newGraphInstance = QueryGraph();
   list<pair<int, int>> edgeList;

   //if (isQueryGraph) //NEED WORK
   //{
   //newGraphInstance = QueryGraph(filename);
   //}
   //else
   //{
   //newGraphInstance = UndirectedGraph();
   //}

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
			   //cout << source << "  --  " << target << endl;
			   edgeList.push_back(make_pair(source, target));
			   //newGraphInstance->AddVerticesAndEdge(source, target);
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
