#include "Options.h"


RunOneVerb::RunOneVerb()
{
	setQueryGraphFile("");
}

string RunOneVerb::getQueryGraphFile() const
{
	return queryGraphFile;
}

void RunOneVerb::setQueryGraphFile(string temp)
{
	queryGraphFile = temp;
}

void RunOneVerb::GetUsage() const
{
	char* h_text = "\t-h, --querygraph\tREQUIRED. The query graph file\n";
	printf("%s \n", h_text);
}

RunManyVerb::RunManyVerb()
{
	setQueryGraphFolder("");
	setQueryGraphFiles(vector<string>());
}


string RunManyVerb::getQueryGraphFolder() const
{
	return queryGraphFolder;
}

void RunManyVerb::setQueryGraphFolder(string temp)
{
	queryGraphFolder = temp;
}

vector<string> RunManyVerb::getQueryGraphFiles()
{
	return queryGraphFiles;
}

void RunManyVerb::setQueryGraphFiles(vector<string> temp)
{
	queryGraphFiles = temp;
}

void RunManyVerb::GetUsage() const
{
	char* f_text = "\t-f, --folder\tA folder containing all the subgraphs (as text files) you want to query. This may be more convenient that using the <q> (<querygraphs>) parameter\n";
	char* q_text = "\t-q, --querygraph\tThe list of files containing the query graphs. If more than one, separate by space. If file name contains space, enclose in quotes.\n\n";
	printf("%s \n %s \n %s", "\tOne of the options -f (--folder) or -q (--querygraphs) has to be set.", f_text, q_text);
}

RunAllVerb::RunAllVerb()
{
	setSubgraphSize(0);
	setSaveTempMappingsToDisk(false);
}

int RunAllVerb::getSubgraphSize() const
{
	return subGraphSize;
}

void RunAllVerb::setSubgraphSize(int temp)
{
	subGraphSize = temp;
}

bool RunAllVerb::getSaveTempMappingsToDisk() const
{
	return saveTempMappingToDisk;
}

void RunAllVerb::setSaveTempMappingsToDisk(bool temp)
{
	saveTempMappingToDisk = temp;
}

void RunAllVerb::GetUsage() const
{
	char* n_text = "\t-n, --size\tREQUIRED. The subgraph size (i.e number of nodes)\n";
	char* d_text = "\t-d, --temptodisk\tThis will tell us how to store the mappings found at an expansion tree node for reuse in a child node\n\n";
	printf("%s \n %s", n_text, d_text);
}


//BaseVerb class
BaseVerb::BaseVerb()
{
	setThreshold(0);
	setInputGraphFile("");
	setSaveOutputs(false);
	setUseGrochow(false);
}

int BaseVerb::getThreshold() const
{
	return threashold;
}

void BaseVerb::setThreshold(int temp)
{
	threashold = temp;
}

string BaseVerb::getInputGraphFile() const
{
	return inputGraphFile;
}

void BaseVerb::setInputGraphFile(string temp)
{
	inputGraphFile = temp;
}

bool BaseVerb::getSaveOutputs() const
{
	return saveOutputs;
}

void BaseVerb::setSaveOutputs(bool temp)
{
	saveOutputs = temp;
}

bool BaseVerb::getUseGrochow() const
{
	return usesGrochow;
}

void BaseVerb::setUseGrochow(bool temp)
{
	usesGrochow = temp;
}

void BaseVerb::GetUsage()
{
	char* t_text = "\t-t, --threshold\tMinimum number of mappings required to be found for a subgraph to be seen as a frequent subgraph\n";
	char* g_text = "\t-g, --graph\tREQUIRED. The file containing the input graph. FUll or relative file path supported.\n";
	char* s_text = "\t-s, --save\tBoolean. If true, the output file containing the mappings for a query graph will be saved to disk\n";
	char* k_text = "\t-k, --gk\tBoolean. If true, the program will use Grochow-Kellis' algorithm instead of the modification we proposed for mapping\n";
	printf("%s \n %s \n %s \n %s", t_text, g_text, s_text, k_text);
}
//Options class
Options::Options()
{
	oneVerb = new RunOneVerb();
	manyVerb = new RunManyVerb();
	allVerb = new RunAllVerb();
}

RunOneVerb * Options::getOneVerb() const
{
	return oneVerb;
}

void Options::setOneVerb(RunOneVerb *value)
{
	oneVerb = value;
}

RunManyVerb * Options::getRunManyVerb() const
{
	return manyVerb;
}

void Options::setRunManyVerb(RunManyVerb *value)
{
	manyVerb = value;
}

RunAllVerb * Options::getRunAllVerb() const
{
	return allVerb;
}

void Options::setRunAllVerb(RunAllVerb *value)
{
	allVerb = value;
}

void Options::GetUsage()
{
	char* one_text = "\n\trunone\tRun program searching with JUST ONE query graph\n";
	char* many_text = "\trunmany\tRun program searching with two or more query graph\n";
	char* all_text = "\trunall\tRun program searching for all possible subgraphs of the specified size. Currently supports sizes 3 to 6.\n";
	printf("%s\n %s \n %s", one_text, many_text, all_text);
}