#include "stdio.h"
#include "string.h"
const int N = 50001;
const int M = 150003;
int animals[M];//��Ϊ���� ��һ��ΪA �ڶ���ΪB ������ΪC
int parents[M] = { 0 };//���游�ڵ� ��ʼ��Ϊ0
int height[M] = { 0 };//����Ǳ��������ĸ߶� 
int find(int j)
{
	if (parents[j] == 0)
	{
		return j;
	}
	else
	{
		return parents[j] = find(parents[j]);
	}
}
void unite(int i, int j)
{
	int f1 = find(i);
	int f2 = find(j);
	if (f1 == f2)
		return;
	if (height[f1] > height[f2])
	{
		//��С�����ϲ�
		parents[f2] = f1;
	}
	else
	{
		if (height[f1] == height[f2])
			height[f2]++;
		parents[f1] = f2;
	}
}
bool same(int i, int j)
{
	int f1 = find(i);
	int f2 = find(j);
	return f1 == f2;
}
int main()
{

	int x, y, d;
	int n, k;
	scanf("%d %d", &n, &k);
	int ans = 0;
	for (int i = 0; i<k; ++i)
	{
		scanf("%d %d %d", &d, &x, &y);
		if (x <= 0 || x >n || y <= 0 || y >n)
		{
			++ans;
			continue;
		}
		if (d == 1)
		{
			//ͬ��
			if (same(x, y + n) || same(x, y + n * 2))
			{
				//false
				++ans;
			}
			else
			{
				unite(x, y);
				unite(x + n, y + n);
				unite(x + 2 * n, y + 2 * n);
			}
		}
		else
		{
			if (d == 2)
			{
				//x eat y 
				//  x eat x         b eat a                c eat b(�м���������ʡ�� Ϊʲô?)    a eat c
				if (same(x, y) || same(x+n,y) || same(x+2*n,y+n) || same(x, y + 2 * n))
					++ans;
				else
				{
					unite(x, y + n);
					unite(x + n, y + 2 * n);
					unite(x + 2 * n, y);
				}
			}
		}

	}
	printf("%d", ans);
	return 0;
}