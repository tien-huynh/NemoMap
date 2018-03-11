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

	  UndirectedGraph LoadGraph(string filename);
	  QueryGraph LoadGraph(string filename, bool isQueryGraph);
   };

}