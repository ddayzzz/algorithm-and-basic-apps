#include "stdio.h"
int max(int a, int b)
{
	return a > b ? a : b;
}
int nums[11][11] = { 0 };
int dp[11] = { 0 };
int main()
{
	int sz;
	int column = 1;
	scanf("%d", &sz);
	for (int row = 1; row <= sz; ++row)
	{
		for (int c = 1; c <= column; ++c)
		{
			scanf("%d", &nums[row][c]);
		}
		++column;
	}
	//��������δӵ�һ������sz���ߣ�ÿ��ֻ�������½� ���½�
	// ������������һ�е����Ȩֵ
	//���ǲ��ô��ϵ��µ�DP ״̬ת�Ʒ��� dp[i][j]=max { dp[i+1][j+1],dp[i+1][j] }+num[i][j]
	for (int i = 1; i <= sz; ++i)
		dp[i] = nums[sz][i];
	int maxs = 0;
	for (int i = sz-1; i >= 0; --i)
	{
		for (int j = 1; j <= i; ++j)
		{
			int left = dp[j];
			int right = dp[j + 1];
			dp[j] = max(left, right) + nums[i][j];
			maxs = max(maxs, dp[i]);
			
		}
	}
	printf("%d", maxs);
	return 0;

}
/*
5
7 
3 8 
8 1 0 
2 7 4 4 
4 5 2 6 5 
��� 30 
*/
