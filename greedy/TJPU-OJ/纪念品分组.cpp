#include "stdio.h"
#include <algorithm>
#include <functional>
#define MAXN 40001
int arr[MAXN][3];
int value[MAXN] = { 0 };
int leftover[201] = { 0 };
int main()
{
	int n;
	int maxw;
	scanf("%d", &maxw);
	scanf("%d", &n);
	int group = 0;
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &value[i]);
		leftover[value[i]]++;
	}
	std::sort(value+1, value + n+1,std::greater<int>());//���ս������� 
	for (int i = 1; i <= n; ++i)
	{
		if (leftover[value[i]] > 0)
		{
			--leftover[value[i]];//��ǰ���ʵ�λ��-1 
			int curr = value[i];//���µ�ǰ�Ĵ�С 
			for (int j = n; j >=i; --j)//ע�� �������С��λ�ÿ�ʼ�Ӻ� ����ֵ+��С���������ǾͿ��Է�Ϊ���������� 
			{
				if (curr + value[j] <= maxw && leftover[value[j]] >0)
				{
					--leftover[value[j]];
					curr = curr + value[j];//�������ֵ 
				}
			}
			++group;
			
		}
	}
	printf("%d", group);
	return 0;
}

