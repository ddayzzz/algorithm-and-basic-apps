#include "stdio.h"
//thinking from http://www.2cto.com/kf/201310/251458.html 
int data[51];
int dp[51];
int max(int a, int b) {
	return a>b ? a : b;
}
int main()
{
	int n;
	scanf("%d", &n);
	int i;
	for (i = 1; i <= n; ++i)
	{
		scanf("%d", &data[i]);
	}
//动态的转移方程 dp[i]=max { 1, dp[j]+1} j<i
	dp[1]=1;
	for(int i=2;i<=n;++i)
	{
		dp[i]=1;//默认本身是不会递增的 
		for(int j=1;j<i;++j)
		{
			if(data[i]>data[j])//搜索data[i]>data[j]的最大序列的长度 
			{
				dp[i]=max(dp[i],dp[j]+1);
			}
		}
	} 
	printf("%d", dp[n]);
	return 0;
}
