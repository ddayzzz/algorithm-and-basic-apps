#include "stdio.h"
const int N=4;
const int MAX_WEIGHT=10000; 
int n=4;
int WV[N][2]={{2,3},{1,2},{3,4},{2,2}};//W V��ʾ�����ͼ�ֵ
//int WV[N][2]={{2,3},{1,1},{3,9}};
int max(int a,int b)
{
	return a>b?a:b;
}
//��i��λ����ѡ��С��j�Ĳ��� 
//ÿ����Ʒ����һ��������ѡ��Ż򲻷� 
int rec(int i,int j)
{
	int res;
	if(i==n)
	{
		//���������ĩβ ��û��ѡ���� 
		res=0;
	}else if(j < WV[i][0])
	{
		res=rec(i+1,j);//û���ʺϵ�����ѡ���� ������Ҫ�Ӻ���һ����ʼѡ�� 
	}
	else {
		res=max(rec(i+1,j),rec(i+1,j-WV[i][0])+WV[i][1]);//�жϼ������Ʒ�Ͳ��������Ʒ����������˸���Ʒ�ļ�ֵ�������� 
	}
	return res;
}
//ʹ�ö�̬�滮
//״̬ת�Ʒ��� f[i][v]=max{ f[i-1][v],f[i-1][v-w[i]]+w[i] } ��ʾ�ľ��ǵ�i�η��� ��i��Ʒ������������ 1.���Է��� 2.������
int dp[N][MAX_WEIGHT]={0};
int dp_flags[N]={0};
//dp���鱣��i�ڵ� ѡ�����j��Ʒ�ļ�ֵ 
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
					if(dp_flags[i])//�����ָ��λ���޷�ѡ�� ��ôҲ��Ҫ�����λ 
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
						dp_flags[i]=0;//�����ѡ��i���Ҽ�¼��־����λ ��ô��λ 
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
			printf("ѡȡ%d��Ʒ���أ�%d����ֵ��%d\n",i+1,WV[i][0],WV[i][1]);
		}
	 } 
	return 0;
	 
} 
