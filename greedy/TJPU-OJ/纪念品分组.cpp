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
	std::sort(value+1, value + n+1,std::greater<int>());//按照降序排列 
	for (int i = 1; i <= n; ++i)
	{
		if (leftover[value[i]] > 0)
		{
			--leftover[value[i]];//当前访问的位置-1 
			int curr = value[i];//记下当前的大小 
			for (int j = n; j >=i; --j)//注意 这给从最小的位置开始加和 最大的值+最小的数字他们就可以分为数量最多的组 
			{
				if (curr + value[j] <= maxw && leftover[value[j]] >0)
				{
					--leftover[value[j]];
					curr = curr + value[j];//加上这个值 
				}
			}
			++group;
			
		}
	}
	printf("%d", group);
	return 0;
}

