#pragma once
#ifndef  _LIST_H
#define _LIST_H
#include "../stdafx.h"
#include "list.h"
#include <stdlib.h>
/*
链表类型 请使用makeempty初始化
        使用free_list释放表头及所有的元素
*/
struct Node
{
	typedef int elementtype;//保存元素类型
	typedef struct Node *PtrtoNode;
	typedef PtrtoNode List;//链表类型
	typedef PtrtoNode Position;//位置类型别名

	Position next;//下一元素的指针
	elementtype data;//当前元素的数值
	Position head=NULL;//表头
	//判断是否为空的链表
	int isempty(List l)
	{
		return l->next == NULL;
	}
	//返回是否是最后一个元素
	int islast(Position p, List l)
	{
		return p->next == NULL;
	}
	//根据元素的值 返回指向该元素的指针
	Position find(elementtype t, List l)
	{
		Position p;
		p = l->next;
		while (p != NULL)
		{
			if (p->data == t)
			{
				return p;
			}
			else
			{
				p = p->next;
			}
		}
		return NULL;
	}
	//根据元素的值 返回指向该元素的前驱指针
	Position findprevious(elementtype t, List l)
	{
		Position p;
		p = l;
		while (p->next != NULL && p->next->data != t)
		{
			p = p->next;
		}
		return p;
	}
	//根据元素的值 删除元素
	void deleteele(elementtype t, List l)
	{

		Position priver = findprevious(t, l), temp;
		if (priver == NULL) return;
		if (islast(priver, l))
		{

		}
		else
		{
			temp = priver->next;
			priver->next = temp->next;
			free(temp);
		}
	}
	//将元素插入到指定的位置的后面
	void insert(elementtype t, List l)
	{
		Position pos;
		pos = (Position)malloc(sizeof(struct Node));
		if (pos == NULL)
		{
			//error
		}
		else
		{
			pos->data = t;
			pos->next = l->next;
			l->next = pos;
		}
	}
	//返回表头元素的指针
	Position header(List l)
	{
		return head;
	}
	//删除指定参数指针之后的链表 参数变为最后的元素
	void deletelist(List l)
	{
		Position p;
		
		p = l->next;
		l->next = NULL;
		Position temp;
		while (p != NULL)
		{
			if (p->next != NULL)
			{
				temp = p->next;
				free(p);
				p = temp;
			}
			else
			{
				return;
			}
		}

	}
	//得到指定位置的保存元素的值
	elementtype retrieve(Position p)
	{
		return p->data;
	}
	//初始化一个空的链表
	List makeempty()
	{
		head = (Position)malloc(sizeof(Node));
		head->next = NULL;
		head->data = elementtype();
		return head;
	}
	//返回首元素的地址
	Position first( List l)
	{
		return head->next;
	}
	//返回最后元素的指针
	Position last(List l)
	{
		Position pos = head;
		if (head == NULL) return NULL;
		while (pos->next != NULL)
		{
			pos = pos->next;
		}
		return pos;
	}
	//打印保存的所有的元素
	void print_all_elements()
	{
		if (head ==NULL) 
			return;
		Position p = head;
		

		while (p->next != NULL)
		{
			if (islast(p->next, p->next))
			{
				printf("%d", p->next->data);
			}
			else
			{
				printf("%d,", p->next->data);
			}
			p = p->next;
		}
	}
	//删除链表的所有元素 包括表头
	void free_list()
	{
		deletelist(head);
		free(head);
	}
	//获取链表的大小
	unsigned int size()
	{
		Position pos = head;
		unsigned int s = 0;
		if (pos == NULL) return s;
		while (pos->next != NULL)
		{
			++s;
			pos = pos->next;
		}
		return s;
	}
	//根据index的值返回对应地址(不包括表头)元素的值的地址
	int* get_position_byindex(unsigned int index)
	{
		unsigned cnt = 0;
		if (index >= size()) return 0;
		Position pos = head->next;
		while (pos->next != NULL && cnt < index)
		{
			pos = pos->next;
			++cnt;
		}
		return &pos->data;
	}
	//计算两个list的交集 写入到Node对象
	void intersection(List l,List dest)
	{
		Position p=head->next;
		dest->makeempty();
		Position dp = dest->head;
		while (p != NULL)
		{
			Position res = l->find(p->data, l);
			if (res != NULL)
			{
				dest->insert(res->data, dp);
				dp = dp->next;
			}
		}
		
	}
};
#endif // ! _LIST_H
