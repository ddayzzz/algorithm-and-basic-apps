// 描述 https://baike.baidu.com/item/%E6%8B%89%E4%B8%81%E6%96%B9%E9%98%B5
#include <iostream>
#include <list>
#include <iomanip>

using namespace std;
//拉丁方阵 我写的解法1
void latin_pattern(int n)
{
	list<int> latin;
	int jieshu = 1;
	int insernum = 1;
	for (int i = 1; i <= n*n; ++i)
	{
		latin.push_back(insernum);
		int flag = i % n;
		if (flag == 0)
		{
			jieshu++;
			insernum = jieshu;
			continue;
		}
		if (insernum >= n)
		{
			insernum = 1;
		}
		else
		{
			++insernum;
		}

	}
	auto i = latin.cbegin();
	for (int o = 1; o <= n*n; ++o)
	{
		if (o % n)
		{
			cout <<setw(3)<< *i++ << " ";
		}
		else
		{
			cout <<setw(3)<< *i++ << "\n";
		}
	}
}
void latin_pattern_1(int n)
{
	std::list<int> latin;
	for (int i = 1; i <= n; ++i)
		latin.push_back(i);
	auto it = latin.begin();
	auto last = --latin.end();
	int cnt = 1;

	auto beg = it;
	for (int i = 1; i <= n; ++i)
	{
		while (cnt <= n)
		{
			if (beg != last)
			{
				cout << *beg++ << " ";
			}
			else
			{
				cout << *beg << " ";
				beg = latin.begin();
			}
			if (cnt++ == n)
				cout << endl;
		}
		cnt = 1;
		beg = latin.begin();
		for (int j = 1; j <= i; ++j)
		{
			++beg;
		}
	}
	
}
int main()
{
    latin_pattern_1(5);//参数表示阶数
}