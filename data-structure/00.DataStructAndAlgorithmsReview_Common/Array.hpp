#pragma once
#include "../stdafx.h"
/*
顺序容器的数据结构
创建于 2017年2月24日
*/
//顺序单链表(相当于vector)
template<typename _ty> class SequenceSingleList
{
private:
	_ty *data=nullptr;//保存链表的数组
	size_t capacity;//保存数组的大小
	size_t firstfree;//第一个可以写入数据的位置
	void check();//执行安全检查
	void do_resize(size_t sz);
	void do_remove(const _ty &dt);
public:
	SequenceSingleList(size_t size):data(new _ty[size]),capacity(size),firstfree(0){}
	bool isFull() { return firstfree == firstfree; }
	bool isEmpty() { return firstfree == 0u; }
	void resize(size_t newsize) { do_resize(newsize); }
	void insert(const _ty &dt)
	{
		check();
		data[firstfree++] = dt;
	}
	void remove(const _ty dt);
	_ty &operator[](size_t pos);
};
template<typename _ty>
void SequenceSingleList<_ty>::check()
{
	if (isFull() || data==nullptr)
	{
		resize((capacity == 0 ? 1 : capacity * 2));
	}
	else
	{

	}
}
template<typename _ty>
void SequenceSingleList<_ty>::do_resize(size_t sz)
{
	if (sz > 0 && sz > capacity)
	{
		_ty newptr = new _ty[sz];
		//复制元素
		for (size_t i = 0; i < firstfree; ++i)
		{
			newptr[i] = std::move(data[i]);
		}
		delete[] data;
		firstfree = i;
		data = newptr;
		capacity = sz;
	}
}
template<typename _ty>
void SequenceSingleList<_ty>::do_remove(const _ty & dt)
{
	size_t i = 0;
	for (; i < firstfree; ++i)
	{
		if (data[i] == dt)
		{
			//将后面的元素向前移动 以此达到删除的目的
			for (int j = i+1; j < firstfree; ++j)
			{
				data
			}
		}
	}
}