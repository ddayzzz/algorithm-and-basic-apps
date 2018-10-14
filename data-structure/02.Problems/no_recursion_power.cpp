#include "stdio.h"
typedef unsigned long long ll;
ll power(ll x, ll y)
{
	ll res = 1;
	while (y > 0)
	{
		if (y & 1ull)//���λ�Ƿ���λ 
		{
			res = res * x;//��һ��x 
		}
		x = x*x;//ÿ��ǰ�ƽ���Ϊ ����Ҫ��һ��x 
		y = y >> 1;//����λ 
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

	printf("�ǵݹ鷽ʽ : %lld\n", h);
	ll p = power_recursion(i, j);
	printf("�ݹ鷽ʽ : %lld\n", p);
	return 0;
}