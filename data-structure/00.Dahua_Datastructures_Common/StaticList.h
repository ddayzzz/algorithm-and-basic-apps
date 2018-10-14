#pragma once
#include "../stdafx.h"
#include <cstdlib>
//��̬�����ʵ��
const int MAXSIZE = 1000;
typedef int DataType;

struct StaticList
{
	int cursor;
	DataType data;
	int maxsize;
};
typedef StaticList *CursorList;
//ɾ��iԪ�� ˽�к���
void free_cursorlist(CursorList list, int i)
{
	list[i].cursor = list[0].cursor;
	list[0].cursor = i;
}
//���ط������Ԫ�ص�λ��
int malloc_cursorlist(CursorList list)
{
	int index = list[0].cursor;
	if (list[0].cursor)
		list[0].cursor = list[index].cursor;
	return index;
}
//��ʼ��һ����̬���� ��Ԫ�ر���ָ���һ����������ڵ���±� ���һ��Ԫ�ر���ָ���ͷ��Ԫ�ص��±�
CursorList initialize_cursorlist(int maxsize)
{
	if (maxsize > 0)
	{
		CursorList list = (CursorList)malloc(maxsize * sizeof(StaticList));
		if (list)
		{
			int i;
			for (i = 0; i < maxsize-1; ++i)
				list[i].cursor = i + 1;
			list[maxsize - 1].cursor = 0;
			list[0].maxsize = maxsize;
			return list;
		}
		return NULL;
	}
	else
	{
		return NULL;
	}
}
//��iλ��֮ǰ����һ��Ԫ�� 
void insert_cursorlist(CursorList list, int i, DataType da)
{
	int needtoinsert = malloc_cursorlist(list);
	list[needtoinsert].data = da;
	int max = list[0].maxsize;
	int cnt;
	int k = max - 1;
	for (cnt = 1; cnt <= i - 1; ++cnt)
	{
		k = list[k].cursor;
	}
	//��ʱk����Ҫ����Ԫ��֮ǰ��λ�õ��±�
	list[needtoinsert].cursor = list[k].cursor;
	list[k].cursor = needtoinsert;//ע�� ��ͷ��λ��Ҳ������ȷ����
}
//ɾ��iԪ��
void delete_cursorlist(CursorList list, int i)
{
	int u;
	int k = list[0].maxsize - 1;
	for (u = 1; u <= i - 1; ++i)
	{
		k = list[k].cursor;
	}
	int j = list[k].cursor;
	list[k].cursor = list[j].cursor;
	free_cursorlist(list, j);
}

void print_allelements(CursorList list)
{
	int k = list[0].maxsize - 1;
	while (list[k].cursor != 0)
	{
		printf("%d\n", list[list[k].cursor].data);
		k = list[k].cursor;
	}
}