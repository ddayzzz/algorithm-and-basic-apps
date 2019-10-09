#include "stdio.h"
//允许存在重复的物品 书P58页 
const int MAX_WEIGHT=20;
const int MAX_BAG=10;
int dp[MAX_BAG][MAX_WEIGHT]={0};
int max(int a,int b){
	return a>b?a:b;
}
int main()
{
	
	int wv[][2]={
		{3,4},{4,5},{2,3}
	};
	int n=3;
	int w=7;
	//三重循环
	//递推关系式：dp[i][j]=max{ dp[i][j] , dp[i+1][j-k*w[i]]+k*v[i] }  k是>=0的正整数 k是可以放入的倍数 
/*
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<=w;++j)
		{
			for(int k=0;k*vw[i][0] <=j;++k)//这个是判断可以放入几个相同的物品 并且倍数k不能大于生于大小j
			{
				dp[i+1][j]=max(dp[i+1][j],dp[i][j-vw[i][0]*k]+k*vw[i][1]);
			}
		}
	}
*/ 
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<=w;++j)
		{
			if(j<wv[i][0])
			{
				dp[i+1][j]=dp[i][j];
			}
			else
			{
				dp[i+1][j]=max(dp[i][j],dp[i+1][j-wv[i][0]]+wv[i][1]);
			}
		}
	}
	int res=dp[n][w];
	printf("最大的价值：%d",res);
	return 0;
} 
