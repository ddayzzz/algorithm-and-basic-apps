#include "stdio.h"
typedef unsigned long long ll;
ll power(ll x, ll y)
{
	ll res = 1;
	while (y > 0)
	{
		if (y & 1ull)//最低位是否置位 
		{
			res = res * x;//乘一个x 
		}
		x = x*x;//每向前推进以为 就需要乘一个x 
		y = y >> 1;//右移位 
	}
	return res;
}
ll power_recursion(ll x, ll y)
{
	//
	if (y == 0)
		return 1;
	ll res = power_recursion(x*x, y / 2);
	if (y & 1ull) res = res*x;
	return res;
}
int main()
{
	ll h;
	int i, j;
	scanf("%d %d", &i, &j);
	h = power(i, j);

	printf("非递归方式 : %lld\n", h);
	ll p = power_recursion(i, j);
	printf("递归方式 : %lld\n", p);
	return 0;
}