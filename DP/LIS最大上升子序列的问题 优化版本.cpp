
#include "stdio.h"
#include <algorithm>
#include "string.h" 

//这个是有较低复杂度的最大上升子序列的问题 
//dp[i] 表示长度为i+1的上升子序列末尾元素的最小值 最小的元素拥有的成为上升的子序列的优势 
const int N = 11;

int a[N] = { -5,-3,0,-9,-7,-18,-17,3,6,9,10 };
const int INF = 655;
int dp[N];

int main()
{
	//memset(dp, INF, N);//memset适用于ASCII值 在这里不行
	for (int i = 0; i < N; ++i)
	{
		dp[i] = INF;
	}
	int n = N;
	for (int i = 0; i<n; ++i)
	{
		int lower = 0;
		int upper = n;
		while (lower <= upper)
		{
			int mid = (lower + upper) / 2;
			if (dp[mid] < a[i])
				lower = mid + 1;
			else if (dp[mid] > a[i])
				upper = mid - 1;
			else { lower = mid; upper = mid + 1; }
		}
		dp[lower] = a[i];//找到边界 这里也使用lower_bound  同下方的解释 总值dp[i]保存的就是当遍历到i的位置 能保持增长的末尾元素的最小值 
	}
	int *r = std::lower_bound(dp, dp + n, INF);
	printf("%d\n", r - dp);//lower_bound寻找第一个可以插入的INF的位置 返回的位置-1就是最后一个递增的元素的位置 因为整个dp数组是递增的 然后减去起始位置就是总个数
	return 0;
}
