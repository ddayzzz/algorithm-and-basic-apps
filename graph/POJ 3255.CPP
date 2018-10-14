#include "stdio.h"
#include <queue>
#include <vector>
#include <iostream>
#include <functional>
#include <utility>
using namespace std;
const int N = 5001;

int graph[N][N] = { 0 };
int minest[N];//��̵�·�� 
int miner[N];//����̵�·�� 
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
		//�����·��������v0->v����̾���+v->w�ľ��� ������v0->v�Ĵζ̾���+v->w�ľ���
		if (miner[v] < p.first)
			continue;
		for (int w = 1; w <= n; ++w)
		{
			if (graph[v][w] != INF && graph[v][w] != 0)
			{
				int weight_vw = graph[v][w];
				int est = weight_vw + p.first;/*��Ҫ���ϴ�v0��v�Ĵ�С����ȷ����v0->v minest����С mner������ ��vλ�ó���*/
				if (minest[w] >est)//һֱ��̵�·��̫�� est < minest[w]
				{
					swap(minest[w], est);//��Ҫ���� 
					que.push(P(minest[w], w));//������С
				}
				if (miner[w] > est/*�������̱�ԭ������̻��� �Ǿ���Ҫ����*/ && minest[w] < est/*֮ǰû��ִ�������if�Ļ� �ͱ�������minset[w] < est(v0->v->w)<miner[w]�ľ��� �ſ��Խ���*/)
				{
					//�ζ�·���ȵ������ľ��뻹��
					miner[w] = est;
					que.push(P(miner[w], w));
				}
			}
		}
	}
	printf("%d", minest[n]);
	return 0;
}