#pragma once
#include "stdafx.h"
#include <queue>
#include <vector>
#include <stack>
typedef int	VertexType;//顶点的类型
int dire[4][2] = { { 0,-1 },{ -1,0 },{ 0,1 },{ 1,0 } };//方向 左 上 右 下
enum StepDirect{LEFT,TOP,RIGHT,DOWN};//表示方向的枚举成员
char DirectFlag[] = { 'L','T','R','D' };//用于识别前驱的方向
const VertexType NOT_BLOCK = 0;//这个表示不是阻碍
//记录
struct Point
{
	int x;//坐标
	int y;
	int step;//累计的步长
	int pre_x;//前驱X
	int pre_y;//前驱Y
	char dir;
	Point():x(-1),y(-1),step(-1),pre_x(-1),pre_y(-1){}
	Point(int _x,int _y,int _step):x(_x),y(_y),step(_step){}
	//若X Y为-1表示这个节点没有被访问过 所以就可以不需要额外建立数组保存visit
};

//BFS算法
void FindShortPath(VertexType **map,int map_row,int map_column,int start_x,int start_y,int dest_x,int dest_y,std::vector<StepDirect> &result)
{
	std::queue<Point> paths;
	if (map)
	{
		Point **pre = new Point*[map_row];//pre的功能可以表示X,Y的信息(累计的步长 前驱节点等)
		for (int i = 0; i < map_row; ++i)
		{
			pre[i] = new Point[map_column];
			for (int j = 0; j < map_column; ++j)
			{
				if (map[i][j] != NOT_BLOCK)//搜索阻碍物 如果是阻碍物的话那么就需要将pre对应位置的标记为已访问
					pre[i][j].x = pre[i][j].y = 0;
			}
		}
		paths.push(Point(start_x,start_y,0));//初始化起点的
		while (paths.empty() == false)
		{
			Point point = paths.front();
			Point temp_p;
			if (point.x == dest_x && point.y == dest_y)
			{
				/*
				printf("%d\n", point.step);//打印出最小的路径(最先到达的就是最短的)
				int px = dest_x; int py = dest_y;
				int temp;
				do
				{
					printf("(%d,%d)<--%c--", px, py, pre[px][py].dir);
					temp = px;
					px = pre[px][py].pre_x;
					py = pre[temp][py].pre_y;
				} while (px != start_x || py != start_y);
				printf("(%d,%d)", start_x, start_y);
				*/
				int px = dest_x, py = dest_y; int temp;
				std::stack<StepDirect> sta;
				do
				{
					switch (pre[px][py].dir)
					{
					case 'L':
						sta.push(StepDirect::LEFT); break;
					case 'R':
						sta.push(StepDirect::RIGHT); break;
					case 'T':
						sta.push(StepDirect::TOP); break;
					case 'D':
						sta.push(StepDirect::DOWN); break;
					default:
						break;
					}
					temp = px;
					px = pre[px][py].pre_x;
					py = pre[temp][py].pre_y;
				} while (px != start_x || py != start_y);
				while (!sta.empty())
				{
					result.push_back(sta.top());
					sta.pop();
				}
				break;
			}
			paths.pop();//弹出
			for (int i = 0; i < 4; ++i)
			{
				int temp_x = point.x + dire[i][0];
				int temp_y = point.y + dire[i][1];
				if ((temp_x >= 0 && temp_x < map_row) && (temp_y >= 0 && temp_y < map_column))
				{
					if (pre[temp_x][temp_y].x == -1 && pre[temp_x][temp_y].y == -1)
					{
						temp_p.x = temp_x;
						temp_p.y = temp_y;
						temp_p.step = point.step + 1;//步长递增
						temp_p.pre_x = point.x;
						temp_p.pre_y = point.y;
						temp_p.dir = DirectFlag[i];
						pre[temp_x][temp_y] = temp_p;
						paths.push(temp_p);//入队
					}
				}
			}
		}
		for (int i = 0; i < map_row; ++i)
				{
					delete[] pre[i];
				}
				delete[] pre;
	}
}