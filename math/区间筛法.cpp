#include "stdio.h"
//thinking from http://www.cnblogs.com/nowandforever/p/4515612.html
//区间筛法 需要求出区间[a...b)的所有素数
/*
原理: 判断是否是素数可以判断从2...sqrt(n)是否可以被n整除(筛第一遍) 然后用筛法将[a...sqrt(b)]范围内的整数倍剔除
*/
#define N 5000
bool prime[N];//存放大的素数
bool prime_small[N];//存放修建的素数
//判断是否是素数
bool isprime(int n)
{
	for (int i = 2; i*i <= n; ++i)
	{
		if (n % i == 0)
			return false;
	}
	return true;
}
//筛选结果从i..u存放 
void getPrime(int l, int u)
{
	//注意 需要进行偏移 第i个素数存放在i-l的位置
	//求出范围内[l...u)的素数
	//先筛第一遍
	for (int i = 0; i*i <= u; ++i) prime_small[i] = 1;//默认全是素数
	for (int i = 0; i<u - l; ++i) prime[i] = 1;
	for (int i = 2; i*i <= u; ++i)
	{
		if (isprime(i))
		{
			for (int j = i * 2; j*j <= u; j = j + i) prime_small[j] = 0;
			int multi = 2;//默认的倍数
			//int calc = (l + i - 1) / i;
			int calc = ((l + i) % i == 0 ? ((l + i - 1) / i) : (l + i) / i);//得到与l 最接近的倍数 最小的倍数必须是2 设这个倍数是d   d*i >=l+i-1 d>=(l+i-1) / i   考虑l+i能整除i的情况,若整除 需要减少一个倍数 随意被除数-1就可以缩小一倍;如不整除-1有不有也无妨
			//但是第一个式子简洁一些
			if (calc > multi)
				multi = calc;
			for (int j = i * multi; j<u; j = j + i) prime[j - l] = 0;
		}

	}
	for (int i = 0; i < u - l; ++i)  //统计个数
		if (prime[i])
			printf("%d ", i + l);
}
int main()
{
	getPrime(20,500);
}
