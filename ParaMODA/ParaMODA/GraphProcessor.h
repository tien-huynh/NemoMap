#pragma once
#include "UndirectedGraph.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class GraphProcessor
{
public:
	GraphProcessor();
	~GraphProcessor();

	UndirectedGraph<int>* LoadGraph(string filename, bool isQueryGraph = false);
};