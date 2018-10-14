#pragma once
#include "../stdafx.h"
#include <cstdlib>
typedef int DatatypeofLinkQueue;
struct LinkQueueNode_List
{
	DatatypeofLinkQueue data;
	LinkQueueNode_List *next;
};
//typedef LinkQueueNode *LinkQueue;
struct LinkQueueNode
{
	LinkQueueNode_List *front;
	LinkQueueNode_List *rear;
};
typedef LinkQueueNode *LinkQueue;
LinkQueue create_empty_linkqueue()
{
	LinkQueue p = (LinkQueue)malloc(sizeof(struct LinkQueueNode));
	LinkQueueNode_List* list = (LinkQueueNode_List*)malloc(sizeof(LinkQueueNode_List));
	if (p && list)
	{
		p->front = p->rear = list;//当为空的链队列时 front=rear=头结点地址
		p->rear->next = NULL;
		list->next = NULL;
		return p;
	}
}
int isempty_linkqueue(LinkQueue q)
{
	if (q)
	{
		return q->front == q->rear;
	}
	return 1;
}
void EnQueue_linkqueue(LinkQueue q, DatatypeofLinkQueue da)
{
	LinkQueueNode_List *s = (LinkQueueNode_List*)malloc(sizeof(LinkQueueNode_List));
	if (s)
	{
		s->data = da;
		s->next = NULL;//最后一个元素的后继为NULL
		q->rear->next = s;
		q->rear = s;
	}
}
DatatypeofLinkQueue DeQueue_linkqueuq(LinkQueue q)
{
	if (!isempty_linkqueue(q))
	{
		LinkQueueNode_List *temp = q->front->next->next;
		DatatypeofLinkQueue f = q->front->next->data;
		free(q->front->next);
		q->front->next = temp;
		return f;
	}
}
void destroy_allLinkQueue(LinkQueue q)
{
	if (!isempty_linkqueue(q))
	{
		if (q->front != NULL)
		{
			LinkQueueNode_List *j = q->front->next,*temp;
			while (j != NULL)
			{
				temp = j->next;
				free(j);
				j = temp;
			}
			q->front = q->rear = NULL;
		}
	}
}