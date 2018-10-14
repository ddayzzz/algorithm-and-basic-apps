#include <cstdio>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> P;

const int MAX_M = 50000;
const int MAX_N = 400 + 1;
const int INF = 100000000;

//输入
int M;
int X[MAX_M], Y[MAX_M], T[MAX_M];

int maze[MAX_N][MAX_N];                        //保存地图
int d[MAX_N][MAX_N];                        //保存最短步数

											//4个方向
const int dx[4] = { -1, 1, 0, 0 };
const int dy[4] = { 0, 0, -1, 1 };

int bfs() {
	//一开始就被炸
	if (maze[0][0] == 0) return -1;

	queue<P> que;
	que.push(P(0, 0));
	d[0][0] = 0;
	while (!que.empty()) {
		P p = que.front();
		que.pop();
		//已到达安全位置
		int x = p.first, y = p.second;
		if (maze[x][y] == INF) return d[x][y];
		//4个方向走
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			//判断是否可移动，是否访问过，以及下一个时刻是否安全
			if (0 <= nx && 0 <= ny && d[nx][ny] == INF && d[x][y] + 1 < maze[nx][ny]) {
				que.push(P(nx, ny));
				d[nx][ny] = d[x][y] + 1;
			}
		}
	}
	return -1;
}

void solve() {
	//初始化地图
	for (int i = 0; i < MAX_N; i++)
		fill(maze[i], maze[i] + MAX_N, INF);
	//模拟轰炸场景
	for (int i = 0; i < M; i++) {
		maze[X[i]][Y[i]] = min(maze[X[i]][Y[i]], T[i]);
		for (int j = 0; j < 4; j++) {
			int nx = X[i] + dx[j], ny = Y[i] + dy[j];
			if (0 <= nx && 0 <= ny)
				maze[nx][ny] = min(maze[nx][ny], T[i]);
		}
	}
	//初始化地图最小步数
	for (int i = 0; i < MAX_N; i++)
		fill(d[i], d[i] + MAX_N, INF);
	//宽度优先搜索
	int ans = bfs();
	printf("%d\n", ans);
}

int main(int argc, char const *argv[]) {

	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &X[i], &Y[i], &T[i]);
	}
	solve();
	return 0;
}
