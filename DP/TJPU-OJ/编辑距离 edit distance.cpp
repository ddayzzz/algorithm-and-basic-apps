#include "stdio.h"
#include "string.h"
#include <iostream>
#define REPLACE -1
#define SAME 0
#define DELETE 1
#define INSERT 2
struct option
{
	int value;
	int opt;
	char data;
};
char s1[51];
char s2[51];
option distance[51][51] = { 0 };
int min(int a, int b) {
	return a<b ? a : b;
}
/*
原理：
当s1[1...i]和s2[i...j)]假设
1.s1[i]==s2[j]那么distance[i][j]的编辑距离就是前一次修改distance[i-1][j-1]
2.s1[i] !=s2[j]
	2.1将s1[1...i-1]转换为s2[1...j-1] : 替换s1[i]为s2[j]
	2.2将s1[1..i-1]转换为s2[1...j] ： 将s1[i]删除 因为前面的s1[1...i-2]是匹配的所以将最后一个不匹配的删除就可以整个匹配了
	2.3将s1[1...i]转换为s2[1...j-1] :在s1[1...i-1]后面添加s2[j] 同理
3.所以当s1[i] !=s2[j]的时候 distance[i][j]=min { distance[i-1][j], distance[i][j-1] , distance[i-1][j-1]} +1
沿矩阵主对角线切开 主对角左边是删除 有边插入 可以类比s1[1] s2[1...j]和s1[1...i] s2[1]
*/
void print(int r, int w)
{
	if (r == 0 && w == 0)
		return;
	switch (distance[r][w].opt)
	{
	case SAME:
		print(r - 1, w - 1);
		break;
	case DELETE:
		print(r-1, w);
		printf("在原位置[%d]%c：删除%c\n",r, s1[r], distance[r][w].data);
		break;
	case INSERT:
		print(r, w-1);
		printf("在原位置[%d]%c：插入%c\n", r, s1[r], distance[r][w].data);
		break;
	case REPLACE:
		print(r - 1, w - 1);
		printf("在原位置[%d]%c：替换为%c\n", r, s1[r], distance[r][w].data);
		break;
	}
}
int main()
{
	//编辑距离 返回s2相对于s1的编辑距离
	scanf("%s", &s1[1]);
	scanf("%s", &s2[1]);
	int row = strlen(&s1[1]);
	int col = strlen(&s2[1]);
	//添加初始的标志 distance[0][i]代表s1[1]转换为s2[1...col]需要添加字符
	for (int i = 1; i <= col; ++i)
	{
		distance[0][i].data = s2[i];
		distance[0][i].opt = INSERT;
		distance[0][i].value = i;
	}
	//添加初始的标志 distance[i][0]代表s1[1...n]转换为s2[1]需要删除字符
	for (int i = 1; i <= row; ++i)
	{
		distance[i][0].data = s1[i];
		distance[i][0].opt = DELETE;
		distance[i][0].value = i;
	}
	for (int i = 1; i <= row; ++i)
	{
		for (int j = 1; j <= col; ++j)
		{
			if (s1[i] == s2[j])
			{
				distance[i][j].value = distance[i - 1][j - 1].value;
				distance[i][j].opt = SAME;
			}
			else
			{
				int tl = distance[i - 1][j - 1].value;
				int l = distance[i][j-1].value;
				int t = distance[i-1][j].value;
				int m = min(min(tl, l), t);
				if (m == tl)
				{
					distance[i][j].data = s2[j];
					distance[i][j].opt = REPLACE;
				}
				else
				{
					if (m == l)
					{
						distance[i][j].data = s2[j];
						distance[i][j].opt = INSERT;
					}
					else
					{
						distance[i][j].data = s1[i];
						distance[i][j].opt = DELETE;
					}
				}
				distance[i][j].value = m + 1;
			}
		}
	}
	printf("编辑距离表格：\n");
	for (int i = 0; i <= row; ++i)
	{
		for (int j = 0; j <= col; ++j)
		{
			printf("%d ", distance[i][j].value);
		}
		printf("\n");
	}
	printf("\"%s\" \"%s\"的编辑距离为：%d\n对于%s操作如下：\n", &s1[1], &s2[1], distance[row][col].value, &s1[1]);
	print(row, col);
	system("pause");
	return 0;
}
