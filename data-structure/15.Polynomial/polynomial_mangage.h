#pragma once
#include "../stdafx.h"
#include "polynomial.h"
struct polynomial_manage
{
	unsigned int maxsize=-1;
	polynomial *polylist;
	//更具大小初始化一个管理多项式的数组
	void initial(unsigned int size)
	{
		polylist = (polynomial*)malloc(size* sizeof(polynomial));
		if (polylist == NULL)
		{
			
		}
		else
		{
			int s;
			for (s = 0; s < size; ++s)
			{
				polylist[s].nd.makeempty();
			}
			maxsize = size;
		}
	}
	//根据索引构造多项式
	bool construct_poly(unsigned index,int unknown,int num,int *xishushuzu_ptr)
	{
		polynomial *p = get_address_byindex(index);
		if (p != NULL)
		{
			p->initpolynomal(unknown, xishushuzu_ptr, num);
			return true;
		}
		else
		{
			return false;
		}
	}
	//根据索引返回多项式对象的指针
	polynomial *get_address_byindex(unsigned int index)
	{
		if (polylist == NULL) { return NULL; }
		if (index >= maxsize) { return NULL; }
		return (polylist + index);
	}
	//释放资源
	void free_polylist()
	{
		//delete[] polylist;
		
		int s;
		for (s = maxsize-1; s >=0; --s)
		{
			get_address_byindex(s)->free_poly();
			
		}	
		
	}
	//计算多项式的值 存入另一个保存结果的多项式
	void calc_polys(unsigned l, unsigned r,int unk,char opsym,polynomial *dest)
	{
		if (l >= maxsize || r >= maxsize)
		{
			return;
		}
		else
		{
			switch (opsym)
			{
			case '+': get_address_byindex(l)->plus_xishuofpoly(get_address_byindex(r), dest, unk); break;

			case '*': get_address_byindex(l)->multiply_xishuopoly(get_address_byindex(r), dest, unk); break;

			default:
				break;
			}
		}
	}
	//输出 带未知数的多项式表达式
	void print_unknown_all(unsigned i, char unk, char endchar)
	{
		if (i < maxsize)
		{
			get_address_byindex(i)->show_unary_mode(endchar, unk);
		}
	}
};