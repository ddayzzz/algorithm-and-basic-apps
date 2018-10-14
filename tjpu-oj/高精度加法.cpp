#include "stdio.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std; 
int main()
{
	string a,b;
	cin>>a>>b;
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());
	int maxsz=(a.size()>b.size() ? a.size(): b.size())+1;
	if(a.size()>b.size())
	{
		b.append(string(a.size()-b.size(),'0'));
	}
	else
	{
		if(a.size() < b.size())
			a.append(string(b.size()-a.size(),'0'));
	}
	string res(maxsz,'0');
	int add=0;
	int j;
	for(j=0;j<b.size();++j)
	{
		int n=res[j]-'0' + b[j]-'0'+add+a[j]-'0';
		int b=n % 10;
		add=b / 10;
		res[j]=b - '0';
	}
	res[j]=res[j]-'0'+add+'0';
	if(res.back()=='0')
		res.pop_back();
	reverse(res.begin(),res.end());
	cout<<res<<endl;
	return 0;
	
} 
