#include <iostream>
using namespace std;
// https://blog.csdn.net/kangyan__/article/details/69908833

int baozi[100];  // 表示笼屉放包子的数量
const int MAX_W = 100 * 100 + 10;
bool dp[MAX_W];// 完全背包的数组
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a%b);
}

int main()
{
    int n;
    cin >> n;
    for(int i=0;i<n;++i)
        cin >> baozi[i];
    // 目前凑包子
    // 每个数字之间
    int g = baozi[0];
    for(int i=1;i<n;++i)
    {
        // 一旦不互质, 就会出现有除数出现在 g 的情况
        g = gcd(g, baozi[i]);// g 最后要等于 = 1
    }
    if(g != 1)
    {
        cout << "INF";
        return 0;
    }
    // 完全背包问题
    dp[0] = true;// 
    for(int i=0;i<n;++i)
    {
        for(int w = 0; w + baozi[i] < MAX_W;++w)
        {
            if(dp[w])// 只要之前的包子能够凑出来, 那么之后+当前容量的笼屉的包子数量一定是可以凑出来的.
            {
                dp[w + baozi[i]] = true;
            }
        }
    }
    int ans = 0;
    for(int i=0;i < MAX_W;++i)
        if(!dp[i])
            ++ans;
    cout << ans;
    return 0;
}