#pragma once
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
//�����ʾ·�ڵļ���
class Crossing
{
public:
	int knot1;//һ��·�� ����Ҫ�ĸ����� ��Ϊ��Ҫ���Ѿ�����·�ڻ���
	int knot2;//
	int knot3;//
	//0��ʾ������·
	Crossing(int one,int two,int three):knot1(one),knot2(two),knot3(three){}
private:

};
class Maze
{
public:
	Maze(std::vector<Crossing> cros,int endcode):crossings(cros),exitcode(endcode){}
	void FindExit()
	{
		do_find(1);
		while (result.empty() == false)
		{
			cout << result.top() << "->";
			result.pop();
		}
		cout << "Exit"<<endl;
	}
private:
	std::vector<Crossing> crossings;
	std::stack<int> result;
	int exitcode;
	int do_find(int entrance)
	{
		if (entrance == 0) { return 0; }
		if (entrance == exitcode)
		{
			result.push(exitcode);
			return 1;
		}
		if (do_find(crossings[entrance].knot1) == 1)
		{
			result.push(entrance);
			return 1;
		}
		if (do_find(crossings[entrance].knot2) == 1)
		{
			result.push(entrance);
			return 1;
		}
		if (do_find(crossings[entrance].knot3) == 1)
		{
			result.push(entrance);
			return 1;
		}
		return 0;

	}
};