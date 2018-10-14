#pragma once
#include "../stdafx.h"
#include <cstdlib>
struct S
{
	char *first;//����ָ���һ���ַ���ָ��
	char *firstfree;//����ָ�����һ���ַ���β��λ��
	char *cap;//����ָ������ڴ��δ��ַ
};
typedef S *String;
typedef int Position;
const unsigned int DEFAULT_SIZE = 20;//Ĭ�ϵ��ַ���С
const char DEFAULT_CHAR = '\0';//Ĭ�ϵ�����ַ�
/*
	cap-first ������
	firstfree-first �ǵ�ǰ�ַ����Ĵ�С
*/
void reallocate_private_string(String sou, Position newsize);
void free_private_string(char *s, int freespace);
char *copy_from_private_string(char *source, char *end1, char *dest, char *cap);

//����������С
Position capacity_string(String s) {
	if (s)
	{
		return s->cap - s->first;
	}
	return 0;
}
//�����ַ�����С
Position size_string(String s) {
	if (s)
	{
		return s->firstfree - s->first;
	}
	return 0;
}
//�����ƶ���С���ַ���
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
//˽�к�����
//�������·���һ���µĿռ����ڴ洢char����
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
//�ͷŻ�����ַ�����
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
//�ṩ���ڵײ����ݵĲ���
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
//����������Ƿ�Ϸ� ������������� ��ô���·���
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
//��ָ���Ĵ��и��Ƶõ��´�
String strcopy_string(String source)
{
	String s = create_string('\0', size_string(source));
	copy_from_private_string(source->first, source->firstfree, s->first, s->cap);
	s->firstfree = s->first + size_string(source);
	return s;
}
//����������� ���ǲ�����տռ�
void clear_string(String s)
{
	//free_private_string(s->data, 0);
	if (!size_string(s))
	{
		*(s->first) = '\0';
		s->firstfree = s->first;
	}

}
//����������ݲ����տռ�
void free_string(String s)
{
	free_private_string(s->first, 1);
	s->cap = s->first = s->firstfree = NULL;
}
//�����ַ��� ����һ���µ��ַ���
String union_string(String s1,String s2)
{
	int newsize = size_string(s1) + size_string(s2);
	String h=create_string('\0', newsize*2);
	copy_from_private_string(s1->first, s1->firstfree, h->first, h->cap);
	copy_from_private_string(s2->first, s2->firstfree, h->first+size_string(s1), h->cap);
	h->firstfree = h->first + newsize; return h;
}
//��ȡһ���ַ���
String substring_string(String so, Position pos, Position end)
{
	String s = create_string('\0', end-pos);
	copy_from_private_string(so->first+pos, so->first+end, s->first, s->cap);
	s->firstfree = s->first + end - pos;
	return s;
}
//�滻�ַ�����ĳ������
void replace_string(String s, Position pos = 0);
//Ѱ�ҵ�һ��ƥ����ַ��������ַ�λ��
int find_string(String match, String source,Position startindex=0)
{
	//����ģʽƥ��
	int i = startindex;
	int j = 0;//���ַ�������ʼλ��
	while (i<=size_string(source)-size_string(match))// ��֤���ַ����ĳ��Ȳ����ڿ�ʼ�����ĳ���
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
//��ĳ��������ַ�
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
//���루�Ӻ��棩
void push_back_string(String s,char c)
{
	check_insertOperation_private_string(s);
	*(s->firstfree) = c;
	++(s->firstfree);
	*(s->firstfree) = '\0';
}
//ɾ��ĳһ�ε��ַ�������
void delete_string(String s, Position beg, Position end);