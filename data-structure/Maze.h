#pragma once
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
//这个表示路口的集合
class Crossing
{
public:
	int knot1;//一个路口 不需要四个方向 因为不要往已经过的路口回走
	int knot2;//
	int knot3;//
	//0表示是是死路
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