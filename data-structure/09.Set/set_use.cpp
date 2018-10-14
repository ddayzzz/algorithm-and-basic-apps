#include "../Set.hpp"
int main()
{
    VectorSet set1(7);
    VectorSet set2(7);
    VectorSet set3(7);
    set1.add(1);
    set1.add(3);
    set1.add(5);
    set1.add(6);
    set2.add(1);
    set2.add(2);
    set2.add(3);
    cout << set1;
    cout << set2;
    cout << set3;
    cout << set1 + set2;
    cout << set1 - set2;
    ListSet<int> ls, ls2;
    ls.add(1);
    ls.add(3);
    ls.add(88);
    ls2.add(8);
    ls2.add(1);
    ls2.add(3);
    ls2.add(88);
    bool l = ls2 == ls;
    ListSet<int> ls3(ls);
    cout << "---------------------------\n";
    cout << "集合ls：" << ls << "集合ls2：" << ls2 << "集合ls3：" << ls3;
    cout << "ls并ls2" << ls + ls2;
    cout << "ls3-ls交ls2" << ls3 - ls * ls2;
}