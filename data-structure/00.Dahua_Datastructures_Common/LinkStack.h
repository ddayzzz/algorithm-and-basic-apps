#pragma once
#include "../stdafx.h"
#include <cstdlib>
typedef char DataType_LinkStack;
struct LinkStackNode
{
	DataType_LinkStack data;
	LinkStackNode *next;//保存栈顶的指针 入栈时 总是向前插入
};
typedef LinkStackNode *LinkStack;
LinkStack create_empty_LinkStack()
{
	LinkStack s=(LinkStack)malloc(sizeof(LinkStackNode));
	s->next = NULL;
	return s;
}
void push_LinkStack(DataType_LinkStack d, LinkStack s)
{
	if (s != NULL)
	{
		LinkStack o = (LinkStack)malloc(sizeof(LinkStackNode));
		if (o)
		{
			o->data = d;
			o->next = s->next;
			s->next = o;
		}
	}
}
DataType_LinkStack topandpop_linkstack(LinkStack s)
{
	if (s->next != NULL)
	{
		LinkStack temp = s->next->next;
		DataType_LinkStack d = s->next->data;
		free(s->next);
		s->next = temp;
		return d;
	}
}
void free_all_linkstack(LinkStack s)
{
	LinkStack p = s->next;
	LinkStack temp;
	while (p != NULL)
	{
		temp = p->next;
		free(p);
		p = temp;
	}
}
void print_all_linkstack(LinkStack s)
{
	printf("从栈顶排列：");
	LinkStack p = s->next;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	p->next = NULL;
	printf("\n");
}