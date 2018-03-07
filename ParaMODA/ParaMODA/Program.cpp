#include "MODATest.h"
using namespace std;
int main(int argc, char *argv[])
{
	//Command line: just execute program ParaMODA: displays verb types
	//execute program ParaMODA run[all/many/one]: displays possible actions 
	MODATest test;
	test.Run(argc, argv);
	return 0;
}
