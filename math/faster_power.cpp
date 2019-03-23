// 快速幂, 挑战程序设计 P123
#include <iostream>
using namespace std;
using ll = long long;

ll mod_pow(ll x, ll n, ll mod)
{
    ll res = 1ll;
    while(n > 0)
    {
        if (n & 1)
            res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}
int main()
{

}