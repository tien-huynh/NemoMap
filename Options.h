#pragma once
#include <string>
#include <vector>
using namespace std;
//Base class 
class BaseVerb
{
public:
	BaseVerb();
	int getThreshold() const;
	void setThreshold(int temp);
	string getInputGraphFile() const;
	void setInputGraphFile(string temp);
	bool getSaveOutputs() const;
	void setSaveOutputs(bool temp);
	bool getUseGrochow() const;
	void setUseGrochow(bool temp);

	void GetUsage();
private:
	int threashold = 0;
	string inputGraphFile = "";
	bool saveOutputs = false;
	bool usesGrochow = false;

};
//RunAll class
class RunAllVerb : public BaseVerb
{
public:
	RunAllVerb();
	int getSubgraphSize() const;
	void setSubgraphSize(int temp);
	bool getSaveTempMappingsToDisk() const;
	void setSaveTempMappingsToDisk(bool temp);

	void GetUsage() const;
private:
	int subGraphSize = 0;
	bool saveTempMappingToDisk = false;
};
//RunOne class 
class RunOneVerb : public BaseVerb
{
public:
	RunOneVerb();
	string getQueryGraphFile() const;
	void setQueryGraphFile(string temp);

	void GetUsage() const;
private:
	string queryGraphFile = "";

};
//RunMany class 
class RunManyVerb : public BaseVerb
{
public:
	RunManyVerb();
	string getQueryGraphFolder() const;
	void setQueryGraphFolder(string temp);
	vector<string> getQueryGraphFiles();
	void setQueryGraphFiles(vector<string> temp);

	void GetUsage() const;
private:
	string queryGraphFolder = "";
	vector<string> queryGraphFiles;
};
//Options class
class Options
{
public:
	Options();
	RunOneVerb* getOneVerb() const;
	void setOneVerb(RunOneVerb *value);

	RunManyVerb* getRunManyVerb() const;
	void setRunManyVerb(RunManyVerb *value);

	RunAllVerb* getRunAllVerb() const;
	void setRunAllVerb(RunAllVerb *value);

	void GetUsage();

private:
	RunOneVerb *oneVerb = new RunOneVerb();
	RunManyVerb *manyVerb = new RunManyVerb();
	RunAllVerb *allVerb = new RunAllVerb();
};