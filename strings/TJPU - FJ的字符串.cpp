#include <string>
#include <iostream>
#include <vector>
using namespace std;
int main()
{
	vector<string> vec(27);
	vec[1] = string("A");
	int n;
	cin >> n;
	for (int i = 2; i <= n; ++i)
	{
		string res = vec[i - 1];
		res.push_back('A' + i - 1);
		res.append(vec[i - 1]);
		vec[i] = res;
	}
	cout << vec[n];
	return 0;
}
