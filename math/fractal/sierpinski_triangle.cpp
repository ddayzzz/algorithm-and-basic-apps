// ConsoleApplication5.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// wiki https://zh.wikipedia.org/wiki/%E8%AC%9D%E7%88%BE%E8%B3%93%E6%96%AF%E5%9F%BA%E4%B8%89%E8%A7%92%E5%BD%A2

#include <iostream>
#include <string>
using namespace std;

char map[1000][1000];

void draw_tri(int i, int j)
{
	map[i][j] = '/';
	map[i][j + 1] = '\\';
	map[i + 1][j - 1] = '/';
	map[i + 1][j] = '_';
	map[i + 1][j + 1] = '_';
	map[i + 1][j + 2] = '\\';
}
void tri(int rank, int i1, int j1, int i2, int j2, int i3, int j3)
{
	if (rank == 2)
	{
		// N = 1. 表示第一个三角形
		draw_tri(i1, j1);
		draw_tri(i2, j2);
		draw_tri(i3, j3);
		
	}
	else
	{
		// 每一个 (ix, jx) 都是一个小三角的上顶点的起始位置。一个大三角形可以分为几个小三个小三角形。对于每个小三角形又能构成其子问题
		tri(rank - 1, i1, j1, i1 + (1 << (rank - 2)), j1 - (1 << (rank - 2)), i1 + (1 << (rank - 2)), j1 + (1 << (rank - 2)));
		tri(rank - 1, i2, j2, i2 + (1 << (rank - 2)), j2 - (1 << (rank - 2)), i2 + (1 << (rank - 2)), j2 + (1 << (rank - 2)));
		tri(rank - 1, i3, j3, i3 + (1 << (rank - 2)), j3 - (1 << (rank - 2)), i3 + (1 << (rank - 2)), j3 + (1 << (rank - 2)));
	}
}
void print(int maxC)
{
	for (int c = 0; c < maxC; ++c)
	{
		cout << map[c] << endl;
	}
}
void drawOne()
{
	draw_tri(0, 1);
}
int main()
{
	int t;
	int n;
	cin >> t;
	while (t--)
	{
		cin >> n;
		// init
		int maxR = 1 << (n + 1);
		int maxC = 1 << n;
		for (int b = 0; b < maxC; ++b)
		{
			int a;
            for(a=0;a <= maxC +b;++a) // 注意不要在后面加上多余的任何字符, 包括空格
                map[b][a] = ' ';
            map[b][a] = '\0';
			
		}
		// 画triangle
		if (n == 1)
		{
			drawOne();
		}
		else
		{
			tri(n, 0, maxC - 1, 1 << (n - 1), (1 << (n - 1)) - 1, 1 << (n - 1), (1 << (n - 1)) * 3 - 1); // 只要阶数 > 2 就画三角形
			
		}
		print(maxC);
	}
	return 0;
}