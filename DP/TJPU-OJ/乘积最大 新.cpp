#include "string.h"
#include "stdio.h"
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
string bignumplus(string s1,string s2)
{
	if(s1=="0" || s2=="0")
		return string("0");
	std::reverse(s1.begin(),s1.end());
	std::reverse(s2.begin(),s2.end());
	int sz=s1.size()+s2.size();
	string res(sz,'0');
	for(int i=0;i<s1.size();++i)
	{
		int addflag=0;
		int multiflag=0;
		for(int j=0;j<s2.size();++j)
		{
			int n=(s1[i]-'0')*(s2[j]-'0')+multiflag;
			multiflag=n / 10;
			n=n % 10;
			int m=res[i+j]-'0' + n +addflag;
			addflag=m / 10;
			res[i+j]=m % 10 +'0';
		}	
		res[i+s2.size()]=res[i+s2.size()] +  multiflag + addflag;
	} 
	if(res.back()=='0')
		res.pop_back();
	reverse(res.begin(),res.end());
	
	return res;
}
bool bigcmp(string s1,string s2)
{
	return s1 > s2;
}
string num(string &s,int k,int en)
{
	return s.substr(k,en-k);
}
string dp[41][41];
int main()
{
	string str;
	int n;int split;
	cin>>n>>split>>str;
	for(int i=1;i<=n;++i)
	{
		for(int j=0;j<i;++j)
		{
			for(int k=j;k<i;++k) //k表示的是前i个相乘 
			{
				string org=dp[i][j];
				string plus=bignumplus(dp[k][j-1], num(str,k+1,i));
				if(plus>org)
				{
					dp[i][j]=plus;
				}
			} 
		}
	}
	cout<<dp[n][split]<<endl;
}
