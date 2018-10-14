#pragma once
#include "../stdafx.h"
#include <cstdlib>
//静态链表的实现
const int MAXSIZE = 1000;
typedef int DataType;

struct StaticList
{
	int cursor;
	DataType data;
	int maxsize;
};
typedef StaticList *CursorList;
//删除i元素 私有函数
void free_cursorlist(CursorList list, int i)
{
	list[i].cursor = list[0].cursor;
	list[0].cursor = i;
}
//返回分配插入元素的位置
int malloc_cursorlist(CursorList list)
{
	int index = list[0].cursor;
	if (list[0].cursor)
		list[0].cursor = list[index].cursor;
	return index;
}
//初始化一个静态链表 首元素保存指向第一个备用链表节点的下标 最后一个元素保存指向表头的元素的下标
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
//在i位置之前插入一个元素 
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
	//此时k是需要插入元素之前的位置的下标
	list[needtoinsert].cursor = list[k].cursor;
	list[k].cursor = needtoinsert;//注意 表头的位置也在这里确认了
}
//删除i元素
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