#include <iostream>
#include <stack>
using namespace std;

using ll = long long;
int main()
{
    stack<char> cc;
    ll a, b;
    cin >> a >> b;
    ll c = a + b;
    int count = 0;
    bool neg = c < 0;
    bool add = false;
    if (neg)
        c = -c;
    // cout << c << endl;
    if(c == 0)
        {
            cout << 0 << endl;
            return 0;
        }
    while (c)
    {
        if (add)
        {
            cc.push(',');
            add = false;
        }
        char aa = c % 10 + '0';
        c = c / 10;
        if (++count % 3 == 0)
            add = true;
        cc.push(aa);
    }
    if (neg)
        cout << "-";

    while (!cc.empty())
    {
        cout << cc.top();
        cc.pop();
    }

    cout << endl;

    return 0;
}