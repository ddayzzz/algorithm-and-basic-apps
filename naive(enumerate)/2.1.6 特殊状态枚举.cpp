#include "stdio.h"
#define MAX_N 20
bool used[MAX_N];
int perm[MAX_N];
//生成{0,1,2,3...，n-1}排列
void permutation1(int pos,int n)
{
	if(pos==n)
	{
		int i;
		printf("{ ");
		for(i=0;i <n-1;++i)
		{
			printf("%d,",perm[i]);
		}
		printf("%d }\n",perm[i]);
		return;
	}
	for(int i=0;i<n;++i)
	{
		if(!used[i])
		{
			perm[pos]=i;
			used[i]=true;
			permutation1(pos+1,n);
			used[i]=false;
		}
	}
} 
//使用标准库的版本
#include <algorithm>
int perm2[MAX_N];
void permutation2(int n)
{
	for(int i=0;i<n;++i)
	{
		perm2[i]=i;
	}
	do{
		printf("{ ");
		for(int i=0;i<n-1;++i)
			printf("%d,",perm2[i]);
		printf("%d }\n",perm2[n-1]);
		
	}while(std::next_permutation(perm2,perm2+n));
 } 
int main()
{
	printf("Permutation using DFS : \n");
	permutation1(0,16);
	printf("Permutation using STL algorithm : \n");
	permutation2(16);
	return 0;
}
