#include "GraphProcessor.h"



ParaMODAImpl::GraphProcessor::GraphProcessor()
{
}

ParaMODAImpl::GraphProcessor::~GraphProcessor()
{
}

QuickGraph::UndirectedGraph<int>^ ParaMODAImpl::GraphProcessor::LoadGraph(string filename, bool isQueryGraph)
{
   string line;
   ifstream inFile(filename);
   QuickGraph::UndirectedGraph<int>^ newGraphInstance;

   if (isQueryGraph) //NEED WORK
   {

   }
   else
   {
	  newGraphInstance = gcnew QuickGraph::UndirectedGraph<int>();
   }

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
				  cout << source << "  --  " << target << endl;
			   newGraphInstance->AddVerticesAndEdge(source, target);
			}
		 }
	  }
	  inFile.close();
   }
   else
	  cerr << "ERROR: Unable to open file" << endl;	  //NEED FURTHER CHECK
   return newGraphInstance;
}
