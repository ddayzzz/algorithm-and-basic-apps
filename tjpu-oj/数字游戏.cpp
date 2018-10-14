#include "stdio.h"
typedef long long ll;
int main()
{
	int N,K,T;
	scanf("%d %d %d",&N,&K,&T);
	ll beg,end,delta,res=1;
	ll rep=1;//表示存放前一次报数的ID 
	for(int i=0;i<T-1;++i)//默认已经报了第一次 所以循环少一次 
	{
		beg=1+i*N;
		end=beg + N-1;
		delta=((beg+end)*N / 2) % K;//这个坑爹 因为期间会有同学可能超出 所以需要 %k 由于mod运算具有可加性 所以就最后%k也可以 
		res=res + (rep + delta) % K;//更新上一次 
		rep=(rep + delta) % K;
	}
	printf("%lld",res);
	return 0;
} 
