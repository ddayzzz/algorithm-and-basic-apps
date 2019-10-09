#include "stdio.h"
const int N=4;
const int MAX_WEIGHT=10000; 
int n=4;
int WV[N][2]={{2,3},{1,2},{3,4},{2,2}};//W V表示重量和价值
//int WV[N][2]={{2,3},{1,1},{3,9}};
int max(int a,int b)
{
	return a>b?a:b;
}
//从i的位置挑选不小于j的部分 
//每种物品仅有一件，可以选择放或不放 
int rec(int i,int j)
{
	int res;
	if(i==n)
	{
		//如果到达了末尾 就没有选择了 
		res=0;
	}else if(j < WV[i][0])
	{
		res=rec(i+1,j);//没有适合的重量选择了 所以需要从后面一个开始选择 
	}
	else {
		res=max(rec(i+1,j),rec(i+1,j-WV[i][0])+WV[i][1]);//判断加入该物品和不加入该物品的情况加入了该物品的价值会是最大的 
	}
	return res;
}
//使用动态规划
//状态转移方程 f[i][v]=max{ f[i-1][v],f[i-1][v-w[i]]+w[i] } 表示的就是第i次放入 将i物品放入的两种情况 1.可以放入 2.不放入
int dp[N][MAX_WEIGHT]={0};
int dp_flags[N]={0};
//dp数组保存i节点 选择放入j物品的价值 
//thinking from http://blog.csdn.net/kangroger/article/details/38864689 
int main()
{
	int maxweight=5;
	//int res=rec(0,maxweight);
	for(int i=n-1;i>=0;--i)
	{
		for(int j=0;j<=maxweight;++j)
		{
			if(j<WV[i][0])
			{
				dp[i][j]=dp[i+1][j];
					if(dp_flags[i])//如果是指定位置无法选择 那么也需要清除置位 
					{
						dp_flags[i]=0;
					}
			}
			else
			{
				int curr=dp[i+1][j];
				int addcurr=dp[i+1][j-WV[i][0]]+WV[i][1];
				if(addcurr>curr)
				{
					dp[i][j]=addcurr;
					dp_flags[i]=1;
				} 
				else
				{
					dp[i][j]=curr;
					if(dp_flags[i])
					{
						dp_flags[i]=0;//如果不选择i并且记录标志被置位 那么复位 
					}
				}
			}
		}
	}
	int res=dp[0][maxweight];
	printf("%d\n",res);
	for(int i=0;i<n;++i)
	{
		if(dp_flags[i]==1)
		{
			printf("选取%d物品，重：%d，价值：%d\n",i+1,WV[i][0],WV[i][1]);
		}
	 } 
	return 0;
	 
} 
