//找钱问题
#include "stdio.h"
int coins[]={1,3,5};
int dp[100];
int main()
{
	//动态规划问题
	//设dp[i]表示当前找零的价格 dp[i]=min { dp(i-1),dp[i-3],dp[i-5] } + 1;
	 int mon;
	 dp[0]=0;
	 scanf("%d",&mon);
	 for(int i=1;i<=mon;++i)
	 {
	 	int min=100000;
	 	for(int j=0;j<3;++j)
	 	{
	 		if(i-coins[j] >= 0)
	 		{
				if(min > dp[i-coins[j]])
					min=dp[i-coins[j]];		 			
			}
		}
		dp[i]=min+1;
	 }
	 printf("找零需要最少：%d张",dp[mon]);
 } 
