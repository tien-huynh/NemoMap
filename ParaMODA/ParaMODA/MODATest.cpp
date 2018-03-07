#include "MODATest.h"
MODATest::MODATest()
{
	sb = "Processing Graph...";
}

void MODATest::Run(int size, char *argv[])
{
	try
	{
		Options *invokedVerbInstance = new Options();
		int verb = 0;
		if (size == 1)		//execute program no args  
		{
			invokedVerbInstance->GetUsage();
			exit(0);
		}
		if (size == 2)		//execute program run[...]
		{
			validateVerb(argv, invokedVerbInstance);
		}
		if (size > 4)	///min [prog] [run...] -g filename 
		{
			string verbName = string(argv[1]);
			string filename;
			if (verbName == "runone" && string(argv[2]) == "-g")
			{
				filename = string(argv[3]);
				RunOneVerb *temp = new RunOneVerb();
				invokedVerbInstance->setOneVerb(temp);
				invokedVerbInstance->setRunAllVerb(nullptr);
				invokedVerbInstance->setRunManyVerb(nullptr);
				temp->setInputGraphFile(filename);
				bool req = false;
				//min [prog] [run..] -g filename -h filename
				if (size > 5)
				{
					req = setOptions(argv, size, invokedVerbInstance);
				}
				else
				{
					printErrorMessage();
				}
				if (!req)
				{
					printErrorMessage();
				}
				verb = 1;
			}
			else if (verbName == "runall" && string(argv[2]) == "-g")
			{
				filename = string(argv[3]);
				RunAllVerb *temp = new RunAllVerb();
				invokedVerbInstance->setOneVerb(nullptr);
				invokedVerbInstance->setRunAllVerb(temp);
				invokedVerbInstance->setRunManyVerb(nullptr);
				temp->setInputGraphFile(filename);
				bool req = false;
				//min needs to have -n 
				if (size > 5)
				{
					req = setOptions(argv, size, invokedVerbInstance);
				}
				else
				{
					invokedVerbInstance->getRunAllVerb()->GetUsage();
					exit(0);
				}
				if (!req)
				{
					invokedVerbInstance->getRunAllVerb()->GetUsage();
					exit(0);
				}
				verb = 2;
			}
			else if (verbName == "runmany" && string(argv[2]) == "-g")
			{
				filename = string(argv[3]);
				RunManyVerb *temp = new RunManyVerb();
				invokedVerbInstance->setOneVerb(nullptr);
				invokedVerbInstance->setRunAllVerb(nullptr);
				invokedVerbInstance->setRunManyVerb(temp);
				temp->setInputGraphFile(filename);
				bool req = false;
				//min needs to have folder or files 
				if (size > 5)
				{
					req = setOptions(argv, size, invokedVerbInstance);
				}
				else
				{
					invokedVerbInstance->getRunManyVerb()->GetUsage();
					exit(0);
				}
				if (!req)
				{
					if (invokedVerbInstance->getRunManyVerb() != nullptr)
						invokedVerbInstance->getRunManyVerb()->GetUsage();
					else if (invokedVerbInstance->getRunAllVerb() != nullptr)
						invokedVerbInstance->getRunAllVerb()->GetUsage();
					else if (invokedVerbInstance->getOneVerb() != nullptr)
						invokedVerbInstance->getOneVerb()->GetUsage();
					exit(0);
				}
				verb = 3;
			}
			else
			{
				invokedVerbInstance->GetUsage();
				exit(0); 
			}
		}
		else
		{
			invokedVerbInstance->GetUsage();
			exit(0);
		}
		ModaAlgorithms *modaAlgo = new ModaAlgorithms();
		GraphProcessor *graphProc = new GraphProcessor();
		UndirectedGraph<int> *inputGraph = new UndirectedGraph<int>();
		//	//= new UndirectedGraph<int>();
		if (verb == 1)
		{
			modaAlgo->setUseModifiedGrochow(invokedVerbInstance->getOneVerb()->getUseGrochow() == false);
			inputGraph = graphProc->LoadGraph(invokedVerbInstance->getOneVerb()->getInputGraphFile());
			if (invokedVerbInstance->getOneVerb()->getSaveOutputs())
			{
				createDirectory();
			}
		}
		else if (verb == 2)
		{
			modaAlgo->setUseModifiedGrochow(invokedVerbInstance->getRunAllVerb()->getUseGrochow() == false);
			inputGraph = graphProc->LoadGraph(invokedVerbInstance->getRunAllVerb()->getInputGraphFile());
			if (invokedVerbInstance->getRunAllVerb()->getSaveOutputs())
			{
				createDirectory();
			}
		}
		else if (verb == 3)
		{
			modaAlgo->setUseModifiedGrochow(invokedVerbInstance->getRunManyVerb()->getUseGrochow() == false);
			inputGraph = graphProc->LoadGraph(invokedVerbInstance->getRunManyVerb()->getInputGraphFile());
			if (invokedVerbInstance->getRunManyVerb()->getSaveOutputs())
			{
				createDirectory();
			}
		}
			
		cout << "Input Graph (G): Nodes - " + to_string(inputGraph->getVertexCount()) + "; Edges: " + to_string(inputGraph->getEdgeCount()) << endl;
		
		//	RunOneVerb *oneVerb = invokedVerbInstance->getOneVerb();
		//	if (oneVerb != nullptr)
		//	{
		//	QueryGraph *queryGraph = reinterpret_cast<QueryGraph*>(graphProc->LoadGraph(oneVerb->getInputGraphFile()));		//try
		//		//Process(oneVerb, inputGraph, queryGraph);
		//		return;
		//	}
		//	RunManyVerb *manyVerb = invokedVerbInstance->getRunManyVerb();
		//	if (manyVerb != nullptr)
		//	{
		//		vector<QueryGraph*> queryGraphs;
		//		//= new vector<QueryGraph>;
		//		if (manyVerb->getQueryGraphFolder() == "")
		//		{
		//			queryGraphs.resize(manyVerb->getQueryGraphFiles().size()); 
		//			for (string gFile : manyVerb->getQueryGraphFiles())
		//			{
		//				QueryGraph *qGraph = reinterpret_cast<QueryGraph*>(graphProc->LoadGraph(gFile, true));
		//				queryGraphs.push_back(qGraph);	//check
		//			}
		//		}
		//		else
		//		{
		//			//files = Directory.GetFiles(runManyVerb.QueryGraphFolder);
		//			//get files from directory in vector<string>
		//			vector<string> files;
		//			queryGraphs.resize(files.size());
		//			for (string gFile : files)
		//			{
		//				QueryGraph *qGraph = reinterpret_cast<QueryGraph*>(graphProc->LoadGraph(gFile, true));
		//				queryGraphs.push_back(qGraph);
		//			}
		//		}
		//		for (QueryGraph *qGraph : queryGraphs)
		//		{
		//			//Process(manyVerb, inputGraph, qGraph);
		//		}
		//		return;
		//	}
		//	RunAllVerb *allVerb = invokedVerbInstance->getRunAllVerb();
		//	if (allVerb != nullptr)
		//	{
		//		if (allVerb->getSubgraphSize() < 3 || allVerb->getSubgraphSize() > 5)
		//		{
		//			cout << "Invalid input for -s (--size; subgraph size). Program currently supports sizes from 3 to 5.\n\n" << endl;
		//			allVerb->GetUsage();		//fill values 
		//			exit(0);
		//		}
		//		if (allVerb->getSubgraphSize() >= inputGraph->getVertexCount())
		//		{
		//			cout << "The specified subgraaph size is too large.\n\n\n" << endl;
		//			allVerb->GetUsage();
		//			exit(0);
		//		}
		//		modaAlgo->BuildTree(allVerb->getSubgraphSize());
		//		//Process(allVerb, inputGraph, nullptr, allVerb->getSubgraphSize(), allVerb->getSaveTempMappingsToDisk());
		//		return;

		//	}
	}
	catch (exception ex)
	{
		printErrorMessage();
	}
}

