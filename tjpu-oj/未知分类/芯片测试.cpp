#include "stdio.h"
#include <vector> 
int graph[21][21];
//����ԭ�� ��:http://blog.csdn.net/qq_32866009/article/details/50786874 
/*
���ݳ���ԭ�� ����n��оƬ����� �ͻ����� ��ô����һ������ӵ������n/2��оƬ, ��֪��оƬ���������ڻ�оƬ,����
ֻҪ���� ��i��оƬ ������n/2��оƬ����Ϊ�� ��ô���оƬ���Ǻõ�оƬ ?? 
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
