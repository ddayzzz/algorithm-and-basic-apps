#pragma once
#include "../stdafx.h"
#include <cstdlib>
struct S
{
	char *first;//保存指向第一个字符的指针
	char *firstfree;//保存指向最后一个字符的尾后位置
	char *cap;//保存指向分配内存的未地址
};
typedef S *String;
typedef int Position;
const unsigned int DEFAULT_SIZE = 20;//默认的字符大小
const char DEFAULT_CHAR = '\0';//默认的填充字符
/*
	cap-first 是容量
	firstfree-first 是当前字符串的大小
*/
void reallocate_private_string(String sou, Position newsize);
void free_private_string(char *s, int freespace);
char *copy_from_private_string(char *source, char *end1, char *dest, char *cap);

//返回容量大小
Position capacity_string(String s) {
	if (s)
	{
		return s->cap - s->first;
	}
	return 0;
}
//返回字符串大小
Position size_string(String s) {
	if (s)
	{
		return s->firstfree - s->first;
	}
	return 0;
}
//创建制定大小的字符串
String create_string(char fillchar=DEFAULT_CHAR,unsigned int size = DEFAULT_SIZE)
{
	String res = (String)malloc(sizeof(S));
	char *data = (char*)malloc(sizeof(char)*(size + 1));
	data[0] = '\0';
	int cnt;
	for (cnt = 1; cnt <= size - 1; ++cnt)
	{
		data[cnt] = fillchar;
	}
	res->first = data;
	res->cap = data + size;
	res->firstfree = data;
	*(res->cap) = '\0';
	return res;
}
//私有函数区
//用于重新分配一个新的空间用于存储char数组
void reallocate_private_string(String sou, Position newsize)
{
	char *newdata = (char*)malloc(sizeof(char)*(newsize + 1));
	copy_from_private_string(sou->first, sou->firstfree, newdata, newdata + newsize);
	int orgsize = size_string(sou);
	free_private_string(sou->first, 1);
	sou->cap = newdata + newsize;
	sou->first = newdata;
	sou->firstfree = newdata + orgsize;
	*sou->cap = '\0';
}
//释放或清除字符内容
void free_private_string(char *s,int freespace)
{
	if (s)
	{
		if (freespace)
		{
			free(s);
			
		}
		else {
			*s = '\0';
		}
	}
}
//提供对于底层数据的操作
char *copy_from_private_string(char *source,char *end1, char *dest,char *cap)
{
	char *beg1 = source;
	char *beg2 = dest;
	while (beg1 != end1 && beg2 != cap)
	{
		*beg2 = *beg1;
		++beg1; ++beg2;
	}
	*beg2 = '\0';
	return dest;
}
//检查插入操作是否合法 如果存在溢出情况 那么重新分配
void check_insertOperation_private_string(String s)
{
	if (s)
	{
		if (s->firstfree == s->cap)
		{
			//full
			reallocate_private_string(s, capacity_string(s) * 2);
		}
		else
		{
			//return s;
		}
	}
	else
	{
		//return NULL;
	}
}
int *create_nextarray_usedinKMP_private_string(char *p, int size)
{
	int *next = (int*)malloc(sizeof(int)*size);

	next[0] = -1;

	int j = 0;

	int k = -1;

	while (j < size - 1) {

		if (k == -1 || p[j] == p[k]) {

			next[++j] = ++k;

		}
		else {

			k = next[k];

		}

	}
	for (int i = 0; i < size; ++i)
		printf("\n%d", next[i]);
	return next;
}
//end
//从指定的串中复制得到新串
String strcopy_string(String source)
{
	String s = create_string('\0', size_string(source));
	copy_from_private_string(source->first, source->firstfree, s->first, s->cap);
	s->firstfree = s->first + size_string(source);
	return s;
}
//清空所有内容 但是不会回收空间
void clear_string(String s)
{
	//free_private_string(s->data, 0);
	if (!size_string(s))
	{
		*(s->first) = '\0';
		s->firstfree = s->first;
	}

}
//清空所有内容并回收空间
void free_string(String s)
{
	free_private_string(s->first, 1);
	s->cap = s->first = s->firstfree = NULL;
}
//连接字符串 返回一个新的字符串
String union_string(String s1,String s2)
{
	int newsize = size_string(s1) + size_string(s2);
	String h=create_string('\0', newsize*2);
	copy_from_private_string(s1->first, s1->firstfree, h->first, h->cap);
	copy_from_private_string(s2->first, s2->firstfree, h->first+size_string(s1), h->cap);
	h->firstfree = h->first + newsize; return h;
}
//截取一段字符串
String substring_string(String so, Position pos, Position end)
{
	String s = create_string('\0', end-pos);
	copy_from_private_string(so->first+pos, so->first+end, s->first, s->cap);
	s->firstfree = s->first + end - pos;
	return s;
}
//替换字符串的某段内容
void replace_string(String s, Position pos = 0);
//寻找第一个匹配的字符串的首字符位置
int find_string(String match, String source,Position startindex=0)
{
	//朴素模式匹配
	int i = startindex;
	int j = 0;//子字符串的起始位置
	while (i<=size_string(source)-size_string(match))// 保证子字符串的长度不大于开始搜索的长度
	{
		if (*(source->first + i) == *(match->first + j))
		{
			if (j == size_string(match) - 1)
			{
				//okay done
				return i - j;
			}
			++i; ++j;
		}
		else
		{
				//re
				i = i - j + 1;
				j = 0;
		}
	}
	return -1;
}
int find_string_KMP(String match, String source, Position start = 0)
{
	create_nextarray_usedinKMP_private_string(match->first, size_string(match));
	return 0;
}
//在某个点插入字符
void insert_string(String s, char c,Position beg)
{
	check_insertOperation_private_string(s);
	if (beg <= size_string(s)-1)
	{
		int lastindex = size_string(s) - 1;
		char *cb = s->firstfree;
		s->first[lastindex + 2]='\0';
		while (lastindex >= beg)
		{
			*cb-- = s->first[lastindex--];
		}
		s->first[lastindex] = c;
	}

}
//插入（从后面）
void push_back_string(String s,char c)
{
	check_insertOperation_private_string(s);
	*(s->firstfree) = c;
	++(s->firstfree);
	*(s->firstfree) = '\0';
}
//删除某一段的字符串内容
void delete_string(String s, Position beg, Position end);