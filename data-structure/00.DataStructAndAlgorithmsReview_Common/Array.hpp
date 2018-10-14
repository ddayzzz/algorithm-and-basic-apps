#pragma once
#include "../stdafx.h"
/*
˳�����������ݽṹ
������ 2017��2��24��
*/
//˳������(�൱��vector)
template<typename _ty> class SequenceSingleList
{
private:
	_ty *data=nullptr;//�������������
	size_t capacity;//��������Ĵ�С
	size_t firstfree;//��һ������д�����ݵ�λ��
	void check();//ִ�а�ȫ���
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
		//����Ԫ��
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
			//�������Ԫ����ǰ�ƶ� �Դ˴ﵽɾ����Ŀ��
			for (int j = i+1; j < firstfree; ++j)
			{
				data
			}
		}
	}
}