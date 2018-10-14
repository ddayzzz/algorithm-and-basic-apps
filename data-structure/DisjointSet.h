#pragma once
#include "stdafx.h"
#include <vector>
#include <map>
template<typename data_type> class DisjointSet
{
private:
	map<int, vector<int>> intership;
	vector<data_type> elements;//这个存储的就是对应位置的元素
	vector<int> PARENTS;//这个是存储对应位置的节点的父节点的位置 对于本身是根节点的话 保存的就是-1
	int size;//不相交集的元素个数
	void do_getIntership()
	{
		vector<int> fg(size);
		for (int p = 0; p < size; ++p)
		{
			if (PARENTS[p] < 0)
				intership[p];
			else
			{
				int root = find(p);
				intership[root].push_back(p);
			}
		}
		
	}

public:
	DisjointSet(int sz,std::initializer_list<data_type> init) :size(sz),elements(sz), PARENTS(sz)
	{
		auto en = init.end();
		auto it = init.begin();
		for (int i = 0; i < sz; ++i)
		{
			PARENTS[i] = -1;//初始化默认他么都是独立的
			if (it != en)
				elements[i] = *it++;
		}
			
	}
	int find(int item)
	{
		if (PARENTS[item] < 0)
			return item;
		else
			return PARENTS[item]=find(PARENTS[item]);//这是一个路径的算法总是将item的上级改为他父节点的父节点
	}
	void setUnion(int se1,int se2)
	{
		int set1 = find(se1);
		int set2 = find(se2);
		if (set1 == set2) return;//SAME ROOT
		if (PARENTS[set1] < PARENTS[set2]) //注意根节点是付的
		{
			//SET2变为set1的子树 
 			PARENTS[set2] = set1;
		}
		else
		{
			if (PARENTS[set1] == PARENTS[set2])
			{
				//SET1 与SET2 具有相同的高度 如果是具有相同的根节点 已经被排除了
				PARENTS[set2] -= 1;
			}
			PARENTS[set1] = set2;//set1作为set2的子树 
		}
	}
	data_type *at(const int index)
	{
		if (index >= 0 && index < size)
			return &elements[index];
		return nullptr;
	}
	~DisjointSet()
	{
		
	}
	void print()
	{
		intership.clear();
		do_getIntership();
		for (auto i = intership.cbegin(); i != intership.cend(); ++i)
		{
			cout << "与" << *at(i->first) << "存在关系的：";
			for (auto j = i->second.cbegin(); j != i->second.cend(); ++j)
			{
				cout << *at(*j) << " ";
			}
			cout << endl;

		}
	}
};