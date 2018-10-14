#pragma once
#include "stdafx.h"
int sum=0;
//N�ʺ�����
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
		for (int j = 0; j < size; ++j)//j���������ƻʺ����ӷ��õ�λ�õ�
		{
			if (i == size)
			{
				sum++;
				cout << "��" << sum << "���:\n";
				printout();//������
				return;
			}
			Queen[i] = j;
			if (IsVaild(i))
				PlaceQueen(i + 1);//���û������Ļ��ͷ�����һ���ʺ�
		}
	}
	void printout()
	{
		for (int i = 0; i < size; ++i)
		{
			//i������
			for (int j = 0; j < size; ++j)//j������
			{
				if (j == Queen[i])//����������ڻʺ󱻷��õı��
					cout << "# ";//���������ʾ�����ϵĻʺ�
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