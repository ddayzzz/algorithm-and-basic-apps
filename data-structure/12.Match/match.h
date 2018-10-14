#pragma once
#include "../stdafx.h"
#include <string>
#include <iostream>
#include <stack>
#include <vector>
int *getMPNextarray(std::string pattern)
{
	int *arr = new int[pattern.size()+1];
	int i, j;
	i = 0;
	j = arr[0] = -1;
	while (i < pattern.size())
	{
		while (j > -1 && pattern[j] != pattern[i])
		{
			j = arr[j];//将j退回到arr[0]的位置也就是-1 需要重新进行判断 同时while后面的语句会将j加到0 就可以把下一位置（i）改为0 因为不论是否有匹配还是k=0 mpnext一律为0
		}
		arr[++i] = ++j;//j保存的是i前一个位置的最大的k 所以需要自加一次
	}
	return arr;
}
int doMP(std::string s, std::string p)
{
	int *u = getMPNextarray(p);
	for (int j = 0; j <= p.size(); ++j)
		std::cout << u[j] << std::endl;

	int i = 0;
	int j = 0;
	while (i < s.size())
	{

		while (j > -1 && s[i] != p[j])
			j = u[j];//总是将j移动到最匹配的那个k的位置 然后判断与s[i]是否相等 如果相等 那么i++ j++ 如果还是不相等 那么循环继续 知道j==p.size -1 表示匹配或者不断循环至i最大 j=0 返回-1
		++j;
		++i;
		if (j >= p.size())
		{

			int res = i - j;
			j = u[j];
			return res;
		}
	}
	
	delete[] u;
	return -1;
}
static int* getKMPNext(std::string  ps) {

	

	int* next = new int[ps.size()+1];
	int i = 0;
	int j = next[0] = -1;
	while (i < ps.size())
	{
		while (j > -1 && ps[i] != ps[j])
		{
			j = next[j];
		}
		if (ps[++i] == ps[++j])
		{
			next[i] = next[j];
		}
		else
		{
			next[i] = j;
		}
	}
	return next;

}
int doKMP(std::string s, std::string p)
{
	int *u = getKMPNext(p);
	for (int j = 0; j <= p.size(); ++j)
		std::cout << u[j] << std::endl;
	int i = 0;
	int j = 0;
	while (i < s.size())
	{

		while (j > -1 && s[i] != p[j])
			j = u[j];//总是将j移动到最匹配的那个k的位置 然后判断与s[i]是否相等 如果相等 那么i++ j++ 如果还是不相等 那么循环继续 知道j==p.size -1 表示匹配或者不断循环至i最大 j=0 返回-1
		++j;
		++i;
		if (j >= p.size())
		{

			int res = i - j;
			j = u[j];
			return res;
		}
	}

	delete[] u;
	return -1;
}
int *getBMbclist(const char* c, int size)
{
	//找到一个好后缀
	int *arrs = new int[256];
	for (int i = 1; i <= 256; ++i)
	{
		arrs[i - 1] = size;
	}
	for (int i = 0; i < size; ++i)
	{
		arrs[c[i]] = size - 1 - i;
	}
	return arrs;
}/*
void suffix(const char *pattern, int m, int suff[])
{
	int i, j;
	int k;

	suff[m - 1] = m;

	for (i = m - 2; i >= 0; i--)
	{
		j = i;
		while (j >= 0 && pattern[j] == pattern[m - 1 - i + j]) j--;

		suff[i] = i - j;
	}
}
void PreBmGs(const char *pattern, int m, int bmGs[])
{
	const int SIZE = 256;
	int i, j;
	int suff[SIZE];

	// 计算后缀数组
	suffix(pattern, m, suff);

	// 先全部赋值为m，包含Case3
	for (i = 0; i < m; i++)
	{
		bmGs[i] = m;
	}

	// Case2
	j = 0;
	for (i = m - 1; i >= 0; i--)
	{
		if (suff[i] == i + 1)
		{
			for (; j < m - 1 - i; j++)
			{
				if (bmGs[j] == m)
					bmGs[j] = m - 1 - i;
			}
		}
	}

	// Case1
	for (i = 0; i <= m - 2; i++)
	{
		bmGs[m - 1 - suff[i]] = m - 1 - i;
	}
}
*/
int returnMatchedsubfix(const char *pattern, int size, int index_fromright)
{
	int *arr = new int[size];
	//好好想想
	return 0;
}
int *getBMgslist(const char *pattern, int size)
{
	return NULL;
}