void MODATest::createDirectory()
{
	if (CreateDirectory("..//MappingOutputs", NULL) || ERROR_ALREADY_EXISTS == GetLastError())
	{
	}//do nothing creates directory 
}

/*Still not tested, needs other classes
*/
//void ParaMODA::MODATest::Process(BaseVerb *options, UndirectedGraph<int> *inputGraph, QueryGraph *queryGraph, int subGraphSize, bool saveTempMappingsToDisk)
//{
//	//threadName
//	thread::id main_thread = this_thread::get_id();
//	if (queryGraph != nullptr)
//	{
//		cout << "Thread ";
//		cout << main_thread;
//		cout << ":\tQuery Graph (H): Nodes - " + queryGraph->getVertexCount();
//		cout << "; Edges: " + queryGraph->getEdgeCount() << endl;
//	}
//	ExecutionStopwatch *sw;//
//	sw = new ExecutionStopwatch();
//	if (saveTempMappingsToDisk == false)
//	{
//		sw->Start();
//
//		ModaAlgorithms *tempAlgo = new ModaAlgorithms();
//		//Dictionary<QueryGraph, ICollection<Mapping>> ?
//		//map< QueryGraph, list<Mapping>> 
//		auto frequentSubgraphs = tempAlgo->Algorithm1(inputGraph, queryGraph, subGraphSize, options->getThreshold());
//
//		sw->Stop();
//
//		//process output
//		int totalMappings = 0;
//		sb += "\nCompleted. Result Summary\n";
//		sb += "-------------------------------------------\n";
//		if (options->getSaveOutputs() == false)
//		{
//			for (auto qGraph : frequentSubgraphs)	//first QueryGraph second list<Mapping>
//			{
//				if (qGraph.second == nullptr) //if no Mappings   might change to qGraph.second.empty()
//				{
//					//qGraph.first QueryGraph subgraph tostring ?
//					sb += "\tSub-graph: " + qGraph.first + "\t Mappings: 0\t Is Frequent Subgraph? false\n" << endl;
//				}
//				else  //found mappings 
//				{
//					int count = qGraph.second.size() ; //change?
//					sb += "\tSub-graph: " + qGraph.first + "\t Mappings: " + count + "\t Is Frequent Subgraph? " + qGraph.first.isIsFrequentSubgraph() + "\n";
//					totalMappings += count;
//				}
//			}
//		}
//		else
//		{
//			for (auto qGraph : frequentSubgraphs)
//			{
//				if (qGraph.second == nullptr)	//qGraph.second.empty()
//				{
//					//toString 
//					sb += "\tSub-graph: " + qGraph.first.ToString() + "\t Is Frequent Subgraph? false\n";
//				}
//				else
//				{
//					string filesb = "";
//					int count = qGraph.second.size();
//					sb += "\tSub-graph: " + qGraph.first.ToString() + "\t Mappings: " + count + "\t Is Frequent Subgraph? " + 
//						qGraph.first->getIsFrequentSubgraph() + "\n";
//					for (auto mapping : qGraph.second)
//					{
//						filesb += mapping->GetMappedNodes();
//					}
//					totalMappings += count;
//					try
//					{
//						ofstream writefile;
//						writefile.open(qGraph.first.getIdentifier() + ".txt");
//						writefile << filesb;
//						writefile.close();
//						//write filesb to file
//					}
//					catch (exception ex)
//					{
//						//error line 
//						cout << "Failed to write file containing mappings found for querygraph " + qGraph.first->getIdentifier() + " to disk.\n\n" << endl;
//					}
//				}
//			}
//		}
//
//		sb += "\nTime Taken: " + sw->getElapsedMilliseconds();
//		sb += "ms)\n Network: Nodes - " + inputGraph->getVertexCount();
//		sb += "; Edges: " + inputGraph->getEdgeCount();
//		sb += "; \nTotal Mappings found : " + totalMappings;
//		sb += "\nSubgraph Size : " + subGraphSize;
//		sb += "\n-------------------------------------------\n";
//		//frequentSubgraphs.Clear();	//look up
//	}
//	else  // if (saveTempMappingsToDisk == true)
//	{
//		sw->Start();
//		ModaAlgorithms *algo = new ModaAlgorithms();
//		auto frequentSubgraphs = algo->Algorithm1_C(inputGraph, queryGraph, subGraphSize, options->getThreshold());
//		sw->Stop();
//
//		//output
//		int totalMappings = 0;
//		sb += "\nCompleted. Result Summary\n";
//		sb += "-------------------------------------------\n";
//		if (options->getSaveOutputs() == false)
//		{
//			for (auto qGraph : frequentSubgraphs)
//			{
//				if (qGraph.second == nullptr)	//? qGraph.second.empty()
//				{
//					sb += "\tSub-graph: " + qGraph.first.ToString() + "\t Is Frequent Subgraph? false\n";		//? toString 
//				}
//				else
//				{
//					int count = qGraph.second.size();
//						// int.Parse(qGraph.Value.Split('#')[0]);
//					sb += "\tSub-graph: " + qGraph.first.ToString() + "\t Mappings: " + count + "\t Is Frequent Subgraph? " + qGraph.first.getIsFrequentSubgraph() + "\n";
//					totalMappings += count;
//				}
//			}
//		}
//		else // if (options.SaveOutputs == true)
//		{
//			for (auto qGraph : frequentSubgraphs)
//			{
//				string fileSb = "";
//				if (qGraph.second == nullptr)	//qGraph.second.empty()
//				{
//					sb += "\tSub-graph: " +qGraph.first.ToString() + "\t Mappings: 0\t Is Frequent Subgraph? false\n";
//				}
//				else
//				{
//					int count = qGraph.second.size();
//					sb += "\tSub-graph: " + qGraph.first.ToString() + "\t Mappings: " + count + " \t Is Frequent Subgraph? " + qGraph.first.getIsFrequentSubgraph() + "\n";
//					//TODO: Big bug here. This line is so wrong. Redo!
//
//					auto mappings = qGraph.first->ReadMappingsFromFile(qGraph.second);
//
//					for (auto mapping : mappings)
//					{
//						fileSb += mapping->GetMappedNodes();
//					}
//					totalMappings += count;
//
//					try
//					{
//						ofstream writefile;
//						writefile.open(qGraph.first.getIdentifier() + ".txt");
//						writefile << fileSb;
//						writefile.close();
//						//write filesb to file
//						//write to file 
//						//File.WriteAllText(Path.Combine(OUTPUT_DIR, qGraph.Key.Identifier + ".txt"), fileSb.ToString());
//					}
//					catch (exception ex)
//					{
//						//Console.Error.WriteLine("Failed to write file containing mappings found for querygraph {0} to disk.\n\n{1}", qGraph.Key.Identifier, ex);
//					}
//				}
//			}
//		}
//		sb += "\nTime Taken: " + sw->getElapsedMilliseconds();
//		sb += "ms)\n Network: Nodes - " + inputGraph->getVertexCount();
//		sb += "; Edges: " + inputGraph->getEdgeCount();
//		sb += "; \nTotal Mappings found : " + totalMappings;
//		sb += "\nSubgraph Size : " + subGraphSize;
//		sb += "\n-------------------------------------------\n";	
//		frequentSubgraphs.Clear();		//might remove ?
//	}
//	cout << sb << endl;	//print sb 
//	try
//	{
//		ofstream writefile;
//		writefile.open(options->getInputGraphFile() + ".txt");
//		writefile << sb;
//		writefile.close();
//		//write filesb to file
//		// Dump general result
//		//File.WriteAllText(Path.GetFileName(options.InputGraphFile) + ".out", sb.ToString());
//	}
//	catch(exception ex) {}
//	sb = "";
//}

