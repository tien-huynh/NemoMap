#pragma once
#include "Graph.h"
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
	  Graph LoadGraph(string filename);
   };

}