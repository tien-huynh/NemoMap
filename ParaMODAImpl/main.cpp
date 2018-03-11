#include "GraphProcessor.h"
#include "ParaMODAAlgorithm.h"
#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace ParaMODAImpl;
using namespace std::chrono;
int main(int argc, char *argv[])
{
	if (argc == 5)
	{
		//format -g [input graph] -h [query graph]
		if (string(argv[1]) == "-g" && string(argv[3]) == "-h")	
		{
			string inputfile = string(argv[2]);
			string queryfile = string(argv[4]);

			//reads input file
			UndirectedGraph inputGraph = GraphProcessor().LoadGraph(inputfile);			
			cout << "Input Graph (G): Nodes - " << boost::num_vertices(inputGraph.graph) << "; Edges: " << boost::num_edges(inputGraph.graph) << endl;

			//reads query file 
			QueryGraph queryGraph = GraphProcessor().LoadGraph(queryfile, true);
			cout << "\nQuery Graph (H): Nodes - " << boost::num_vertices(queryGraph.graph) << "0; Edges: " << boost::num_edges(queryGraph.graph) << "\n" << endl;
			
			high_resolution_clock::time_point t1 = high_resolution_clock::now();	//times execution counts in microseconds 
			
			//calls Algorithm2_Modified to get the frequent subgraphs 
			list<Mapping> frequentSubgraphs = ParaMODAAlgorithm().Algorithm2_Modified(queryGraph, inputGraph, -1, true);
			
			high_resolution_clock::time_point t2 = high_resolution_clock::now();

			auto duration = duration_cast<microseconds>(t2 - t1).count();
			
			string result = "\nProcessing Graph...\nCompleted. Result Summary\n-----------------------------------------------------"; 

			result += "\nSub-graph: Graph Edges:\t";
			std::list < std::pair<int, int>> qGraphs = queryGraph.GetEdgeList();
			int count = 0;
			int numgraphs = qGraphs.size();
			//list all edges from query graph 
			for (auto q : qGraphs)
			{
				count++;
				result += "[" + to_string(q.first) + "->" + to_string(q.second) + "]";
				if (count != numgraphs)
					result += ",";
			}
			result += "\tMappings: " + to_string(frequentSubgraphs.size()) + "\t Is Frequent Subgraph? False\n";
			
			result  += "\nTime Taken: " + to_string(float(duration)/ float(1000000)) +" secoonds (" + to_string(duration/1000) + "ms)";
			
			result += "\nNetwork: Nodes - " + to_string(boost::num_vertices(inputGraph.graph)) + "; Edges: " + to_string(boost::num_edges(inputGraph.graph));
			
			result += "\nTotal Mappings found: " + to_string(frequentSubgraphs.size());
			
			result += "\nSubgraph Size: -1";
			
			result += "\n------------------------------------------------------ ";
			
			cout << result  << endl;
			
			//write results to file 
			ofstream output(inputfile + ".out");
			output << result;
			output.close();
			exit(0);
		}
		else
		{
			cout << "ERROR: Wrong number of arguments." << endl;
			cout << "Input format: -g [input graph] -h [query graph]" << endl;
			exit(0);
		}
	}
	else
	{
		cout << "ERROR: Wrong number of arguments." << endl;
		cout << "Input format: -g [input graph] -h [query graph]" << endl;
		exit(0);
	}
}