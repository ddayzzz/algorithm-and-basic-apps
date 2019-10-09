#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <algorithm>
#define INF 65535
double ropes[10001];

int n;//ropes 
int k;//need to be cut
bool isokay(double x)
{
	int num=0;
	for(int i=0;i<n;++i)
	{
		num=num+ (int)ropes[i] / x;
	}
	return num >=k;
}
int main()
{
	double l=0.0;
	double u=INF;
	scanf("%d %d",&n,&k);
	for(int i=0;i<n;++i)
		scanf("%lf",&ropes[i]);
	for(int i=1;i<100;++i)
	{
		double mid=(l+u)/2;
		if(isokay(mid)) l=mid;
		else u=mid;
	}
	printf("%.2lf",floor(u*100) / 100);
	return 0;
}
