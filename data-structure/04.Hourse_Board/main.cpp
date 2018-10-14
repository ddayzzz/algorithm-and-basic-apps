#include "../GraphArray.h"
#include <iostream>
using namespace std;


int main()
{
    // 马踏棋盘
    Board bd;

    int x, y;
    cin >> x >> y; // 起始坐标
    //bd.findPath_digui(x, y);//这个是递归法 很慢
    bd.findPath_tanxin(x, y);//这个是贪心算法优化的
    bd.print();

}