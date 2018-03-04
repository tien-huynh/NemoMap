#include "Mapping.h"
#include "GraphProcessor.h"
#include <sstream>
using namespace ParaMODAImpl;

int main()
{
   int hold;
   //map<int, int> f1, f2;
   //f1[1] = 2;
   //f1[4] = 5;
   //f1[3] = 7;

   //f2[6] = 23;
   //f2[13] = 54;
   //f2[2] = 79;

   //Mapping m1 = Mapping(f1, 0);
   //Mapping m2 = Mapping(f2, 0);

   //if (m1 == m2)
	  //cout << "==" <<endl;
   //else
	  //cout << "!=" <<endl;

   //cout << m1.GetMappedNodes() << endl;
   //cout << m2 << endl;

   string filename = "SampleInputGraph.txt";
   GraphProcessor gp = GraphProcessor();
   gp.LoadGraph(filename);




   cin >> hold;



   //string h = "";
   //string g = h;
   //string result;
   //if (Function.size())
   //{
	  //h += "[";
	  //g += " => [";
	  //map<int, int>::iterator itr =Function.begin();
	  //h += to_string((itr)->first);
	  //g += to_string((itr++)->second);
	  //for (; itr != Function.end(); itr++)
	  //{
		 //h += '-' + to_string(itr->first);
		 //g += '-' + to_string(itr->second);
	  //}
	  //h += "]";
	  //g += "]";
   //}
   //cout << h << g;
   //cin >> g;
}