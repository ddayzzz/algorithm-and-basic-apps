#include "stdio.h"
#include <queue>
#include <vector>
#include <iostream>
#include <functional>
#include <utility>
using namespace std;
const int N = 5001;

int graph[N][N] = { 0 };
int minest[N];//最短的路径 
int miner[N];//次最短的路径 
int main()
{
	typedef std::pair<int, int> P;
	int n, r;
	scanf("%d %d", &n, &r);
	for (int i = 0; i<r; ++i)
	{
		int x, y, w;
		scanf("%d %d %d", &x, &y, &w);
		graph[x][y] = w;
		graph[y][x] = w;
	}
	int INF = 65535;
	fill(minest, minest + N, INF);
	fill(miner, miner + N, INF);
	minest[1] = 0;
	std::priority_queue<P, std::vector<P>, greater<P> > que;
	que.push(P(0, 1));
	while (!que.empty())
	{
		P p = que.top();
		que.pop();
		int v = p.second;
		//次最短路径可能是v0->v的最短距离+v->w的距离 或者是v0->v的次短距离+v->w的距离
		if (miner[v] < p.first)
			continue;
		for (int w = 1; w <= n; ++w)
		{
			if (graph[v][w] != INF && graph[v][w] != 0)
			{
				int weight_vw = graph[v][w];
				int est = weight_vw + p.first;/*需要加上从v0到v的大小可以确定从v0->v minest是最小 mner是最大的 从v位置出发*/
				if (minest[w] >est)//一直最短的路径太大 est < minest[w]
				{
					swap(minest[w], est);//需要交换 
					que.push(P(minest[w], w));//更新最小
				}
				if (miner[w] > est/*如果次最短比原来的最短还大 那就需要更新*/ && minest[w] < est/*之前没有执行上面的if的话 就必须满足minset[w] < est(v0->v->w)<miner[w]的距离 才可以交换*/)
				{
					//次短路径比到这个点的距离还大
					miner[w] = est;
					que.push(P(miner[w], w));
				}
			}
		}
	}
	printf("%d", minest[n]);
	return 0;
}