int *getBMH_badchar_list(const char *cha,int size)
{
	//坏字符偏移函数
	const int SIZE = 256;
	int *pianyi = new int[SIZE];
	for (int i = 1; i <= SIZE; ++i)
	{
		pianyi[i - 1] = size;
	}
	for (int i = 0; i < size-1; ++i)
	{
		pianyi[cha[i]] = size - 1 - i;
	}
	return pianyi;
}
int find_using_BMH(const char *t, const char *p, int ts, int ps)
{
	if (ts < ps) { return -1; }
	int k = ps - 1;
	int *bmhbc = getBMH_badchar_list(p, ps);
	while (k < ts)
	{
		int j = ps - 1;
		int i = k;
		while (j >= 0 && t[i] == p[j])
		{
			j--;
			i--;
		}
		if (j == -1)
			return i + 1;
		k = bmhbc[t[k]] + k;
	}
	return -1;
}

//模糊匹配
int max(int a, int b) { return a > b ? a : b; }
int** draw_dw_alogrithms(const char *c1,const char *c2,int size_c1,int size_c2)
{
	int **martix = new int*[size_c1+1];
	for (int i = 1; i <= size_c1+1; ++i)
		martix[i - 1] = new int[size_c2+1];
	martix[0][0] = 0;
	for (int x = 1; x < size_c2 + 1; ++x)
		martix[0][x] = martix[0][x - 1] - 1;
	for (int y = 1; y < size_c1 + 1; ++y)
		martix[y][0] = martix[y - 1][0] - 1;
	for (int i = 1; i < size_c1 + 1; ++i)
	{
		for (int j = 1; j < size_c2 + 1; ++j)
		{
			int zuo = martix[i][j - 1];
			int shang = martix[i - 1][j];
			int zuoshang = martix[i - 1][j - 1];
			if (c1[i-1] == c2[j-1])
				zuoshang++;
			else
				zuoshang--;
			martix[i][j] = max(max(zuo - 1, shang - 1), zuoshang);
		}
	}
	return martix;
}
class point
{
public:
	point(int ix,int iy):x(ix),y(iy){}
private:
	int x, y;
};
class opsandnum
{
public:
	enum OPS{LEFT=0,LEFTANDUP=2,UP=4};
	opsandnum(OPS o,int x,int y):ops(o),pt(x,y){}
private:
	char ops;
	point pt;
};
void add(const char* c1,const char *c2,int** pattern,std::vector<opsandnum> &op, int i, int j)
{
	if (i == 0 || j == 0)
	{
		return;
	}
	int zuoshang = pattern[i - 1][j - 1];
	if (c1[i-1] == c2[j-1])
	{
		
		zuoshang++;
	}
	else { zuoshang--; }
	int zuo = pattern[i][j - 1]-1;
	int shang = pattern[i - 1][j]-1;
	int currv = pattern[i][j];
	if (shang == currv)
	{
		op.push_back(opsandnum(opsandnum::UP, i, j));
		add(c1,c2,pattern, op, i - 1, j);
	}
	if (zuo == currv)
	{
		op.push_back(opsandnum(opsandnum::LEFT, i, j));
		add(c1,c2,pattern, op, i, j-1);
	}
	if (zuoshang == currv)
	{
		op.push_back(opsandnum(opsandnum::LEFTANDUP, i, j));
		add(c1,c2,pattern, op, i - 1, j - 1);
	}
	
}
void huisu_mohu_alogrithms(const char* c1, const char *c2, int size_c1, int size_c2)

{
	int **draw = draw_dw_alogrithms(c1, c2, size_c1, size_c2);
	for (int i = 0; i < size_c1 + 1; ++i)
	{
		for (int j = 0; j < size_c2 + 1; ++j)
		{
			printf("%3d", draw[i][j]);
		}
		putchar('\n');
	}
	//for (int i = 0; i < size_c1 + 1; ++i)
		//delete[] draw[i];
	//delete[] draw;
	//回溯法求路径
	int i = size_c2;//列
	int j = size_c1;//行
	std::vector<opsandnum> vec;
	//std::stack<decltype(vec)> sta(vec);
	add(c1,c2,draw, vec, size_c1, size_c2);
}