#include "stdio.h"
//����������

const int MAX_M=20;//��������Ļ��ֵ����� 
const int MAX_N=30;//�����N����Ʒ
//�����������N����Ʒ �����ǻ���Ϊ������M�� �󻮷ַ�����ģM������  
int dp[MAX_M+1][MAX_N+1]={0};
int main()
{
	int n=4;
	int m=3;
	//dp[i][j]��ʾ��j����Ϊi�ݵ����� 
	
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
