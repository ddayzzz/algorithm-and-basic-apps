#include "stdio.h"
#include <algorithm>
using namespace std;
const int MAXN = 105;
double R[MAXN][MAXN] = { 0.0 };//保存从i到j的比例
double C[MAXN][MAXN] = { 0.0 };//保存手续费
double gra[1000];
int N;//货币类型总数
int M;//兑换点数目
int S;//手上钱的类型
double V;//手上钱实际金额
//thinking from http://blog.csdn.net/yslcl12345/article/details/50574213
bool floyd()
{
	double d[MAXN];
	int i, j, k;
	for (i = 1; i <= N; i++) d[i] = gra[i];
	//d用来保存从兑换类型到i这个货币总数的其实余额
	for (k = 1; k<=N; ++k)
	{
		for (i = 1; i<=N; ++i)
		{
			for (j = 1; j<=N; ++j)
			{
				if ((gra[i] - C[i][j])*R[i][j] > gra[j]) 
					gra[j] = (gra[i] - C[i][j])*R[i][j];//如果从i兑换得到的钱然后兑换位j的钱要比直接从某一个兑换点到j的兑换的价格要高 那么就需要替换
			}
		}

	}
	for (i = 1; i<=N; ++i)
	{
		if (d[i]<gra[i])return true;//如果发现得到的其实的金额要高，那么是YES
	}
	return false;

}
int main()
{
	scanf("%d %d %d %lf", &N, &M, &S, &V);
	for (int i = 0; i<M; ++i)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		scanf("%lf", &R[a][b]);
		scanf("%lf", &C[a][b]);
		scanf("%lf", &R[b][a]);
		scanf("%lf", &C[b][a]);
	}
	gra[S] = V;
	floyd();//第一步：更新能兑换得到的钱的列表
	//这么做的目的是：有可能有些增加量太小，如果第二次增加的比第一还多，那么存在n次，可以是第n次的转换>本金。
	if (floyd())//第二部：Floyd中的三重循环不会执行，然后需要判断是否能搞继续递增。也就是存在一个正环。
		printf("YES\n");
	else
		printf("NO\n");
	return 0;
}

