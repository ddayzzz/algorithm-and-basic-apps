#include "stdio.h"
#include <vector>
std::vector<int> res;
int SSS[100000];
const int INF = 100000000;
int main()
{
	int seq;
	scanf("%d", &seq);
	int N; int S;
	for (int t = 0; t<seq; ++t)
	{
		scanf("%d %d", &N, &S);
		int mix = INF;
		for (int j = 0; j < N; ++j)
		{
			int s;
			scanf("%d", &s);
			SSS[j + 1] = SSS[j] + s;//sss[i]表示前i项的和 
		}
		int i = 1; int j = 2;
		while (i <= j && j <= N)
		{
			int sum = SSS[j] - SSS[i];
			if (sum >= S)
			{
				++i;
			}
			else
			{
				++j;
			}
			if (mix > j - i + 1 && sum >=S)
			{
				mix = j - i + 1;
			}
		}
		res.push_back(mix);
	}
	for (int i = 0; i < res.size(); ++i)
	{
		if (res[i] == INF)
		{
			printf("%d\n", 0);
		}
		else
		{
			printf("%d\n", res[i]);
		}
	}
	return 0;
}
