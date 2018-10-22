#include "GraphProcessor.h"
#include "Utility.h"
#include "NodeExpansion.h"
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
		high_resolution_clock::time_point t1, t2;
		long long duration = 0;
		int totalMappings = 0;

		string inputfile = string(argv[2]);
		Graph inputGraph = GraphProcessor().LoadGraph(inputfile);

		cout << "\nInput Graph (G): Nodes - " << inputGraph.getNumberOfVertices() << "; Edges - " << inputGraph.getNumberOfEdges() << endl;


		if (string(argv[3]) == "-h")
		{
			string queryfile = string(argv[4]);
			Graph queryGraph = GraphProcessor().LoadGraph(queryfile);

			cout << "\nQuery Graph (H): Nodes - " << queryGraph.getNumberOfVertices() << "; Edges - " << queryGraph.getNumberOfEdges() << "\n" << endl;

			string result = "\nSub-graph: Graph Edges:\t";

			vector<pair<int, int>> qGraphs = queryGraph.GetEdgeList();
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
			result += "\n\n";
			cout << result;


			int h = queryGraph.GetNodesSortedByDegree(0).back();
			string tempPrint;
			result += "H node =  [" + to_string(h) + "]  ---------------------------------------------";
			tempPrint += "H node =  [" + to_string(h) + "]  ---------------------------------------------";
			t1 = high_resolution_clock::now();	//times execution counts in microseconds
			totalMappings = Algorithm2_Modified(queryGraph, inputGraph, h);

			t2 = high_resolution_clock::now();

			auto tempDuration = duration_cast<microseconds>(t2 - t1).count();

			duration += tempDuration;

			result += "\nTime Taken: " + to_string(float(tempDuration) / float(1000000)) + " seconds (" + to_string(tempDuration / 1000) + "ms)\n\n";
			tempPrint += "\nTime Taken: " + to_string(float(tempDuration) / float(1000000)) + " seconds (" + to_string(tempDuration / 1000) + "ms)\n\n";
			cout << tempPrint;

			cout << "Mapping: " + to_string(totalMappings) + "\n";

			result += "Mapping: " + to_string(totalMappings) + "\n";

			//write results to file 
			ofstream output(queryfile + "resultHnode.out");
			output << result;
			output.close();
		}
		else if (string(argv[3]) == "-n")
		{
			NodeExpansion node;
			string expansionSize = string(argv[4]);

			t1 = high_resolution_clock::now();	//times execution counts in microseconds

			if (expansionSize == "3")
				node.threeExpand();
			else if (expansionSize == "4")
				node.fourExpand();
			else if (expansionSize == "5")
				node.fiveExpand();
			else
			{
				cout << "ERROR: Expansion size must be between 3 to 5" << endl;
				exit(0);
			}

			int i = 1;
			for (auto & queryGraph : node.getListOfGraphs())
			{
				int h = queryGraph.GetVertexList().begin()->first;
				totalMappings += Algorithm2_Modified(queryGraph, inputGraph, h);

				string outFileName = "QueryGraphGK";
				outFileName += to_string(i) + ".out";
				ofstream outputFormatted(outFileName);
				string format = "*vertices " + to_string(queryGraph.getNumberOfVertices()) + "\n";

				for (auto const& vertex : queryGraph.GetVertexList())
				{
					format += to_string(vertex.first) + "\n";
				}

				format += "*edges\n";
				for (auto const& edge : queryGraph.GetEdgeList())
				{
					format += to_string(edge.first) + " " + to_string(edge.second) + "\n";
				}
				outputFormatted << format;
				outputFormatted.close();
				i++;
			}
			t2 = high_resolution_clock::now();

			duration = duration_cast<microseconds>(t2 - t1).count();
		}
		else
		{
			cout << "ERROR: Wrong number of arguments. 1" << endl;
			cout << "Input format: -g [input graph] -h [query graph]" << endl;
			exit(0);
		}

		string result = "\nProcessing Graph...\nCompleted. Result Summary\n-----------------------------------------------------";

		result += "\nTime Taken: " + to_string(float(duration) / float(1000000)) + " seconds (" + to_string(duration / 1000) + "ms)";

		result += "\nNetwork: Nodes - " + to_string(inputGraph.getNumberOfVertices()) + "; Edges - " + to_string(inputGraph.getNumberOfEdges());

		result += "\nTotal Mappings found: " + to_string(totalMappings);

		result += "\n------------------------------------------------------ ";

		cout << result << endl;

		//write results to file 
		ofstream output(inputfile + ".out");
		output << result;
		output.close();

		ofstream outputFormatted("QueryGraphGK.out");
		string format = "*vertices " + to_string(inputGraph.getNumberOfVertices()) + "\n";

		for (auto const& vertex : inputGraph.GetVertexList())
		{
			format += to_string(vertex.first) + "\n";
		}

		format += "*edges\n";
		for (auto const& edge : inputGraph.GetEdgeList())
		{
			format += to_string(edge.first) + " " + to_string(edge.second) + "\n";
		}
		outputFormatted << format;
		outputFormatted.close();

		exit(0);
	}
	else
	{
		cout << "ERROR: Wrong number of arguments. 2" << endl;
		cout << "Input format: -g [input graph] -h [query graph]" << endl;
		exit(0);
	}
}


