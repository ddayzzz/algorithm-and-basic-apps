//̰�ķ� ����Ǯ������
#include "stdio.h"
int memony[]={0,1,5,10,50,100,500};
int leftover[7]={0};
int used[7]={0};
int min(int a,int b)
{
	return a<b?a:b;
}
int main()
{
	int value;
	int v=value;
	printf("��������Ҫ֧���ļ۸�");
	scanf("%d",&value);
	printf("������������ĳ�Ʊ��ʣ��������");
	for(int i=1;i<=6;++i)
		scanf("%d",&leftover[i]);
	int usedcnt=0;
	for(int i=6;i>=1;--i)
	{
		int t=min(value / memony[i],leftover[i]);
		used[i]=t;
		value-=memony[i]*t;
		usedcnt+=t;
	}
	printf("֧��%dԪ��Ҫ��\n",v);
	for(int i=1;i<=6;++i)
	{
		if(used[i])
		{
			printf("��ֵ��%3d��%3d��\n",memony[i],used[i]);
		}
	}
	printf("���� %3d��",usedcnt);
	return 0;
}
