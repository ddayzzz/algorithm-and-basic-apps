#include "stdio.h" 
#include <algorithm>
//book P45
int main()
{
	int N=6;
	int R=10;
	int X[]={1,7,15,20,30,50};
	std::sort(X,X+N);
	int pos=0;
	int ans=0;
	while(pos < N)
	{
		int s=X[pos++];//��ʼ���λ�� 
		while(pos < N && X[pos] <=R+ s) ++pos;
		int p=X[pos-1];//p������Ҫ���ϱ�ǵĵ� �����һ���ܱ�ԭpos��R��Χ�ڸ��ǵĵ�
		while(pos < N && X[pos] <=p+R) ++pos;
		++ans; 
	}
	printf("%d",ans);
	return 0;
}