bool MODATest::setOptions(char * args[], int size, Options *invokedVerbInstance)
{
	bool req = false;
	for (int i = 4; i < size; i++)
	{
		string tempVal = string(args[i]);
		//check for OneVerb  -h 
		if (invokedVerbInstance->getOneVerb() != nullptr)
		{
			if (tempVal == "-h")	//required 
			{
				if (i + 1 < size)
				{
					invokedVerbInstance->getOneVerb()->setQueryGraphFile(string(args[i + 1]));
					req = true;
					i = i + 1;
				}
				else
				{
					invokedVerbInstance->getOneVerb()->GetUsage();
					exit(0);
				}
			}
		}
		else if (invokedVerbInstance->getRunAllVerb() != nullptr)
		{
			if (tempVal == "-n")
			{
				if (size > i + 1)
				{
					invokedVerbInstance->getRunAllVerb()->setSubgraphSize(int(args[i + 1]));
					req = true;
					i += 1;
				}
				else
				{
					invokedVerbInstance->getRunAllVerb()->GetUsage();
				}
			}
			else if (tempVal == "-d")
			{
				invokedVerbInstance->getRunAllVerb()->setSaveTempMappingsToDisk(true);
			}
		}
		else if (invokedVerbInstance->getRunManyVerb() != nullptr)
		{
			if (tempVal == "-f")
			{
				if (size > i + 1)
				{
					invokedVerbInstance->getRunManyVerb()->setQueryGraphFolder(string(args[i + 1]));
					i += 1;
					req = true;
				}
				else
				{
					invokedVerbInstance->getRunManyVerb()->GetUsage();
				}
			}
			else if (tempVal == "-q")
			{
				if (size > i + 1)
				{
					vector<string> tempVal;
					for (int j = i + 1; j < size; j++)
					{
						string tempArg = string(args[j]);
						if (tempArg == "-t" || tempArg == "-s" || tempArg == "-k")
						{
							i = j - 1;
							break;
						}
						else
						{
							tempVal.push_back(tempArg);
						}
					}
					invokedVerbInstance->getRunManyVerb()->setQueryGraphFiles(tempVal);
					req = true;
				}
				else
				{
					printErrorMessage();
				}
			}
		}
		if (tempVal == "-t")
		{
			if (i + 1 < size)
			{
				if (invokedVerbInstance->getOneVerb() != nullptr)
					invokedVerbInstance->getOneVerb()->setThreshold(int(args[i + 1]));
				else if (invokedVerbInstance->getRunAllVerb() != nullptr)
					invokedVerbInstance->getRunAllVerb()->setThreshold(int(args[i + 1]));
				else if (invokedVerbInstance->getRunManyVerb() != nullptr)
					invokedVerbInstance->getRunManyVerb()->setThreshold(int(args[i + 1]));
				i++;
			}
			else
			{
				printErrorMessage();
			}
		}
		if (tempVal == "-s")
		{
			if (invokedVerbInstance->getOneVerb() != nullptr)
				invokedVerbInstance->getOneVerb()->setSaveOutputs(true);
			else if (invokedVerbInstance->getRunAllVerb() != nullptr)
				invokedVerbInstance->getRunAllVerb()->setSaveOutputs(true);
			else if (invokedVerbInstance->getRunManyVerb() != nullptr)
				invokedVerbInstance->getRunManyVerb()->setSaveOutputs(true);
		}
		if (tempVal == "-k")
		{
			if (invokedVerbInstance->getOneVerb() != nullptr)
				invokedVerbInstance->getOneVerb()->setUseGrochow(true);
			else if (invokedVerbInstance->getRunAllVerb() != nullptr)
				invokedVerbInstance->getRunAllVerb()->setUseGrochow(true);
			else if (invokedVerbInstance->getRunManyVerb() != nullptr)
				invokedVerbInstance->getRunManyVerb()->setUseGrochow(true);
		}
	}
	return req;
}

void MODATest::printErrorMessage()
{
	cout << "Invalid input. Program is terminating." << endl;
	exit(0);
}
//Prints possible actions for Verb
void MODATest::validateVerb(char * argv[], Options *invokedVerbInstance)
{
	string verb = string(argv[1]);
	BaseVerb *temp = new BaseVerb();
	if (verb == "runone")
	{
		invokedVerbInstance->getOneVerb()->GetUsage();
		cout << "\t---------------------------------" << endl;
		temp->GetUsage();
		exit(0);
	}
	else if (verb == "runmany")
	{
		invokedVerbInstance->getRunManyVerb()->GetUsage();
		cout << "\t---------------------------------" << endl;
		temp->GetUsage();
		exit(0);
	}
	else if (verb == "runall")
	{
		invokedVerbInstance->getRunAllVerb()->GetUsage();
		cout << "\t---------------------------------" << endl;
		temp->GetUsage();
		exit(0);
	}
	else
	{
		printErrorMessage();
	}
}