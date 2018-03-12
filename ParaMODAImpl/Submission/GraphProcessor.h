#pragma once
#include "UndirectedGraph.h"
#include "QueryGraph.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

namespace ParaMODAImpl
{
   class GraphProcessor
   {
   public:
	  GraphProcessor();
	  ~GraphProcessor();

	  //Method to read graph input from file and construct inputGraph
	  UndirectedGraph LoadGraph(string filename);

	  //Overload method to read graph input from file and construct queryGraph
	  QueryGraph LoadGraph(string filename, bool isQueryGraph);
   };

}