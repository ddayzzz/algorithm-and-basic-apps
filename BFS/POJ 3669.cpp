#include "stdio.h"
#include <iostream> 
#include <iterator>
#include <queue>
const int MAXM = 50000; //搞错范围了 浪费了很多的时间 
const int MAXN = 400;
const int  INF = 100000;

using namespace std;

int dir[4][2] = { { 0,1 },{ -1,0 },{ 0,-1 },{ 1,0 } };

int map[MAXN][MAXN];
int step[MAXN][MAXN];
int X[MAXM];
int Y[MAXM];
int T[MAXM];
typedef pair<int, int> P;
int N;
int bfs(int x, int y)
{
	if (map[x][y] == 0)
		return -1;
	queue<P> que;
	que.push(P(x, y));
	step[x][y] = 0;
	while (!que.empty())
	{
		int cx, cy;
		P  p = que.front();
		cx = p.first;
		cy = p.second;
		que.pop();
		if (map[cx][cy] == INF)
		{
			return step[cx][cy];
		}
		for (int i = 0; i<4; ++i)
		{
			int dx = cx + dir[i][0];
			int dy = cy + dir[i][1];
			if (dx >= 0 && dy >= 0 && step[dx][dy] == INF && step[cx][cy]+1 < map[dx][dy])
			{
				step[dx][dy] = step[cx][cy] + 1;
				que.push(P(dx, dy));
			}
		}
	}
	return -1;
}
void solve()
{
	/*
	//首先模拟轰炸
	for (int i = 0; i<MAXN; ++i)
	{
		for (int j = 0; j<MAXN; ++j)
		{
			map[i][j] = INF;
			step[i][j] = INF;
		}
	}
	//开始模拟
	for (int i = 0; i<N; ++i)
	{
		map[X[i]][Y[i]] = min(map[X[i]][Y[i]], T[i]);
		for (int j = 0; j<4; ++j)
		{
			int dx = X[i] + dir[j][0];
			int dy = Y[i] + dir[j][1];
			if (dx >= 0 && dy >= 0)
			{
				map[dx][dy] = min(map[dx][dy], T[i]);
			}
		}
	}
	*/
	//初始化地图
	for (int i = 0; i < MAXN; i++)
		fill(map[i], map[i] + MAXN, INF);
	//模拟轰炸场景
	for (int i = 0; i < N; i++) {
		map[X[i]][Y[i]] = min(map[X[i]][Y[i]], T[i]);
		for (int j = 0; j < 4; j++) {
			int nx = X[i] + dir[j][0], ny = Y[i] +dir[j][1];
			if (0 <= nx && 0 <= ny)
				map[nx][ny] = min(map[nx][ny], T[i]);
		}
	}
	//初始化地图最小步数
	for (int i = 0; i < MAXN; i++)
		fill(step[i], step[i] + MAXN, INF);
	//宽度优先搜索
	
	int ans = bfs(0, 0);
	printf("%d\n", ans);

}
int main(int argc, char const *argv[])
{
	scanf("%d", &N);
	for (int i = 0; i<N; ++i)
	{
		scanf("%d %d %d", &X[i], &Y[i], &T[i]);
	}
	solve();
	return 0;
}
