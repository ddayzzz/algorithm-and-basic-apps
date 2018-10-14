#include "stdio.h"
#include <iostream>
#include <cmath>
int N;
int ans = 0;
int maps[9][9];//0 not be place 1 for being placed ;2 is white set;3 is black set
int black[9];
int white[9];
bool vaild(int i, bool isblack)
{
	//i表示的是i行 flag[i]表示的是列 需要检查之前的行是否有冲突 
	int *flag = black;
	if (!isblack) flag = white;
	if (maps[i][flag[i]] == 0)
		return false;
	for (int w = 1; w<i; ++w)
	{
		if (flag[w] == flag[i])
			return false;//same columns
		if (abs(w - i) == abs(flag[w] - flag[i]))
			return false;
	}
	return true;
}
int blackqueen = 0;
void placeblack(int i)
{
	for (int w = 1; w <= N; ++w)
	{
		if (i == N + 1)
		{
			++blackqueen;
			return;
		}
		black[i] = w;
		if (vaild(i, true) && white[i] != black[i])
			placeblack(i + 1);
	}
}
void placequeen(int i)
{
	for (int w = 1; w <= N; ++w)
	{
		if (i == N+1)
		{
			//白皇后顺序已经确定了
			//确定黑皇后
			placeblack(1);
			ans += blackqueen;
			blackqueen = 0;
			return;
		}
		//先放白皇后
		white[i] = w;
		bool res = vaild(i, false);
		if (res)
			placequeen(i + 1);
	}
}
int main()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			scanf("%d", &maps[i][j]);
		}
	}
	//策略是先放黑皇后 再放白皇后
	placequeen(1);
	printf("%d", ans);
	return 0;
}
