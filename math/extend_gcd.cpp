// 扩展欧几里得定理的应用
// https://blog.csdn.net/zhjchengfeng5/article/details/7786595
// https://zh.wikipedia.org/wiki/%E6%89%A9%E5%B1%95%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E7%AE%97%E6%B3%95
#include <iostream>
#include <cstdio>
using namespace std;
//
int gcd(int a, int b)
{
    // 辗转相除法求最大公约数
    return b == 0 ? a : gcd(b, a % b);
}
// 主要是要求不定方程:ax+by=1. 或者还是 ax+by=gcd(a,b).
int exgcd(int a, int b, int &x, int &y)
{
    int d = a;
    // 扩展欧几里得算法的递归形式
    if (b != 0)
    {
        d = exgcd(b, a % b, y, x);
        y -= (a / b) * x;
        
    }
    else
    {
        x = 1;
        y = 0;
    }
    return d;
}
int main()
{
    int a, b;
    int x, y;
    while (scanf("%d%d", &a, &b) != EOF)
    {
        exgcd(a, b, x, y);
        if (gcd(a, b) != 1)
            printf("impossible\n"); // 如果 a b不是互质的, 则 ax+by=1 无解
        else
            printf("%d %d\n", x, y);
    }
    return 0;
}