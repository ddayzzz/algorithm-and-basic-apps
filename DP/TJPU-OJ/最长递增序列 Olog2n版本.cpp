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
//״̬ת�Ʒ��� dp[i]=max {1,dp[j]+1}����j<i
//i֮ǰ������Ϊ�ǵݼ����� ���Կ������ö������� 
//����û�㶮 you can visit this : http://blog.sina.com.cn/s/blog_a16dd6d101015773.html 
	for(int i=2;i<=n;++i)
	{	
		//����ʹ�ö������������������ܹ���ɵ�������
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
