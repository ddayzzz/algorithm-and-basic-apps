#include "stdio.h"
typedef unsigned long long ll;
ll power(ll x,ll n)
{
	ll res=1;
	while(n > 0)
	{
		if(n & 1ull)
		{
			res=res * x;
		}
		x=x*x;
		n=n>>1;
	}
	return res;
} 
int main()
{
	ll h=power(5,75);
	printf("%d",h);
	return 0;
}
