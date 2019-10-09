#include "stdio.h"
#include <algorithm>
int tree[20000];
int main()
{
	const int N=3;
	int n=N;
	int L[N]={8,5,8};
	int ans=0;
	//std::sort(L,L+N);
	while(n>1)
	{
		int smallest=0;
		int smaller=1;
		if(L[smallest] > L[smaller]) std::swap(smallest,smaller);//交换次小和最小的下标
		for(int i=2;i<n;++i)
		{
			if(L[i] < L[smallest])
			{
				smaller=smallest;
				smallest=i;
			}
			else
			{
				if(L[i] <L[smaller])
				{
					smaller=i;	
				} 
			}
		}
		int t=L[smaller]+L[smallest];
		ans+=t;
		if(smallest==n-1) std::swap(smaller,smallest);//如果这个是边界 那么需要与次最小交换写入位置 否则在下次循环中就不会被访问了 次最小和最小已经被淘汰了 
		L[smallest]=t;
		L[smaller]=L[n-1];
		n--;
	}
	printf("%d",ans);
	return 0;
}
