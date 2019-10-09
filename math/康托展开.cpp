#include "stdio.h"
#include <algorithm>
#include <numeric>
#include <iostream> 
#include <cstdlib>
//http://www.acmerblog.com/cantor-expansion-3647.html
typedef unsigned long long ll;
int seq[100]={1,2,3,4};
int perm[100]; 
ll fact[100]={1,1};
ll fac(ll n)
{
	if(n==1 || n==0)
		return fact[n];
	if(fact[n] > 0)
	{
		return fact[n];
	}
	else
	{
		return fact[n]=n*fac(n-1);
	}
}
int vis[100];
int get_kangtuo(int *p,int n)
{
	int sum=0;
	for(int i=0;i<n;++i)
	{
		int cnt=0;
		for(int j=i+1;j<n;++j)
		{

				if(p[i] > p[j])
					++cnt;
			
		}
		sum+=fac(n-i-1)*cnt;
		//printf("%d ",sum);
	}
	//
	return sum;
}
//
void invKT(int n, int k, int s[]){
	int t,j;
	bool visit[10] = {false}; //需要记录该数是否已在前面出现过
	for(int i=0; i<n; i++){
		t = k/fac(n-i-1);
		for(j=1; j<=n; j++){
			if(!visit[j]){
				if(t == 0) break;
				t--;
			}
		}
		s[i] = j;
		visit[j] = true;
		k %= fac(n-i-1);
	}
}
int main()
{
	/*
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i) scanf("%d",&seq[i]);
	*/
	int p[100]={4,2,1,3};
	int n=4;
	int sum=0;
	printf("%d\n",get_kangtuo(p,n));
	int out[4];
	invKT(4,20,out);
	for(int i=0;i<n;++i)
		printf("%d",out[i]);
	return 0;
} 
