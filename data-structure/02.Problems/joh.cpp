// 约瑟夫环的一些问题

#include <list>
#include <iostream>
#include <string>
#include <algorithm>

//解法一：list模拟
int jos(int tobedel,int tot)
{
	//tobedel是删除的报数编号 从1开始
	//toto是总人数
	std::list<int> list;
	
	int n = tot;
	for (int i = 1; i <= n; ++i)
		list.insert(list.end(),i);
	std::list<int>::iterator it = list.begin();
	while (list.size() > 1)
	{
		for (int i = 1; i < tobedel; ++i)
		{
			if (++it == list.end())
			{
				it = list.begin();
			}

		}
		std::list<int>::iterator del = it;
		if (++it == list.end())
		{
			it = list.begin();
		}
		list.erase(del);
	}
	return *(it);
}
//解法二：数学方法
int jos2(int tobedel,int total)
{
	int x1=0;
	for (int i = 2; i <= total; ++i)
	{
		x1 = (x1 + tobedel) % i;
	}
	return x1+1;
}
int main()
{
    // 报2的删除
    int j=jos(2,16900);
    int u = jos2(2,16900);
    std::cout << "Normal:"<<j<<std::endl << "Math:"<<u<<std::endl;
}