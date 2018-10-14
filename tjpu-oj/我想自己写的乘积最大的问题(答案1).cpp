#include "stdio.h"
#include <iostream>
char str[43];

typedef unsigned long long bigtype;
bigtype f[43][43] = { 0 };
/* thinking from http://blog.csdn.net/zwb8848happy/article/details/7480014
动态规划问题 设f[i][j] 表示前i个字符插入j个乘号，满足j<=i-1 然后动态转移方程为
f[i][j]=max { f[i-1][j-1]} * num[i,n-1] num[[i,n-1]表示i->末尾的字符长度
*/
bigtype max(bigtype a, bigtype b)
{
	return a > b ? a : b;
}
bigtype num(int i, int n)
{

	int fact = 1;
	bigtype res = 0;
	for (int j = n; j >= i; --j)
	{
		res = res + (str[j] - '0')*fact;
		fact = fact * 10;
	}
	return res;
}

int main()
{
	int N;
	int K;
	scanf("%d %d", &N, &K);
	scanf("%s", &str[1]);
	for (int i = 1; i <= N; ++i)
	{
		f[i][0] = num(1, i);
	}
	for (int i = 1; i <= N; ++i)//前i个字符串
	{
		for (int j = 0; j < i; ++j)
		{
			for (int k = j; k < i; ++k)//如果k是介于J(需要插入的*号个数)和i（前i个字符之间）表示一定可以进行向前可能存在一个最大的乘积
			{
				f[i][j] = max(f[i][j], f[k][j - 1] * num(k + 1, i)/*从k+1-j就是减少一个高位 用于求出增加一位的可能的最大乘积*/);
			}
		}
	}
	std::cout << f[N][K] << std::endl;
	//system("pause");
	return 0;
}
