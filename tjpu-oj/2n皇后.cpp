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
	//i��ʾ����i�� flag[i]��ʾ������ ��Ҫ���֮ǰ�����Ƿ��г�ͻ 
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
			//�׻ʺ�˳���Ѿ�ȷ����
			//ȷ���ڻʺ�
			placeblack(1);
			ans += blackqueen;
			blackqueen = 0;
			return;
		}
		//�ȷŰ׻ʺ�
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
	//�������ȷźڻʺ� �ٷŰ׻ʺ�
	placequeen(1);
	printf("%d", ans);
	return 0;
}
