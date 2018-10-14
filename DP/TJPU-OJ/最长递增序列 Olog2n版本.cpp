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
	dp[1]=1;
	int maxcount=0; 
//状态转移方程 dp[i]=max {1,dp[j]+1}其中j<i
//i之前的序列为非递减序列 所以可以是用二分搜索 
//还是没搞懂 you can visit this : http://blog.sina.com.cn/s/blog_a16dd6d101015773.html 
	for(int i=2;i<=n;++i)
	{	
		//可以使用二分搜索搜索出最大的能够组成的子序列
		dp[i]=1;
		int lower=1;
		int upper=i;
		int mid;
		while(lower < upper)
		{
			mid=(lower+upper) / 2;
			if(data[mid] < data[i])
			{
				lower=mid +1;
			}
			else 
				upper=mid-1;
			//else if(data[mid]==data[i])
		}
		dp[i]=dp[lower]+1;
		maxcount=max(maxcount,dp[i]);
	} 
	printf("%d",maxcount);
}
