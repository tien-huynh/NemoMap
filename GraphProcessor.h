/*	Filename:		GraphProcessor.h
	Description:	Declaration of a class to read in graph data from a text file an construct the graph
	Author:			Tien Huynh
*/

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

	  /*	Method to read graph input from file and construct inputGraph
			@param
				filename: name of the text file that contain graph data
					Format of the file: each line is an edge with a target and a source vertex ID number;
						the target and source is separated by a tab or whitespace
						Example: edge from node #12 to #25 == "12		25" 
			@return
				A graph object constructed based on read in data*/
	  Graph LoadGraph(string filename);
   };

}