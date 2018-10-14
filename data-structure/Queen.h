#pragma once
#include "stdafx.h"
int sum=0;
//N皇后问题
class QueenPuzzle
{
public:
	QueenPuzzle(int n = 8) :size(n),Queen(new int[n]) { }
	bool IsVaild(int queenindex)
	{
		for (int i = 0; i < queenindex; ++i)
		{
			if (Queen[i] == Queen[queenindex])
				return false;
			if (abs(Queen[i] - Queen[queenindex]) == queenindex-i)
				return 0;

		}
		return true;
	}
	void PlaceQueen(int i)
	{
		for (int j = 0; j < size; ++j)//j是用来控制皇后棋子放置的位置的
		{
			if (i == size)
			{
				sum++;
				cout << "第" << sum << "组解:\n";
				printout();//输出结果
				return;
			}
			Queen[i] = j;
			if (IsVaild(i))
				PlaceQueen(i + 1);//如果没有问题的话就放置下一个皇后
		}
	}
	void printout()
	{
		for (int i = 0; i < size; ++i)
		{
			//i是行数
			for (int j = 0; j < size; ++j)//j是列数
			{
				if (j == Queen[i])//如果列数等于皇后被放置的编号
					cout << "# ";//这个用来表示棋盘上的皇后
				else
					cout << " ";
			}
			cout << endl;
		}
	}
	~QueenPuzzle()
	{
		delete Queen;

	}
	//static int sum;
private:
	int size;
	int *Queen;
	

};