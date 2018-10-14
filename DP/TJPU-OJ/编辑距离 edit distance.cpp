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
ԭ��
��s1[1...i]��s2[i...j)]����
1.s1[i]==s2[j]��ôdistance[i][j]�ı༭�������ǰһ���޸�distance[i-1][j-1]
2.s1[i] !=s2[j]
	2.1��s1[1...i-1]ת��Ϊs2[1...j-1] : �滻s1[i]Ϊs2[j]
	2.2��s1[1..i-1]ת��Ϊs2[1...j] �� ��s1[i]ɾ�� ��Ϊǰ���s1[1...i-2]��ƥ������Խ����һ����ƥ���ɾ���Ϳ�������ƥ����
	2.3��s1[1...i]ת��Ϊs2[1...j-1] :��s1[1...i-1]�������s2[j] ͬ��
3.���Ե�s1[i] !=s2[j]��ʱ�� distance[i][j]=min { distance[i-1][j], distance[i][j-1] , distance[i-1][j-1]} +1
�ؾ������Խ����п� ���Խ������ɾ�� �б߲��� �������s1[1] s2[1...j]��s1[1...i] s2[1]
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
		printf("��ԭλ��[%d]%c��ɾ��%c\n",r, s1[r], distance[r][w].data);
		break;
	case INSERT:
		print(r, w-1);
		printf("��ԭλ��[%d]%c������%c\n", r, s1[r], distance[r][w].data);
		break;
	case REPLACE:
		print(r - 1, w - 1);
		printf("��ԭλ��[%d]%c���滻Ϊ%c\n", r, s1[r], distance[r][w].data);
		break;
	}
}
int main()
{
	//�༭���� ����s2�����s1�ı༭����
	scanf("%s", &s1[1]);
	scanf("%s", &s2[1]);
	int row = strlen(&s1[1]);
	int col = strlen(&s2[1]);
	//��ӳ�ʼ�ı�־ distance[0][i]����s1[1]ת��Ϊs2[1...col]��Ҫ����ַ�
	for (int i = 1; i <= col; ++i)
	{
		distance[0][i].data = s2[i];
		distance[0][i].opt = INSERT;
		distance[0][i].value = i;
	}
	//��ӳ�ʼ�ı�־ distance[i][0]����s1[1...n]ת��Ϊs2[1]��Ҫɾ���ַ�
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
	printf("�༭������\n");
	for (int i = 0; i <= row; ++i)
	{
		for (int j = 0; j <= col; ++j)
		{
			printf("%d ", distance[i][j].value);
		}
		printf("\n");
	}
	printf("\"%s\" \"%s\"�ı༭����Ϊ��%d\n����%s�������£�\n", &s1[1], &s2[1], distance[row][col].value, &s1[1]);
	print(row, col);
	system("pause");
	return 0;
}
