#pragma once
#include "../stdafx.h"
#include "polynomial.h"
struct polynomial_manage
{
	unsigned int maxsize=-1;
	polynomial *polylist;
	//���ߴ�С��ʼ��һ���������ʽ������
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
	//���������������ʽ
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
	//�����������ض���ʽ�����ָ��
	polynomial *get_address_byindex(unsigned int index)
	{
		if (polylist == NULL) { return NULL; }
		if (index >= maxsize) { return NULL; }
		return (polylist + index);
	}
	//�ͷ���Դ
	void free_polylist()
	{
		//delete[] polylist;
		
		int s;
		for (s = maxsize-1; s >=0; --s)
		{
			get_address_byindex(s)->free_poly();
			
		}	
		
	}
	//�������ʽ��ֵ ������һ���������Ķ���ʽ
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
	//��� ��δ֪���Ķ���ʽ���ʽ
	void print_unknown_all(unsigned i, char unk, char endchar)
	{
		if (i < maxsize)
		{
			get_address_byindex(i)->show_unary_mode(endchar, unk);
		}
	}
};