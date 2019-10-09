#include "stdio.h"
#include "string.h"
const int MAXN=3;
const int MAXK=20;
int A[MAXN]={3,5,8};
int M[MAXN]={3,2,2}; 
int main()
{
	int n=3;
	int K=MAXK;
	
	//dp[i+1][j]��ֵ��ʾ����ǰi�������Ƿ��ܹ��ӳ�j
	//���ƹ�ϵʽ�� dp[i+1][j]=(0<=k<=M[i]�� ��k*A[i] <=j ʱ����ʹdp[i][j-k*A[i]]Ϊ��) 
/*
	bool dp[MAXN+1][MAXK+1];
	memset(dp,false,(MAXN+1)*(MAXK+1));
	dp[0][0]=true; 
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<=K;++j)
		{
			for(int k=0;k<=M[i] && k*A[i] <=j;++k)
			{
				dp[i+1][j] =dp[i+1][j] | dp[i][j-k*A[i]];
			}
		}
	}
	if(dp[n][K])
	{
		printf("Yes!\n");
	}
	else
	{
		printf("No!\n");
	}
*/ 
//��һ������ �����˸��Ӷ� dp[i+1][j]��ʾ��i�ַ����ӵ�j�����ʣ���¶��ٸ�
//�м���״̬
//dp[i+1][j] 1.dp[i][j] >=0 m[i] 2.j<a[i]��c������ʣ�µ������� ������dp[i+1][j-a[i]] <=0(û��ʣ����) -1  3.else  dp[i][j-a[i]] -1  
//����ֻ����һά����dp[i] 0<=i<=K 
//vc++�����ȷ GNU/C++���� ���� 
	int dp[MAXK+1];
	memset(dp,-1,MAXK+1);
	dp[0]=0;
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<=K;++j)
		{
			if(dp[j] >=0)
			{
				dp[j]=M[i];
			}
			else 
			{
				if(j < A[i] || dp[j-A[i]] <=0)
				{
					dp[j]=-1;//���ܹ�����A[i]���Ԫ�� 
				}
				else
				{
					dp[j]=dp[j-A[i]]-1;//����������� 
			 	} 	
			}

				
			
		}	
	}
	if(dp[K] >=0)
		printf("Yes!");
	else 
		printf("No!");
	for(int j=0;j<=MAXK;++j)
	{
		printf("%d ",dp[j]);
	}
	return 0;
} 
