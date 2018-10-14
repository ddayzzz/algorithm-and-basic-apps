#include <cstdio>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> P;

const int MAX_M = 50000;
const int MAX_N = 400 + 1;
const int INF = 100000000;

//����
int M;
int X[MAX_M], Y[MAX_M], T[MAX_M];

int maze[MAX_N][MAX_N];                        //�����ͼ
int d[MAX_N][MAX_N];                        //������̲���

											//4������
const int dx[4] = { -1, 1, 0, 0 };
const int dy[4] = { 0, 0, -1, 1 };

int bfs() {
	//һ��ʼ�ͱ�ը
	if (maze[0][0] == 0) return -1;

	queue<P> que;
	que.push(P(0, 0));
	d[0][0] = 0;
	while (!que.empty()) {
		P p = que.front();
		que.pop();
		//�ѵ��ﰲȫλ��
		int x = p.first, y = p.second;
		if (maze[x][y] == INF) return d[x][y];
		//4��������
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			//�ж��Ƿ���ƶ����Ƿ���ʹ����Լ���һ��ʱ���Ƿ�ȫ
			if (0 <= nx && 0 <= ny && d[nx][ny] == INF && d[x][y] + 1 < maze[nx][ny]) {
				que.push(P(nx, ny));
				d[nx][ny] = d[x][y] + 1;
			}
		}
	}
	return -1;
}

void solve() {
	//��ʼ����ͼ
	for (int i = 0; i < MAX_N; i++)
		fill(maze[i], maze[i] + MAX_N, INF);
	//ģ���ը����
	for (int i = 0; i < M; i++) {
		maze[X[i]][Y[i]] = min(maze[X[i]][Y[i]], T[i]);
		for (int j = 0; j < 4; j++) {
			int nx = X[i] + dx[j], ny = Y[i] + dy[j];
			if (0 <= nx && 0 <= ny)
				maze[nx][ny] = min(maze[nx][ny], T[i]);
		}
	}
	//��ʼ����ͼ��С����
	for (int i = 0; i < MAX_N; i++)
		fill(d[i], d[i] + MAX_N, INF);
	//�����������
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
