//��Ǯ����
#include "stdio.h"
int coins[]={1,3,5};
int dp[100];
int main()
{
	//��̬�滮����
	//��dp[i]��ʾ��ǰ����ļ۸� dp[i]=min { dp(i-1),dp[i-3],dp[i-5] } + 1;
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
	 printf("������Ҫ���٣�%d��",dp[mon]);
 } 
