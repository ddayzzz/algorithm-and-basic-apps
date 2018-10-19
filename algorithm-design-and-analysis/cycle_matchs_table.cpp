#include <iostream>
#include <iomanip>

using namespace std;
int WIDTH = 4;
int T;
void Table(int n,int k, int **a)
{
	// a 是二维数组, k是选手的数量
	// 对于n个选手, 总共交换 k=log2(n) 次
	for (int i = 1; i <= n; ++i)
		a[1][i] = i; // 填充第一行


		
	int m = 1; // m 是外循环用来控制
	for (int s = 1; s <= k; ++s)
	{
		n /= 2; // 用于控制交换次数, 代替了取对数的方式.
		for (int t = 1; t <= n; ++t)
		{
			for (int i = m + 1; i <= 2 * m; ++i)// 控制行。*2是因为每一个兑换过程中，被交换的起始位置是交换的2倍的增长
			{
				for (int j = m + 1; j <= 2 * m; ++j) // 控制列
				{
					a[i][j + (t - 1)* m * 2] = a[i - m][j + (t - 1)*m * 2 - m];
					a[i][j + (t - 1) * m * 2 - m] = a[i - m][j + (t - 1)*m * 2];
                    // for(int o=1;o<=T;++o)
                    // {
                    //     for(int p=1;p<=T;++p)
                    //     {
                    //         if(a[o][p] == -1)
                    //             cout << setw(WIDTH) << "-";
                    //         else
                    //             cout << setw(WIDTH) << a[o][p];
                    //     }
                    //     cout << endl;
                    // }
                    // cout <<  "-----------------------------------"<<endl;
				}
			}
		}
		m *= 2;
	}
}
int main()
{
	int num_comper;
	int k=0, n=0;
	cout << "请输入选手的数量:";
	cin >> num_comper;
	n = T = num_comper;
	// 计算k
	while (n > 1)
	{
		++k;
		n /= 2;
	}
	int **table = new int*[num_comper + 1];
	for (int i = 0; i <= num_comper; ++i)
	{
		table[i] = new int[num_comper + 1];
        for(int j=0;j<= num_comper;++j)
        {
            table[i][j] = -1;
        }
	}
	Table(num_comper, k,table);
	for (int i = 1; i <= num_comper; ++i)
	{
		for (int j = 1; j <= num_comper; ++j)
		{
			cout << setw(WIDTH) << table[i][j];
		}
		cout << endl;
	}
	for (int i = 0; i <= num_comper; ++i)
	{
		delete[] table[i];
	}
	delete[] table;
}