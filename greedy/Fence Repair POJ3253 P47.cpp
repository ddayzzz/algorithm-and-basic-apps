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
		if(L[smallest] > L[smaller]) std::swap(smallest,smaller);//������С����С���±�
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
		if(smallest==n-1) std::swap(smaller,smallest);//�������Ǳ߽� ��ô��Ҫ�����С����д��λ�� �������´�ѭ���оͲ��ᱻ������ ����С����С�Ѿ�����̭�� 
		L[smallest]=t;
		L[smaller]=L[n-1];
		n--;
	}
	printf("%d",ans);
	return 0;
}
