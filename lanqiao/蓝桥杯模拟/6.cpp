#include "stdio.h"
const int INF=65535;
const int SAME=0;
int map[10][10]={
{0,SAME,1,INF,1,1,INF,INF,INF,INF},
{0,1 ,0 ,1, INF ,1 ,INF ,INF ,INF, INF},
{0,INF ,1, 0 ,INF, 1, 1, INF, INF, INF},
{0,1 ,INF ,INF, 0 ,1, INF, 1 ,INF, INF},
{0,1, 1 ,1, 1, 0, 1 ,1, 1 ,1},
{0,INF, INF ,1, INF, 1, 0, INF, INF, 1},
{0,INF ,INF, INF ,1, 1, INF, 0, 1, INF},
{0,INF, INF, INF, INF ,1 ,1, INF ,1, 0}
};
int main()
{
	
} 
