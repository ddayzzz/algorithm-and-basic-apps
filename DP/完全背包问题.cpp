#include "stdio.h"
//��������ظ�����Ʒ ��P58ҳ 
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
	//����ѭ��
	//���ƹ�ϵʽ��dp[i][j]=max{ dp[i][j] , dp[i+1][j-k*w[i]]+k*v[i] }  k��>=0�������� k�ǿ��Է���ı��� 
/*
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<=w;++j)
		{
			for(int k=0;k*vw[i][0] <=j;++k)//������жϿ��Է��뼸����ͬ����Ʒ ���ұ���k���ܴ������ڴ�Сj
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
	printf("���ļ�ֵ��%d",res);
	return 0;
} 
