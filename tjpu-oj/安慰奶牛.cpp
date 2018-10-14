#include "stdio.h"
#include  <iostream>
#include <algorithm>
#include <vector> 
#include <queue>
int talktime[100000];

struct edge
{
	int v;
	int w;
	int weight;
	edge(int _v, int _w, int _weg) :v(_v), w(_w), weight(_weg) {
	}
	edge() {}
};
int getend(int v, std::vector<int> &parent)
{
	while(parent[v]!=v)
	{
		v = parent[v];
	}
	return v;
}
int main()
{
	int N;
	int P;
	int ans = 500000;
	std::cin >> N >> P;
	std::vector<edge> vec(P);
	std::vector<int> parent(N);
	for (int i = 0; i < N; ++i)
	{
		scanf("%d", &talktime[i]);
		if (talktime[i] < ans)
			ans = talktime[i];
		parent[i]=i;
	}
	for (int i = 0; i<P; ++i)
	{
		//总时间 两头牛的交谈时间+边长度
		int v, w, weg;
		scanf("%d%*c%d%*c%d", &v, &w, &weg);
		
		vec[i].v = v - 1;
		vec[i].w = w - 1;
		vec[i].weight = (weg << 1 )+ talktime[v - 1] + talktime[w - 1];

	}
	std::sort(vec.begin(), vec.end(), [](const edge &l, const edge &r) {return l.weight < r.weight; }
	);
	//图已经准备好了 现在可以kruskal最小生成树 从1开始进行遍历
	int tot = 0;
	for (int i = 0; i<P; ++i)
	{
		int m = getend(vec[i].v, parent);
		int n = getend(vec[i].w, parent);
		if (m != n)
		{
			tot++;
			parent[m] = n;
			ans = ans + vec[i].weight;
		}
		//if (tot == N - 1)
		//	break;
	}
	printf("%d", ans);
	return 0;
}
