#pragma once
#include "../stdafx.h"
#include <cstdlib>
typedef int DoubleNodeDataType;
struct DoubleNode
{
	DoubleNodeDataType data;
	DoubleNode *prior;
	DoubleNode *next;
};
typedef DoubleNode *DoubleList;
DoubleList initialize_DoubleList()
{
	DoubleList d = (DoubleList)malloc(sizeof(DoubleNode));
	d->next = d;
	d->prior = d;
	return d;
}
void insert_DoubleList(DoubleList list, int i, DoubleNodeDataType da)
{
	int cnt;
	DoubleNode *s = (DoubleList)malloc(sizeof(DoubleNode));
	s->data = da;
	DoubleList qianqu = list;
	for (cnt = 1; cnt <= i-1; ++cnt)
	{
		qianqu = qianqu->next;
	}
	//
	s->prior = qianqu;
	s->next = qianqu->next;
	qianqu->next->prior = s;
	qianqu->next = s;
}
void delete_DoubleList(DoubleList list, int i)
{
	int cnt;
	DoubleList pr=list;
	for (cnt = 1; cnt <= i - 1; ++cnt)
	{
		pr = pr->next;
	}
	DoubleList del = pr->next;
	pr->next = del->next;
	pr->next->next->prior = pr;
	free(del);
}
void print_DoubleList_next(DoubleList list)
{
	DoubleList d = list->next;
	while (d->next !=list)
	{
		printf("%d\n", d->data);
		d = d->next;
	}
	printf("%d\n", d->data);
}
void print_DoubleList_prior(DoubleList list)
{
	DoubleList d = list->prior;
	while (d->prior != list)
	{
		printf("%d\n", d->data);
		d = d->prior;
	}
	printf("%d\n", d->data);
}
void free_DoubleList(DoubleList dl)
{
	DoubleList d = dl;
	DoubleList temp;
	while (d->next != dl)
	{
		temp = d->next;
		free(d);
		d = temp;
	}
	//free(dl);
}