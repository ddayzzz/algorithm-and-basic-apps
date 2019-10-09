#include "stdio.h"
#include "string.h"
const int MAXN=3;
const int MAXK=20;
int A[MAXN]={3,5,8};
int M[MAXN]={3,2,2}; 
int main()
{
	int n=3;
	int K=MAXK;
	
	//dp[i+1][j]的值表示的是前i个数字是否能够加成j
	//递推关系式： dp[i+1][j]=(0<=k<=M[i]是 且k*A[i] <=j 时存在使dp[i][j-k*A[i]]为真) 
/*
	bool dp[MAXN+1][MAXK+1];
	memset(dp,false,(MAXN+1)*(MAXK+1));
	dp[0][0]=true; 
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<=K;++j)
		{
			for(int k=0;k<=M[i] && k*A[i] <=j;++k)
			{
				dp[i+1][j] =dp[i+1][j] | dp[i][j-k*A[i]];
			}
		}
	}
	if(dp[n][K])
	{
		printf("Yes!\n");
	}
	else
	{
		printf("No!\n");
	}
*/ 
//另一个方法 降低了复杂度 dp[i+1][j]表示第i种方法加到j最多能剩下下多少个
//有几种状态
//dp[i+1][j] 1.dp[i][j] >=0 m[i] 2.j<a[i]（c超过了剩下的容量） 或者是dp[i+1][j-a[i]] <=0(没有剩余了) -1  3.else  dp[i][j-a[i]] -1  
//这里只是用一维数组dp[i] 0<=i<=K 
//vc++结果正确 GNU/C++不行 怪事 
	int dp[MAXK+1];
	memset(dp,-1,MAXK+1);
	dp[0]=0;
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<=K;++j)
		{
			if(dp[j] >=0)
			{
				dp[j]=M[i];
			}
			else 
			{
				if(j < A[i] || dp[j-A[i]] <=0)
				{
					dp[j]=-1;//不能够加入A[i]这个元素 
				}
				else
				{
					dp[j]=dp[j-A[i]]-1;//如果具有容量 
			 	} 	
			}

				
			
		}	
	}
	if(dp[K] >=0)
		printf("Yes!");
	else 
		printf("No!");
	for(int j=0;j<=MAXK;++j)
	{
		printf("%d ",dp[j]);
	}
	return 0;
} 
