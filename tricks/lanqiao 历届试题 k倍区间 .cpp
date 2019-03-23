#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

#define N 100000
#define K 100000

typedef long long ll;

int Ai[N];
ll sum[N+1]; // 默认带有0
ll cnt[N+1]; // 前缀数组, 如果 (sum[j] - sum[i]) % k == 0 如果有能够连续的前缀
int main()
{
    int n, k;
    cin >> n >> k;
    ll ans = 0;
    for(int i=0;i<n;++i)
    {
        // 
        cin >> Ai[i];
        sum[i] = (sum[i-1] + Ai[i]) % k;
        ans += cnt[sum[i]];
        ++cnt[sum[i]];
    }
    // 计算 sum (timeout)
    // sum[0] = 0;
    // for(int i=0;i<n;++i)
    // {
    //     sum[i+1] = sum[i] + Ai[i];
    // }
    // for(int i=1;i<n;++i)
    // {
    //     for(int j=i;j<n;++j)
    //     {
    //         if(0 == (sum[j] - sum[i]) % k)
    //             ++count;
    //     }
    // }
    cout << (ans + cnt[0]); // cnt[0] 记录了以 k 开始的倍数的个数
    return 0;
}