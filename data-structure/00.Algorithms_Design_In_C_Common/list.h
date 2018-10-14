#pragma once
#ifndef  _LIST_H
#define _LIST_H
#include "../stdafx.h"
#include "list.h"
#include <stdlib.h>
/*
�������� ��ʹ��makeempty��ʼ��
        ʹ��free_list�ͷű�ͷ�����е�Ԫ��
*/
struct Node
{
	typedef int elementtype;//����Ԫ������
	typedef struct Node *PtrtoNode;
	typedef PtrtoNode List;//��������
	typedef PtrtoNode Position;//λ�����ͱ���

	Position next;//��һԪ�ص�ָ��
	elementtype data;//��ǰԪ�ص���ֵ
	Position head=NULL;//��ͷ
	//�ж��Ƿ�Ϊ�յ�����
	int isempty(List l)
	{
		return l->next == NULL;
	}
	//�����Ƿ������һ��Ԫ��
	int islast(Position p, List l)
	{
		return p->next == NULL;
	}
	//����Ԫ�ص�ֵ ����ָ���Ԫ�ص�ָ��
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
	//����Ԫ�ص�ֵ ����ָ���Ԫ�ص�ǰ��ָ��
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
	//����Ԫ�ص�ֵ ɾ��Ԫ��
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
	//��Ԫ�ز��뵽ָ����λ�õĺ���
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
	//���ر�ͷԪ�ص�ָ��
	Position header(List l)
	{
		return head;
	}
	//ɾ��ָ������ָ��֮������� ������Ϊ����Ԫ��
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
	//�õ�ָ��λ�õı���Ԫ�ص�ֵ
	elementtype retrieve(Position p)
	{
		return p->data;
	}
	//��ʼ��һ���յ�����
	List makeempty()
	{
		head = (Position)malloc(sizeof(Node));
		head->next = NULL;
		head->data = elementtype();
		return head;
	}
	//������Ԫ�صĵ�ַ
	Position first( List l)
	{
		return head->next;
	}
	//�������Ԫ�ص�ָ��
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
	//��ӡ��������е�Ԫ��
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
	//ɾ�����������Ԫ�� ������ͷ
	void free_list()
	{
		deletelist(head);
		free(head);
	}
	//��ȡ����Ĵ�С
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
	//����index��ֵ���ض�Ӧ��ַ(��������ͷ)Ԫ�ص�ֵ�ĵ�ַ
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
	//��������list�Ľ��� д�뵽Node����
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
