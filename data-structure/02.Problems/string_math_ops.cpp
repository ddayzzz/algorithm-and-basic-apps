//计算工具函数 大数 + * 
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
//数字的分解（int to char[])
std::string InttoString(int tmp)
{
	int weight = 10;
	std::string s;
	while (tmp)
	{
		int a = tmp % weight;
		a = a / (weight / 10);
		s.insert( s.begin(),char(a + 48));
		tmp = tmp - a*(weight/10);
		weight *= 10;
		
	}
	return s;
}
int makeZHENGQI_ANDREVERSE(std::string &s1, std::string &s2)
{
	int maxcnt = (s1.size() > s2.size() ? s1.size() : s2.size()) + 1;
	if (s1.size() > s2.size())
	{
		//s2
		int cnt = s1.size() - s2.size();
		for (; cnt > 0; --cnt)
		{
			s2.insert(s2.begin(), '0');
		}
	}
	else
	{

		if (s2.size() > s1.size())
		{
			//s1
			int cnt = s2.size() - s1.size();
			for (; cnt > 0; --cnt)
			{
				s1.insert(s1.begin(), '0');
			}
		}

	}
	//反
	/*
	int cnt = maxcnt - 1;
	int li = cnt - 1;
	cnt /= 2;
	int i = 0;
	while (cnt > 0)
	{
		int t = s1[i];
		s1[i] = s1[li];
		s1[li] = t;
		t = s2[i];
		s2[i] = s2[li];
		s2[li] = t;
		++i;
		--li;
		--cnt;
	}
	*/
	//使用标准库算法
	std::reverse(s1.begin(), s1.end());
	std::reverse(s2.begin(), s2.end());
	s1.push_back('0');
	s2.push_back('0');
	return maxcnt;
}
std::string bigadd(std::string s1, std::string s2)
{
	std::string res;
	int max = makeZHENGQI_ANDREVERSE(s1, s2);
	int flag = 0;
	for (int i = 0; i < max; ++i)
	{
		int add = s1[i]-48 + s2[i]-48;
		add = add + flag;
		res.push_back(add % 10 + 48);
		flag = add / 10;
	}
	if (res.back() == '0')
	{
		res.pop_back();
	}
	std::reverse(res.begin(), res.end());
	return res;
}
std::string bigmultiply(std::string s1, std::string s2)
{
	std::reverse(s1.begin(), s1.end());
	std::reverse(s2.begin(), s2.end());
	std::string res;
	int maxsz = s1.size() + s2.size();
	for (int s = 0; s < maxsz; ++s) res.push_back('0');
	int i, j;
	for (i = 0; i < s1.size(); ++i)
	{
		int addflag = 0;
		int multiplyflag = 0;
		for (j = 0; j < s2.size(); ++j)
		{
			int cheng = (s1[i] - '0')*(s2[j] - '0');
			cheng = cheng + multiplyflag;
			int add = res[i + j] - '0' + cheng % 10 + addflag;
			res[i + j] = add % 10 + '0';
			addflag = add / 10;
			multiplyflag = cheng / 10;
		}
		res[i + j] = res[i + j] - '0' + multiplyflag +addflag+ '0';
	}
	if (res.back() == '0')
	{
		res.pop_back();
	}
	std::reverse(res.begin(), res.end());
	return res;
}
//显示阶乘
void display_factorize(int s)
{
	std::vector<string> str;
	for (int i = 1; i <= s; ++i)
	{
		if (i == 1)
		{
			str.push_back(string("1"));
			cout << "1!=1" << endl;
		}
		else
		{
			string tmp = bigmultiply(str[i - 2], InttoString(i));
			str.push_back(tmp);
			cout << i << "!=" << tmp << endl;
		}
	}
}
void output_factorize(int s)
{
	std::vector<string> str;
	std::ofstream of("FACT.TXT");
	for (int i = 1; i <= s; ++i)
	{
		if (i == 1)
		{
			str.push_back(string("1"));
			of << "1!=1" << endl;
		}
		else
		{
			string tmp = bigmultiply(str[i - 2], InttoString(i));
			str.push_back(tmp);
			of << i << "!=" << tmp << endl;
		}
	}
}
int main()
{
    output_factorize(5);
}