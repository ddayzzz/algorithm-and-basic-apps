#include "stdio.h"
typedef long long ll;
int main()
{
	int N,K,T;
	scanf("%d %d %d",&N,&K,&T);
	ll beg,end,delta,res=1;
	ll rep=1;//��ʾ���ǰһ�α�����ID 
	for(int i=0;i<T-1;++i)//Ĭ���Ѿ����˵�һ�� ����ѭ����һ�� 
	{
		beg=1+i*N;
		end=beg + N-1;
		delta=((beg+end)*N / 2) % K;//����ӵ� ��Ϊ�ڼ����ͬѧ���ܳ��� ������Ҫ %k ����mod������пɼ��� ���Ծ����%kҲ���� 
		res=res + (rep + delta) % K;//������һ�� 
		rep=(rep + delta) % K;
	}
	printf("%lld",res);
	return 0;
} 
