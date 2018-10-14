
#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
#include <cstring>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
//普通线性筛选法 埃拉托斯特尼筛法

const int MAX = 5000;
int PRIME_FLAGS[MAX];
long PRIME[MAX];
int cnt = 0;

void make_prime()
{
	memset(PRIME_FLAGS, 1, sizeof(PRIME_FLAGS));
	PRIME_FLAGS[0] = 0;
	PRIME_FLAGS[1] = 0;
	for (int i = 2; i < MAX; ++i)
	{
		if (PRIME_FLAGS[i])
		{
			PRIME[cnt++] = i;
			
		}
		for (int k = i*i; k < MAX; k = k + i)
			PRIME_FLAGS[k] = 0;
	}
}
int main()
{
	make_prime();
	for(int i=0;i<cnt;++i)
	{
		if(i % 100 == 0)
		{
			printf("\n");
		}
		printf("%d ", PRIME[i]);
	}
	
	return 0;
}