#include <iostream>
using namespace std;


#define N 100000

int Wi[N];
int Hi[N];
int K;
int n;
int isok(int w)
{
    int sum = 0;
    for(int i=0;i<n;++i)
    {
        sum += (Hi[i] / w)* (Wi[i] / w);
        if(sum >= K)
            return true;
    }
    return false;
}
int main()
{
    cin >> n >> K;
    for(int i = 0; i<n;++i)
    {
        cin >> Wi[i] >> Hi[i];
    }
    int l = 0, h=100000;
    int ans;
    while(l <= h)
    {
        ans = (l + h) / 2;
        if(isok(ans))
            l = ans + 1;
        else
        {
            h = ans - 1;
        }
        
    }
    ++l;
    // ans 最大能够放的大小. l 可能包含解
    while(l--)
    {
        if(isok(l))
            break;
    }
    cout << l;
    return 0;
}

