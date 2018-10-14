#include "stdio.h"
#include <iostream>
char s1[51];
char s2[51];
//Thinking from http://blog.chinaunix.net/uid-27767798-id-3479761.html
//and https://en.wikipedia.org/wiki/Longest_common_subsequence_problem
//http://blog.csdn.net/liufeng_king/article/details/8500084
int workmap[52][52];
void print(int r, int c)
{
	if (r == 0 || c == 0)
		return;
	if (s1[r] == s2[c])
	{
		print(r - 1, c - 1);
		printf("%c", s1[r]);
	}
	else
	{
		if (workmap[r - 1][c] == workmap[r][c])
			print(r - 1, c);
		else print(r, c - 1);
	}
}
int main()
{
	scanf("%s", &s1[1]);
	scanf("%s", &s2[1]);
	int n1 = strlen(&s1[1]);
	int n2 = strlen(&s2[1]);
	for (int i = 1; i <= n1;++i)
		workmap[1][i] = 0;
	for (int i = 1; i <= n2; ++i)
		workmap[i][1] = 0;
	for (int i = 2; i <= n1; ++i)
	{
		for (int j = 2; j <= n2; ++j)
		{
			if (s1[i] == s2[j])
			{
				workmap[i][j] = workmap[i - 1][j - 1]+1;
			}
			else
			{
				int left = workmap[i][j - 1];
				int top = workmap[i - 1][j];
				if (left > top)
				{
					workmap[i][j] = left;
				}
				else
				{
					workmap[i][j]= top;
				}
			}
		}
	}
	print(n1, n2);
	system("pause");
	return 0;
}
