#pragma once
#using "QuickGraph.dll"
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

	  QuickGraph::UndirectedGraph<int>^ LoadGraph(string filename, bool isQueryGraph = false);
   };

}