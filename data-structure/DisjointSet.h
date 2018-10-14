#pragma once
#include "stdafx.h"
#include <vector>
#include <map>
template<typename data_type> class DisjointSet
{
private:
	map<int, vector<int>> intership;
	vector<data_type> elements;//����洢�ľ��Ƕ�Ӧλ�õ�Ԫ��
	vector<int> PARENTS;//����Ǵ洢��Ӧλ�õĽڵ�ĸ��ڵ��λ�� ���ڱ����Ǹ��ڵ�Ļ� ����ľ���-1
	int size;//���ཻ����Ԫ�ظ���
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
			PARENTS[i] = -1;//��ʼ��Ĭ����ô���Ƕ�����
			if (it != en)
				elements[i] = *it++;
		}
			
	}
	int find(int item)
	{
		if (PARENTS[item] < 0)
			return item;
		else
			return PARENTS[item]=find(PARENTS[item]);//����һ��·�����㷨���ǽ�item���ϼ���Ϊ�����ڵ�ĸ��ڵ�
	}
	void setUnion(int se1,int se2)
	{
		int set1 = find(se1);
		int set2 = find(se2);
		if (set1 == set2) return;//SAME ROOT
		if (PARENTS[set1] < PARENTS[set2]) //ע����ڵ��Ǹ���
		{
			//SET2��Ϊset1������ 
 			PARENTS[set2] = set1;
		}
		else
		{
			if (PARENTS[set1] == PARENTS[set2])
			{
				//SET1 ��SET2 ������ͬ�ĸ߶� ����Ǿ�����ͬ�ĸ��ڵ� �Ѿ����ų���
				PARENTS[set2] -= 1;
			}
			PARENTS[set1] = set2;//set1��Ϊset2������ 
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
			cout << "��" << *at(i->first) << "���ڹ�ϵ�ģ�";
			for (auto j = i->second.cbegin(); j != i->second.cend(); ++j)
			{
				cout << *at(*j) << " ";
			}
			cout << endl;

		}
	}
};