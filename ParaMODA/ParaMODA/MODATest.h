#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include <map>
#include <list>
#include <thread>
#include <exception>
#include <fstream>
#include "UndirectedGraph.h"
#include "Options.h"
#include "GraphProcessor.h"
#include "ModaAlgorithms.h"
using namespace std;
class MODATest
{
public:
	MODATest();
	static void Run(int size, char *argv[]);
private:
	const string OUTPUT_DIR = "...//MappingOutputs";
	string sb = "";
	static void createDirectory();
	//static void Process(BaseVerb *options, UndirectedGraph<int> *inputGraph, QueryGraph *queryGraph = nullptr, int subGraphSize = -1, bool saveTempMappingsToDisk = false);
	static bool setOptions(char* args[], int size, Options *invokedVerbInstance);
	static void printErrorMessage();
	static void validateVerb(char *argv[], Options *invokedVerbInstance);
};
