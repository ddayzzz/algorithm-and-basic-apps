#include <cstdio>
#include <vector>
#include <algorithm>
enum Node {
	NO = 0, BLOCK, START, GOAL
};
const int MAX_W = 20;
const int MAX_H = 20;
int map[MAX_W][MAX_H];
//int flag[MAX_W][MAX_H];
int res[100] = { 0 };
int w, h;
const int limit = 10;
int minopt = limit + 1;
int dir[4][2] = { { 0,-1 },{ -1,0 },{ 0,1 },{ 1,0 } };
bool dfs(int depth, int x, int y)
{
	if (depth >limit)
	{
		//fail the game
		return false;
	}
	int dx, dy;
	for (int i = 0; i<4; ++i)
	{
		dx = x + dir[i][0];
		dy = y + dir[i][1];
		if (dx >= 0 && dx <h && dy >= 0 && dy <w && map[dx][dy] !=BLOCK)
		{
			//合法的点 那么需要项这个方向递增移动到下一个组块之前 然后进行dfs
			int nx = dx, ny = dy;
			for (; nx >= 0 && nx <h && ny >= 0 && ny <w && (map[nx][ny] == NO || map[nx][ny]==START); nx = nx + dir[i][0], ny = ny + dir[i][1])
				;
			
			if (nx <0 || nx >= h || ny <0 || ny >= w)
				continue;
			//if (flag[nx][ny] == 1)//这个根本没什么用 因为冰壶会把之前的进过的位置全部撞开 所以我只需要讨论下一步是否出界或者是撞到块的情况
				//continue;
			if (map[nx][ny] == GOAL)
			{
				minopt = std::min(minopt, depth);
				continue;
			}
			if (map[nx][ny] == BLOCK)
			{
				//HIT IT REMOVE;
				map[nx][ny] = NO;
				//flag[x][y] = 1;
				dfs(depth + 1, nx - dir[i][0], ny - dir[i][1]);
				//flag[x][y] = 0;
				map[nx][ny] = BLOCK;
			}
			else
			{
				//flag[x][y] = 1;
				dfs(depth + 1, nx - dir[i][0], ny - dir[i][1]);
				//flag[x][y] = 0;
			}


		}
	}
}
int main()
{
	int r = 0;
	while (~scanf("%d %d", &w, &h) && w != 0 && h != 0)
	{
		int bx, by;
		for (int i = 0; i<h; ++i)
		{
			for (int j = 0; j<w; ++j)
			{
				scanf("%d", &map[i][j]);
				if (map[i][j] == START)
					bx = i, by = j;
			}

		}
		//地图准备完毕了 
		dfs(1, bx, by);
		if (minopt == limit + 1)
		{
			res[r++] = -1;
		}
		else
		{
			res[r++] = minopt;
		}
		minopt = limit + 1;
	}
	for (int i = 0; i<r; ++i)
	{
		if (res[i] != 0)
			printf("%d\n", res[i]);

	}
	return 0;
}
