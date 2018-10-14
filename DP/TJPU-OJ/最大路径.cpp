#include "stdio.h"
#include <iostream>
//thinking from http://blog.csdn.net/chlrandybear/article/details/22753089
int M;
int N;
int dp[31][31]={0};
int getleft(int n)
{
	if(n == 1)
		return M;
	return n-1; 
}
int getright(int n)
{
	if(n==M)
		return 1;
	return n+1;
}
int find_fenzhi(int n,int k)
{
	//分治法 n表示报数的人，k表示剩余的次数
	if(k==0)
	{
		return (n==1?1:0);
	}
	int left=find_fenzhi(getleft(n),k-1);
	int right=find_fenzhi(getright(n),k-1);
	return left+right;
	
}
//用动态规划
//状态转移方程 dp[i][N]= dp[left(i)][N-1]+dp[right(i)][N-1]表示从左右两边的下一次传球的方法数 
int main()
{
	
	scanf("%d %d",&M,&N);
	//printf("%d",find_fenzhi(1,N)); 
	dp[1][0]=1;
	for(int i=1;i<=N;++i)
	{
		for(int j=1;j<=M;++j) 
		{
			dp[j][i]=dp[getleft(j)][i-1]+dp[getright(j)][i-1];
		}
	}	
	printf("%d",dp[1][N]);
	return 0;
}
