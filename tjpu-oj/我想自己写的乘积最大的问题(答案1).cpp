#include "stdio.h"
#include <iostream>
char str[43];

typedef unsigned long long bigtype;
bigtype f[43][43] = { 0 };
/* thinking from http://blog.csdn.net/zwb8848happy/article/details/7480014
��̬�滮���� ��f[i][j] ��ʾǰi���ַ�����j���˺ţ�����j<=i-1 Ȼ��̬ת�Ʒ���Ϊ
f[i][j]=max { f[i-1][j-1]} * num[i,n-1] num[[i,n-1]��ʾi->ĩβ���ַ�����
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
	for (int i = 1; i <= N; ++i)//ǰi���ַ���
	{
		for (int j = 0; j < i; ++j)
		{
			for (int k = j; k < i; ++k)//���k�ǽ���J(��Ҫ�����*�Ÿ���)��i��ǰi���ַ�֮�䣩��ʾһ�����Խ�����ǰ���ܴ���һ�����ĳ˻�
			{
				f[i][j] = max(f[i][j], f[k][j - 1] * num(k + 1, i)/*��k+1-j���Ǽ���һ����λ �����������һλ�Ŀ��ܵ����˻�*/);
			}
		}
	}
	std::cout << f[N][K] << std::endl;
	//system("pause");
	return 0;
}
