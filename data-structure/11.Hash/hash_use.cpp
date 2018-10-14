#include "../stdafx.h"
#include "../Hash.hpp"
#include <cstring>
int main()
{
    string keys[] = {
        "auto", "amd", "alike",
        "bbc", "big",
        "city", "cinema", "crime",
        "double",
        "zippod",
        "feature"};
    int sz = sizeof(keys) / sizeof(keys[0]);
    const int MAXSIZE = 101;
    int count[MAXSIZE];
    memset(count, 0, MAXSIZE * sizeof(int));
    int pos;
    for (int i = 0; i < sz; ++i)
    {
        pos = BKDRHash(keys[i], MAXSIZE);
        count[pos]++;
    }
    cout << "BKDR Hash函数处理：\n";
    for (int i = 0; i < sz; ++i)
    {
        pos = BKDRHash(keys[i], MAXSIZE);
        cout << keys[i] << "  Position is " << pos << "  HASH ID IS : " << count[pos] << endl;
    }
    cout << "\nFNV Hash函数处理：\n";
    for (int i = 0; i < sz; ++i)
    {
        cout << "单词\"" << keys[i] << "\" Hash的位置是" << std::hex << std::showbase << FNV1A_32_Hash(keys[i]) << endl;
    }
    cout << "\nFNV Hash(优化版本)函数处理：\n";
    for (int i = 0; i < sz; ++i)
    {
        cout << "单词\"" << keys[i] << "\" Hash的位置是" << std::hex << std::showbase << FNV1A_32_Hash_Optimize(keys[i]) << endl;
    }
}