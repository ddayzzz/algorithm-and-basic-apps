#include <iostream>
#include <algorithm>
// 折半搜索
// POJ 2785
using namespace std;
const int MAX_N = 4000;
int n;
int A[MAX_N], B[MAX_N], C[MAX_N], D[MAX_N];
int CD[MAX_N * MAX_N];  // C 和 D数组组合

void solve()
{
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            CD[i*n+j] = C[i] + D[j];
        }
    }
    // 计算好 C 和 D 的和. 通过二维数组的压缩, 压缩为一维数组
    sort(CD, CD+ n * n);
    long long res = 0;
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            int cd = -(A[i] + B[j]);
            res += upper_bound(CD, CD + n*n, cd) - lower_bound(CD, CD + n*n, cd); // 区间的长度
        }
    }
    cout << res;
}
int main()
{
    cin >> n;
    for(int i=0;i < n;++i)
    {
        cin >> A[i] >> B[i] >> C[i] >> D[i];
    }
    solve();
}