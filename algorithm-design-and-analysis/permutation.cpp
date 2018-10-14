#include <iostream>
#include <utility>
using namespace std;


template<typename T>
void Perm(T list[], int k, int m)
{
    if(k == m)
    {
        for(int i=0;i<=m;++i)
        {
            cout << list[i];
        }
        cout <<endl;
    }
    else
    {
        for(int i=k;i<=m;++i)
        {
            swap(list[k], list[i]);
            Perm(list, k+1,m);
            swap(list[k], list[i]);
        }
    }
}
int main()
{
    int a[]={1,2,3};
    Perm(a,0,2);
}