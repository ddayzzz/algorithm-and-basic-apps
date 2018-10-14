#include  "stdio.h"
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
//用来去除大数乘法的末尾的0
void remove_0(string &s)
{
	if (s.back() != '0')
	{
		reverse(s.begin(), s.end());
	}
	else
	{
		int n;
		for (n = s.size() - 1; n>0; --n)
		{
			if (s[n] == '0' && s[n - 1] != '0')
				break;
		}
		if (n == 0)
		{
			s = "0";
		}
		else {
			s = s.substr(0, n);
			reverse(s.begin(), s.end());
		}
	}
}
//大数乘法
string plus1(string s, string s1)
{
	//for big plus
	if (s.size() == 0 || s1.size() == 0)
		return "0";
	string res(s.size() + s1.size(), '0');
	reverse(s.begin(), s.end());
	reverse(s1.begin(), s1.end());
	for (int i = 0; i<s.size(); ++i)
	{
		int add = 0;//乘法进位 
		int pl = 0;//加法进位
		int j;
		for (j = 0; j<s1.size(); ++j)
		{
			int mul = (s[i] - '0')*(s1[j] - '0') + pl;
			pl = mul / 10;
			int aa = mul % 10 + (res[i + j] - '0') + add;
			add = aa / 10;
			res[i + j] = aa % 10 + '0';
		}
		res[i + j] = res[i + j] + pl+add;//末尾必须要加上乘法 加法的进位
	}
	remove_0(res);//除掉0
	return res;
}
//返回的是s从b到e的子字符串
string num(int b, int e, string &s)
{
	//获取s的数值
	return s.substr(b, e - b + 1);
}
//这个是返回按照数学意义的最大的字符串表示的数字的字符串
const string &max1(const string &l, const string &r)
{
	if (l.size() > r.size())
		return l;
	else
	{
		if (l.size() < r.size())
			return r;
		else
		{
			if (l > r)
				return l;
			else return r;
		}
	}
}
string dp[41][7];
