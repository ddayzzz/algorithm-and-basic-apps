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
//��̬��ת�Ʒ��� dp[i]=max { 1, dp[j]+1} j<i
	dp[1]=1;
	for(int i=2;i<=n;++i)
	{
		dp[i]=1;//Ĭ�ϱ����ǲ�������� 
		for(int j=1;j<i;++j)
		{
			if(data[i]>data[j])//����data[i]>data[j]��������еĳ��� 
			{
				dp[i]=max(dp[i],dp[j]+1);
			}
		}
	} 
	printf("%d", dp[n]);
	return 0;
}
