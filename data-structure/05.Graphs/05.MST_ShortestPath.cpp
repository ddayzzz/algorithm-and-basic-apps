#include "../GraphArray.h"
#include <iostream>

using namespace std;
int main()
{
    GraphMartix gr(string("graph_martix.txt"));
    vector<int> ss;
    gr.Find_MinPath_Floyd();
    gr.Find_MinPath_Dijkstra();
    cout << "Kruskal算法：\n";
    gr.MST_Kruskal();
    cout << "Prim算法，请输入起始点坐标：";
    int n;
    cin >> n;
    gr.MST_Prim(n);
}