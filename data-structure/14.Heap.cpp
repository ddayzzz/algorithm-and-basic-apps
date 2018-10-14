#include "stdafx.h"
#include "HeapArray.hpp"

int main()
{
    HeapArray<int, bool(int,int)> hn(10, std::greater<int>());
    hn.insert(10);
    hn.insert(40);
    hn.insert(30);
    hn.insert(60);
    hn.insert(90);
    hn.insert(70);
    hn.insert(20);
    hn.insert(50);
    hn.insert(80);
    hn.insert(85);
    hn.insert(90);
    int sz = hn.getSize();
    for (int i = 0; i < sz; ++i)
        cout << hn.TopandPop() << endl;
}