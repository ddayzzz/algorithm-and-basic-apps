//负数权的Bellman-Ford算法 
#include "stdio.h"
#include "string.h"
#define MAXF 5
#define MAXN 501
#define MAXM 2501
#define MAXW 201
#define INF 10000
int F;
int N;
int M;
int W; 
int graph[MAXN][MAXN];
bool res[MAXF];
//算法的任务是需要找到一个环，没有指定起点，所以用floyd算法查找是否存在一个环
bool floyd()
{
	for(int k=1;k<=N;++k)
	{
		for(int i=1;i<=N;++i)
		{
			for(int j=1;j<=N;++j)
			{
				if(graph[i][j] > graph[i][k]+graph[k][j])
					graph[i][j]=graph[i][k]+graph[k][j];
			}
		}
	 }
	 for(int p=1;p<=N;++p)
	 {
	 	if(graph[p][p]<0)
	 		return true;
	 }
	 return false;
} 
int main()
{
	scanf("%d",&F);
	for(int i=0;i<F;++i)
	{
		for(int u=0;u<MAXN;++u)
			for(int j=0;j<MAXN;++j)
				graph[u][j]=INF;
		scanf("%d %d %d",&N,&M,&W);
		for(int u=0;u<N;++u)
			for(int j=0;j<N;++j)
				graph[u][j]=INF;
		for(int vm=0;vm<M;++vm)
		{
			int s,e,t;
			scanf("%d %d %d",&s,&e,&t);
			if(t < graph[s][e]) //有重边 fix from http://blog.csdn.net/yslcl12345/article/details/50573269 
			{
				graph[s][e]=t;
				graph[e][s]=t;//注意是双向的边 
			}
		}
		for(int vw=0;vw <W;++vw)
		{
			int s,e,t;
			scanf("%d %d %d",&s,&e,&t);
			graph[s][e]=-t;//这个是虫洞的边 我认为进一次虫洞 时间就减少t 对应的，就需要变成相反数 
		}
		res[i]=floyd();
	}
	for(int i=0;i<F;++i)
	{
		if(res[i]==false)
			printf("NO\n");
		else
			printf("YES\n");
	}
	return 0;
}
