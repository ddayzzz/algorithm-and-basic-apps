#pragma once
#include "../stdafx.h"
#include <map>
#include <string>
#include <vector>
#include <cstring>
//����ת�ַ���
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
//�ַ���ת����
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
//ƥ���ַ��� ����������������ַ������ֵĴ���(��������)
//��һ���㷨 ���ַ����ֽ�Ϊ�Ӵ� ͳ���Ӵ����ֵĴ���
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
//�����������ַ������ֵ����ĸ���
int do_getLinkedMaxSubString(std::string &str,int step,std::vector<std::string> &matched)
{
	int i = 0;
	int  maxcount = 0;
	int currcount = 1;
	int sz = str.size();
	std::string temp,nextstr;
	while (i + step - 1 < sz)//��֤����Խ��
	{
		temp = str.substr(i, step);
		nextstr = str.substr(i + step, step);//��ǰ��ȡ ��ȡ������ͬһ���ַ���
		if (nextstr == temp)//�����ǰ���ַ�������һ����ͬ
		{
			i = i + step;//����һ��������ʼ��������ͬ���ַ���λ�ã�
			++currcount;//��ǰ�ַ������ֵĴ���+1
		}
		else
		{
			++i;//�ƶ���һ��λ�ã������¼���
			currcount = 1;
		}
		if (currcount >= maxcount)
		{
			if (currcount == maxcount)
				matched.push_back(temp);//������ͬ���ִ������ַ���
			else
			{
				matched.clear();//���֮ǰ�ı������ַ���
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
		if (n > maxcount)//��ֻҪ�����������ֵ��ַ���
		{
			maxcount = n;
			res = s;
		}
	}
	return maxcount;
}
//�������ͬ�ҳ�������ַ�����������ģ� p247
int get_MaxCommonString(std::string s,std::string &r)
{
	std::string tmp;
	int i;
	for (i = s.size(); i >= 0; --i)
	{
		for (int j = 0; j < s.size(); ++j)
		{
			if (j + i < s.size())//i���Ͻ� j��ʾ�½�
			{
				size_t t = 0;
				size_t num = 0;
				tmp = s.substr(j, i);//��ȡ��ȡ�ķ�Χ
				t = s.find(tmp);//��������Ѱ��
				num = s.rfind(tmp);//��ĩβѰ��
				if (t != num)//�����������ͬ��λ��
				{
					r = tmp;
					return t + 1;//����λ��
				}
			}
		}
	}
	return -1;
}
//����ƥ������ַ������ֵ�λ�� �����س��ֵ�λ�� ��ʵ��������ģʽƥ��
int my_strstr(std::string s1,std::string s2)
{
	int i;
	for (i = 0; i < s1.size();++i)
	{
		if (i > s1.size() - s2.size())
			break;//s1����Ҫ���㹻�ĳ���
		int j = 0;
		int t = i;//��¼��ʼ��λ��
		for (; j < s2.size(); ++j)
		{
			if (s1[i] != s2[j])//������������i
			{
				i = t;
				break;
			}
			++i;
		}
		if (j >= s2.size())//�����ȫƥ��
			return i - j;
	}
	return -1;
}
//�ַ�����ת ��һ�������巴ת �ڶ��������ʲ��ַ�ת
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
	int temp = 0;//��¼�����ո�����г�ʼ��λ��
	while (i < s.size())
	{
		if (s[i] != ' ')
			++i;
		else
		{
			std::string m = s.substr(temp, i - temp);//��ʱ��ȡҪ�滻��λ��
			do_reverse(m);//��ת����
			s.replace(temp, i - temp, m);//�滻ԭ���ĵ���
			temp = temp + m.size()+1;
			i = temp;//�޸���һ�γ�ʼ������
			
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
//���ֵ��ַ�ͳ���㷨
std::string countCharStr(const char* s)
{
	int i = 0;
	int size = strlen(s);
	std::string res;
	char *max = new char[size * 2];
	//char *max = (char*)malloc(sizeof(char)*size * 2);
	max[0] = '\0';//��ֹ��һ������
	int count = 1;
	for (; i <size;++i)
	{
		if (s[i] == s[i + 1])
		{
			++count;//���������ַ���ǰ����ַ����
		}
		else
		{
			sprintf(max + strlen(max), "%c%d", s[i], count);//���ĺ�����ܻ�������������. sprintf���Զ����\0 ����д��\0
			count = 1;//���¼���
		}
	}
	if (s[i - 1] != s[i])//������һ���ַ��뵹����һ���ַ�����ͬ ��ô��������ַ�ֻ�����һ�� �������ͬ�Ļ� �Ͳ���Ҫ������
		count = 1;
	sprintf(max + strlen(max), "%c%d", s[i], count);
	res = max;
	delete[] max;//ɾ��
	//free(max);
	return res;
}
//�ַ�ƫ��
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