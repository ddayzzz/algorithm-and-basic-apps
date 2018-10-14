#include "stdio.h"
#include <map>
#include <algorithm>
#include <set>
using namespace std;
map<int, int> se;//表示页数->剩余数目的集合
const int MAXN = 1000001;
int P[MAXN] = { 0 };//P[i]表示的是i页的知识点的ID 
int main()
{

	int N;
	scanf("%d", &N);
	
	int mix = N;
	for (int i = 0; i<N; ++i)
	{
		scanf("%d", P + i);
	}
	set<int> aid;
	for (int i = 0; i < N; ++i)
		aid.insert(P[i]);//这个目的是获取知识点的数量 用来去重复 
	int start = 0;//起点 
	int e = 0;//终点 
	//尺取法思路：假设从s开始 到e 可以阅读完 那么从s+1开始的话 至少需要阅读到e+1 或者是e的页面才可以 我的目的是找到最小值 所以我就需要向前来获取能够读的最小的连续页面的长度 
	while (1)
	{
		int num = 0;
		while (e < N && num < aid.size())
		{
			if (se[P[e++]]++ == 0)//如果是一个新的知识点 那么就更新计数num 
			{
				++num;
			}
		}
		if (num < aid.size()) {
			break;//若num还是小于题目的个数 表示e已经到达终点了 所以退出 mix就是最小的值 
		}
		mix = min(mix, e - start);//注意 不是e-start 因为whille退出 就需要不需要+1. 进行到这儿表示已经找到了阅读所有的长度 就是需要更新最小值  ++starts 
		if (--se[P[start++]] == 0)//如果是最后的一个知识点 那么已经进过的题号数量-1 
		{
			--num;
		}
	}
	printf("%d", mix);
	return 0;
}
