#include "stdio.h"
#include "string.h"
//背包问题之二 P60 
const int MAX_WEIGHT=20;
const int MAX_BAG=10;
int dp[MAX_BAG+1][MAX_WEIGHT*MAX_BAG]={0};
int min(int a,int b){
	return a<b?a:b;
}
int main()
{
	//初始化dp数组 dp[i][j]表示在前1~i-1个物品重 挑选的总值为j时的重量最小值 
	const int INF=MAX_WEIGHT;
	memset(dp,INF,MAX_WEIGHT*MAX_BAG+1);
	int wv[][2]={
		{3,4},{4,5},{2,3}
	};
	int n=3;
	int w=7;
	dp[0][0]=0;
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<=MAX_WEIGHT*MAX_BAG;++j)
		{
			if(j < wv[i][1])
			{
				dp[i+1][j]=dp[i][j];
			}
			else
			{
				dp[i+1][j]=min(dp[i][j],dp[i][j-wv[i][1]]+wv[i][0]);
			}
		}
	}
	int res=0;
	for(int i=0;i<=MAX_WEIGHT*MAX_BAG;++i)
	{
		if(dp[n][i] < w)
			res=i;
	}
	printf("%d",res);
	return 0;
}
