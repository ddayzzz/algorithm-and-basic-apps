#include "stdio.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
string bignum(string a, string b)
{
	int size = a.size() + b.size();
	int maxsz = size + 1;
	string res(maxsz, '0');
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	int i, j;
	
	for (i = 0; i<a.size(); ++i)
	{
		int add = 0, multi = 0;
		for (j = 0; j<b.size(); ++j)
		{
			int temp = (a[i] - '0') *( b[j] - '0' )+multi;
			multi = temp / 10;
			int add_p = res[i + j] - '0' + temp % 10 + add;
			add = add_p / 10;
			res[i + j] = add_p % 10 + '0';
		}
		res[i + j] = res[i + j] + multi+add;
	}
	if (res.back() == '0')
		res.pop_back();
	reverse(res.begin(), res.end());
	return res;
}
string my_itoa(int o)
{
	string r;
	int fact = 10;
	while (o)
	{
		//r.push_back(o % 10 + '0');
		r.insert(r.begin(), o % 10 + '0');
		o = o / fact;
	}
	return r;
}
int main()
{
	
	int n;
	cin >> n;
	if (n == 1)
	{
		printf("1");
		return 0;
	}
	vector<string> p(n+1);
	p[1] = "1";
	string s;
	for (int i = 2; i <= n; ++i)
	{
		s = my_itoa(i);
		p[i] = bignum(p[i - 1], s);
	}
	bool first = true;
	int i;
	for (i = 0; i < p[n].size()-1; ++i)
	{
		if (p[n][i]=='0' && p[n][i+1] !='0')
		{
			break;
		}
	}
	printf("%s", p[n].c_str() + i + 1);
	return 0;
}
