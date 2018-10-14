#pragma once
#include "../stdafx.h"
#include <cstdlib>
typedef int Datatype_SharedStack;
struct Shared_Stack
{
	int top1;
	int top2;
	Datatype_SharedStack *data;
	int max;
};
typedef Shared_Stack *SharedStack;
SharedStack create_sharedStack(int maxsize)
{
	SharedStack s = (SharedStack)malloc(sizeof(Shared_Stack));
	Datatype_SharedStack* p = (Datatype_SharedStack*)malloc(sizeof(Datatype_SharedStack)*maxsize);
	s->top1 = -1;
	s->top2 = maxsize;
	s->data = p;
	s->max = maxsize;
	return s;
}
void push_sharedStack(Datatype_SharedStack d, SharedStack s, int stacknum)
{
	if (s->top2 - s->top1 == 1)
	{
		//Õ»ÒÑÂú
		return;
	}
	if (stacknum == 1)
	{
		s->top1++;
		s->data[s->top1] = d;
	}
	else
	{
		s->top2--;
		s->data[s->top2] = d;
	}
}
void pop_sharedStack(SharedStack s, int id)
{
	if (id == 1)
	{
		if (s->top1 == -1)
		{
			//¿ÕµÄ
			return;
		}
		s->top1--;
	}
	else
	{
		if (id == 2)
		{
			if (s->top2 ==s->max)
				return;
			s->top2++;
		}
	}
}
Datatype_SharedStack popandtop_sharedStack
(SharedStack s, int stacknum)
{
	if (stacknum == 1)
	{
		if (s->top1 == -1)
		{
			//¿ÕµÄ
			return 0;
		}
		return s->data[s->top1--];
	}
	else
	{
		if (stacknum == 2)
		{
			if (s->top2 == s->max)
				return 0;
			return s->data[s->top2++];
		}
	}
}
void free_sharedStack(SharedStack s)
{
	free(s->data);
	s->data = NULL;
	
}
void print_allelemaentsinSharedStack(SharedStack s)
{
	int i;
	printf("Õ»1Õ»µ×:\n");
	for (i = 0; i <= s->top1;++i)
		printf("%d\n", s->data[i]);
	printf("Õ»1Õ»¶¥\n");
	printf("Õ»2Õ»µ×\n");
	for (i = s->max - 1; i >= s->top2; --i)
		printf("%d\n", s->data[i]);
	printf("Õ»2Õ»¶¥\n");
}