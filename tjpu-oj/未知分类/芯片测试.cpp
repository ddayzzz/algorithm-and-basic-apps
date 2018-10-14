#include "stdio.h"
#include <vector> 
int graph[21][21];
//抽屉原理 哭:http://blog.csdn.net/qq_32866009/article/details/50786874 
/*
根据抽屉原理 共有n块芯片放入好 和坏盒子 那么存在一个盒子拥有至少n/2快芯片, 已知好芯片的数量多于坏芯片,所以
只要满足 第i快芯片 被至少n/2快芯片测试为好 那么这块芯片就是好的芯片 ?? 
*/
int main()
{
	int n;	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
		{
			scanf("%d",&graph[i][j]);
		}
	 }

	std::vector<int> res;
	for(int i=1;i<=n;++i)
	{
		int test=0;
		for(int k=1;k<=n;++k)
		{
			if(k !=i)
			{
				if(graph[k][i]==1)
					++test;
			}
		}
		if(test >= n /2)
		{
			printf("%d ",i);
		}
	}
	return 0;
} 
