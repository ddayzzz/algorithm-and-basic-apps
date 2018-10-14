#include <string>
#include <iostream>
#include <vector>
//思路来源 http://blog.csdn.net/liukx940818/article/details/44204411
//不知道怎么回事 大量的数据无法通过 
using namespace std;
char c[80002];
int main()
{
	//只有向内反向才可以
	int n;
	scanf("%d", &n);
	scanf("%s", &c[1]);

	int l = 1;
	int u = n;
	int ans=0;
	int sigle=0;
	while (l < u)
	{
		int left;
		int f = u;
		while (f >= l && c[f] != c[l])--f;
		if (f == l)
		{
			
			++sigle;
			//如果是找到了一个只有一个的就需要将这个点移到终点 只有奇数才允许
			if (n % 2 == 0 || sigle >= 2)
			{
				ans = -1;
				break;
			}
			else
			{
				ans += (n / 2 + 1) - l;
			}
			++l;
			continue;
		}
		//进行交换
		if (f < u)
		{
			int cnt = 0;
			int cha = f + 1;
			while (cha <= u)
			{
				char t = c[cha];
				c[cha] = c[f];
				c[f] = t;
				++cnt;
				f = cha;
				cha = f + 1;
			}
			ans += cnt;
		}
		--u;
		++l;
	}
	if (ans == -1)
	{
		printf("Impossible");
	}
	else
	{
		printf("%d", ans);
	}
	
	return 0;
}
