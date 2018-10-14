#pragma once
#include "stdafx.h"
#include <cmath>
#include <algorithm>
#include <numeric>
#include <functional>
//使用数组实现的堆
template<typename T,typename Comp=bool(int,int)> class HeapArray
{
private:
	T *data;//数组指针
	int capacity;//数组的最大元素容器
	int size;//这个记录当前数组实际元素
	//自下向上调整
	void modifyUp(int start)
	{
		int n = start;//这个是其实索引
		//2I是左儿子的节点 2I+1是右儿子节点 父节点是floor(i-1)/2 start将会从size-1向上移动到0
		int parent = (start - 1) / 2;
		T temp;
		while (start > 0)
		{
			if (orderComp(data[start],data[parent])/*data[start] > data[parent]*/)
			{
				//printf("change : parent is %d start is %d\n", data[parent], data[start]);
				//交换顺序
				temp = data[start];
				data[start] = data[parent];
				data[parent] = temp;
				start = parent;//起始的为原父节点
				parent = (start - 1) / 2;//改为start原父节点的父节点
			}
			else
			{
				break;//这个节点<=父亲 不需要再调整了
			}
		}
	}
	//自上向下调整
	void modifyDown(int start, int end)
	{
		//这个是向下调整顺序
		//左儿子的索引为2i+1 右儿子为2i+2
		int i = start;
		int left = (2 * i + 1);
		T tmp = data[i];//这个tmp保存的是
		while (left <= end)//这end表示最后能有儿子的节点
		{
			//此时的首元素为data[size]
			//在左儿子和右儿子之间选择
			if (left < end && orderComp(data[left+1],data[left])/* data[left] < data[left + 1]*/)
			{
				//右儿子是最大的值 所以这个left要更新为右儿子
				++left;
			}
			if (orderComp(tmp,data[left]) || (!orderComp(data[left],tmp) && !orderComp(tmp,data[left]))/*tmp >= data[left]*/) { break; }//如果检测到节点比他的左儿子大那么久不需要比较了 i表示的就是目标写入的索引
			else

			{
				//这个left是目标替换位置 可以左儿子也可以是右儿子
				data[i] = data[left];//写入
				i = left;//更新搜索位置
				left = 2 * i + 1;//从新设置左儿子位置

			}

		}
		data[i] = tmp;//更新了目标的值
	}
	//typedef bool(*Comp)(const T&, const T&);
	function<Comp> orderComp;
	
public:
	//默认的构造函数默认使用>比较运算符 也就是大堆
	HeapArray():HeapArray(10){}
	//指定容量的构造函数 默认使用>比较运算符 也就是大堆
	HeapArray(int cap, function<Comp> ops = std::greater<int>()) :capacity(cap), data(new T[cap]), size(0), orderComp(ops) {}
	void insert(T da)
	{
		if (size == capacity)
		{
			//如果大小超过了容量那么退出
			return;
		}
		if (data != nullptr)
		{
			data[size] = da;
			modifyUp(size);
			size++;
		}
	}
	void erase(T da)
	{
		int index = getIndex(da);
		if (index >= 0)
		{
			//find it
			data[index] = data[--size];
			modifyDown(index, size-1);
		}
	}
	int getIndex(T da)
	{
		int i;
		for (i = 0; i < size; ++i)
		{
			if (data[i] == da)
				return i;
		}
		return -1;
	}
	T TopandPop()
	{
		T res;
		if (size > 0)
		{
			res = data[0];
			erase(res);
		}
		return res;
	}
	int getSize()
	{
		return size;
	}
	void print()
	{
		for (int i = 0; i < size; ++i)
		{
			cout << data[i] << " ";
		}
		cout << endl;
	}
	~HeapArray() {
		delete data;
		data = nullptr;
		size = capacity = 0;
	}
};