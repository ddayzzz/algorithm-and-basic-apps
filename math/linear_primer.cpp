
#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
#include <cstring>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

//快速线性筛选法 欧拉筛法 这个算法之所以快速是因为能够线性的剔除合数
#define MAXN 5000005
#define MAXL 5000005
int PRIME_FLAGS[MAXL];//标记为0表示素数   1为合数
long PRIME[MAXN];
int cnt = 0;
void make_prime()
{
	memset(PRIME_FLAGS, 0, sizeof(PRIME_FLAGS));

	for (int i = 2; i<MAXL; ++i)
	{
		if (!PRIME_FLAGS[i])
		{
			PRIME[cnt++] = i;
		}
		//i是不是合数 质数不重要 反正一开始标记都是0
		for (int j = 0; j < cnt /*&& i *PRIME[j]<=MAXL*/; ++j)//这个是遍历所有的以保存的素数
		{
			if (i*PRIME[j] > MAXL)
				break;//如果两个素数的和超过了最大的值那么退出 可以放到判断条件哪儿
			PRIME_FLAGS[i*PRIME[j]] = 1;//将能够分解为两个质数的整数剔除(最后一次剔除的合数为I*I) 合数只会有从他最小的因子递增的开始才会剔除
			if (i % PRIME[j] == 0)//如果素数==i的大小那么退出循环(其实最大的那个素数就是i本身)
				break;
		}
	}
}
int main()
{
	make_prime();
	for(int i=0;i<cnt;++i)
	{
		if(i % 100 == 0)
		{
			printf("\n");
		}
		printf("%d ", PRIME[i]);
	}
	
	return 0;
}