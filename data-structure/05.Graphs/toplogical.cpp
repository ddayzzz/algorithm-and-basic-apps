#include <string>
#include "../GraphArray.h"
using namespace std;

int main()
{
    	///*拓扑排序
	string fn = "topologicalsort/P.txt";
	GraphMartix gm(fn, true);
	printf("Toplogical Khan:\n");
	gm.TopologicalSort_Khan();
	printf("Toplogical DFS:\n");
	gm.TopologicalSort_DFS();
	printf("Critical:\n");
	gm.CriticalSort();
	//*/
}