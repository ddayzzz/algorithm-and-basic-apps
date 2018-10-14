#pragma once
#include "../stdafx.h"
#include <map>
#include <string>
#include <vector>
#include <cstring>
//数字转字符串
void my_itoa(int num, char *arr)
{
	int i = 0;
	while (num)
	{
		arr[i++] = num % 10+'0';
		num /= 10;
	}
	arr[i] = '\0';
	int j = i - 1; i = 0;
	while (i < j)
	{
		char temp = arr[j];
		arr[j] = arr[i];
		arr[i] = temp;
		--j;
		++i;
	}
}
//字符串转数字
int my_atoi(char *arr)
{
	int len = strlen(arr);
	int res=0;
	int base=1;
	int k;
	/*
	for (k = 0; k < len; ++k)
		base *= 10;
	for (int i=0; i <len; ++i)
	{
		res = res + (arr[i]-'0') * base;
		base /= 10;
	}
	*/
	for (int i = len - 1; i >= 0; --i)
	{
		res = res + (arr[i] - '0')*base;
		base = base * 10;
	}
	return res;
}
//匹配字符串 正是求非连续的子字符串出现的次数(出现最多的)
//第一个算法 将字符串分解为子串 统计子串出现的次数
void getSubStringCount(int step, std::string str,std::map<std::string, int> &cnts)
{
	int sz = str.size();
	int i = 0;
	std::string temps;
	while (i+step-1 < sz)
	{
		temps = str.substr(i, step);
		cnts[temps]++;
		++i;
	}
}
int getMaxSubStrCount(std::vector<std::string> &res,std::string s)
{
	int maxc=0;
	int i;
	std::map<std::string, int> analysis;
	for (i = 1; i <= s.size(); ++i)
		getSubStringCount(i, s, analysis);
	for (auto i = analysis.cbegin(); i != analysis.cend(); ++i)
	{
		if (i->second > maxc)
			maxc = i->second;
	}
	for (auto i = analysis.cbegin(); i != analysis.cend(); ++i)
	{
		if (i->second == maxc)
		{
			res.push_back(i->first);
		}
	}
	return maxc;
}
//求连续的子字符串出现的最大的个数
int do_getLinkedMaxSubString(std::string &str,int step,std::vector<std::string> &matched)
{
	int i = 0;
	int  maxcount = 0;
	int currcount = 1;
	int sz = str.size();
	std::string temp,nextstr;
	while (i + step - 1 < sz)//保证不会越界
	{
		temp = str.substr(i, step);
		nextstr = str.substr(i + step, step);//向前截取 获取可能是同一个字符串
		if (nextstr == temp)//如果当前的字符串与下一个相同
		{
			i = i + step;//从下一个步长开始（跳过相同的字符串位置）
			++currcount;//当前字符串出现的次数+1
		}
		else
		{
			++i;//移动下一个位置，并重新计数
			currcount = 1;
		}
		if (currcount >= maxcount)
		{
			if (currcount == maxcount)
				matched.push_back(temp);//具有相同出现次数的字符串
			else
			{
				matched.clear();//清除之前的保留的字符串
				matched.push_back(temp);
				maxcount = currcount;
			}
		}

	}
	return maxcount;
}
int getLinkedMaxSubStr(std::string str,std::vector<std::string> &res)
{
	int maxcount = 0;
	int i;
	for (i = 1; i <= str.size(); ++i)
	{
		std::vector<std::string> s;
		int n = do_getLinkedMaxSubString(str, i,s);
		if (n > maxcount)//我只要最大的连续出现的字符串
		{
			maxcount = n;
			res = s;
		}
	}
	return maxcount;
}
//求出现相同且长度最长的字符串（出现最长的） p247
int get_MaxCommonString(std::string s,std::string &r)
{
	std::string tmp;
	int i;
	for (i = s.size(); i >= 0; --i)
	{
		for (int j = 0; j < s.size(); ++j)
		{
			if (j + i < s.size())//i是上界 j表示下届
			{
				size_t t = 0;
				size_t num = 0;
				tmp = s.substr(j, i);//获取截取的范围
				t = s.find(tmp);//从起点出发寻找
				num = s.rfind(tmp);//从末尾寻找
				if (t != num)//如果是两个不同的位置
				{
					r = tmp;
					return t + 1;//返回位置
				}
			}
		}
	}
	return -1;
}
//返回匹配的子字符串出现的位置 并返回出现的位置 其实就是朴素模式匹配
int my_strstr(std::string s1,std::string s2)
{
	int i;
	for (i = 0; i < s1.size();++i)
	{
		if (i > s1.size() - s2.size())
			break;//s1必须要有足够的长度
		int j = 0;
		int t = i;//记录初始的位置
		for (; j < s2.size(); ++j)
		{
			if (s1[i] != s2[j])//如果不相等重置i
			{
				i = t;
				break;
			}
			++i;
		}
		if (j >= s2.size())//如果完全匹配
			return i - j;
	}
	return -1;
}
//字符串翻转 第一步：整体反转 第二步：单词部分反转
void do_reverse(std::string &s)
{
	int i = 0;
	int j = s.size() - 1;
	while (i < j)
	{
		char temp = s[i];
		s[i] = s[j];
		s[j] = temp;
		++i;
		--j;
	}
}
void SpecialFlip(std::string &s)
{
	do_reverse(s);
	int i=0;
	int temp = 0;//记录搜索空格过程中初始的位置
	while (i < s.size())
	{
		if (s[i] != ' ')
			++i;
		else
		{
			std::string m = s.substr(temp, i - temp);//临时截取要替换的位置
			do_reverse(m);//反转单词
			s.replace(temp, i - temp, m);//替换原来的单词
			temp = temp + m.size()+1;
			i = temp;//修改下一次初始的设置
			
		}
	}
}
//sprintf
void sprintf_fcn()
{
	char c[23];
	sprintf(c, "%d", 123);

	printf("%s", c);
}
//出现的字符统计算法
std::string countCharStr(const char* s)
{
	int i = 0;
	int size = strlen(s);
	std::string res;
	char *max = new char[size * 2];
	//char *max = (char*)malloc(sizeof(char)*size * 2);
	max[0] = '\0';//防止第一步出错
	int count = 1;
	for (; i <size;++i)
	{
		if (s[i] == s[i + 1])
		{
			++count;//如果后面的字符与前面的字符相等
		}
		else
		{
			sprintf(max + strlen(max), "%c%d", s[i], count);//他的后面可能会有其他的数据. sprintf会自动添加\0 不用写入\0
			count = 1;//重新计数
		}
	}
	if (s[i - 1] != s[i])//如果最后一个字符与倒数第一个字符不相同 那么这个最后的字符只会出现一次 如果是相同的话 就不需要递增了
		count = 1;
	sprintf(max + strlen(max), "%c%d", s[i], count);
	res = max;
	delete[] max;//删除
	//free(max);
	return res;
}
//字符偏移
void StringMove_01(char* s, int m)
{
	int i = 0;
	int len = strlen(s);
	if (m > len) m = len;
	while (len - m > 0 || (m = 0) != 0)
	{
		for (i = 0, s[len] = s[0], ++m; i < len; ++i)
			s[i] = s[i + 1];
	}
	s[len - m] = '\0';
}