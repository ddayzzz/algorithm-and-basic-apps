// 魔术师发牌问题: 问题描述 https://www.cnblogs.com/ranjiewen/p/6439667.html
#include <iostream>
#include <list>

using namespace std;


void realease_poker()
{
	list<int> poker;
	for (int i = 1; i <= 13; ++i)
	{
		poker.push_back(0);
	}
	//poker[0]='1';
	auto it = poker.begin();
	*it = 1;
	for (int i = 2; i < 14; ++i)//注意是从从黑桃1开始的也就是index=2
	{
		for (int j = 0; j < i; ++j)
		{
			it++;
			if (it == poker.end())
			{
				it = poker.begin();
			}
			
			if (*it != 0)
				--j;
		}
		*it= i;

		if (it == poker.end())
		{
			it = poker.begin();
		}
	}
	for (auto i = poker.cbegin(); i != poker.cend(); ++i)
		cout << *i << " ";
}
int main()
{
    realease_poker();
}