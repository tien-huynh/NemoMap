#include "GraphProcessor.h"



GraphProcessor::GraphProcessor()
{
}

GraphProcessor::~GraphProcessor()
{
}

UndirectedGraph<int>* GraphProcessor::LoadGraph(string filename, bool isQueryGraph)
{
	string line;
	ifstream inFile;
	inFile.open(filename);
	UndirectedGraph<int>* newGraphInstance;

	if (isQueryGraph) //NEED WORK
	{

	}
	else
	{
		newGraphInstance = new UndirectedGraph<int>();
	}
	newGraphInstance = new UndirectedGraph<int>();
	if (inFile)
	{
		cout << "Undirected Graph:" << endl;
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
