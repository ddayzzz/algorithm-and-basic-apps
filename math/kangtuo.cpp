
#include <iostream>

using namespace std;
using ll = long long;
ll fact[11];
void factor()
{
	fact[0] = fact[1] = 1;
	for (int j = 2; j <= 10; ++j)
	{
		fact[j] = fact[j - 1] * j;
	}
}
bool flag[10];
int main()
{
	// 使用逆康托展开
	factor(); // 初始化
	int n, r, t, j, l;
	int init = 10;
	cin >> n;
	n--;

	do {
		--init;
		if (init < 0)
			break;
		t = n / fact[init]; // 这个是商, 表示有几个数字 < 他
		r = n % fact[init]; // 这个是余数
		// 查找是否已经标记了
		// 注意， 比t个大的是要忽略掉已经被标记的数字。纯标记是无用的，因为下一个未标记的位置不一定会比所有的 t 大
		// 需要定义另外的索引， 用来记录出现第一个可用的位置的次数

		for (j = 1, l = 0; l <= t; ++j)
		{
			if (!flag[j])
				++l;
		}
		flag[--j] = true;
		cout << j - 1;
		n = r;
	} while (true);
	cout << endl;
	return 0;
}