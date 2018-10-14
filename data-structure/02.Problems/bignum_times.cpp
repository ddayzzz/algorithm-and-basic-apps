#include "string.h"
#include "stdio.h"
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
string bignumplus(string s1, string s2)
{
	if (s1 == "0" || s2 == "0" || s1=="" || s2=="")
		return string("0");
	std::reverse(s1.begin(), s1.end());
	std::reverse(s2.begin(), s2.end());
	int sz = s1.size() + s2.size();
	string res(sz, '0');
	for (int i = 0; i<s1.size(); ++i)
	{
		int addflag = 0;
		int multiflag = 0;
		for (int j = 0; j<s2.size(); ++j)
		{
			int n = (s1[i] - '0')*(s2[j] - '0') + multiflag;
			multiflag = n / 10;
			n = n % 10;
			int m = res[i + j] - '0' + n + addflag;
			addflag = m / 10;
			res[i + j] = m % 10 + '0';
		}
		res[i + s2.size()] = res[i + s2.size()] + multiflag + addflag;
	}
	if (res.back() == '0')
		res.pop_back();
	reverse(res.begin(), res.end());

	return res;
}
bool bigcmp(string s1, string s2)
{
	return s1 > s2;
}
string num(string &s, int beg, int en)
{
	return s.substr(beg-1, en-beg+1);
}
string dp[41][41];
int main()
{
	
	string str;

	int n; int split;
	cin >> n >> split >> str;
	for (int i = 1; i <= 41; ++i)
	{
		for (int j = 0; j <= 41; ++j)
		{
			dp[i][j] = "0";
		}
		dp[i][0] = num(str,1,i);
	}
	int i, j, l;
	for (j = 1; j <= split; j++) {
		for (i = 2; i <= n; i++) {
			for (l = 1; l < i; l++) {
				//[i][j] = max(f[i][j], f[l][j - 1] * num[l + 1][i]);
				string org = dp[i][j];
				string plus = bignumplus(dp[l][j - 1] , num(str, l + 1, i));
				if (plus > org)
					dp[i][j] = plus;
			}
		}
	}
	cout << dp[n][split] << endl;
	int a[][3] = { 1,2,3 };
	int (*p)[3] = a;
}