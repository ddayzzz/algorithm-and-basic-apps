#include "stdio.h"
//划分数问题

const int MAX_M=20;//这个是最大的划分的组数 
const int MAX_N=30;//这个是N个物品
//问题是有最多N个物品 将他们划分为不超过M组 求划分方法数模M的余数  
int dp[MAX_M+1][MAX_N+1]={0};
int main()
{
	int n=4;
	int m=3;
	//dp[i][j]表示将j划分为i份的总数 
	
	dp[0][0]=1;
	for(int i=1;i<=m;++i)
	{
		for(int j=0;j<=n;++j)
		{
			if(j-i>=0)
			{
				dp[i][j]=(dp[i-1][j] + dp[i][j-i]) % m;
			}
			else
			{
				dp[i][j]=dp[i-1][j];
			}
		}
	}
	printf("%d\n",dp[m][n]);
	return 0;
} 
