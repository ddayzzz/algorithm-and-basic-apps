//贪心法 ：找钱的问题
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
	printf("请输入需要支付的价格：");
	scanf("%d",&value);
	printf("请输入各个面额的钞票的剩余数量：");
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
	printf("支付%d元需要：\n",v);
	for(int i=1;i<=6;++i)
	{
		if(used[i])
		{
			printf("面值：%3d，%3d张\n",memony[i],used[i]);
		}
	}
	printf("共： %3d张",usedcnt);
	return 0;
}
