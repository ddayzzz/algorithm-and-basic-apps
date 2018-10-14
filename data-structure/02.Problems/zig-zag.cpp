#include "../stdafx.h"
#include <iomanip>
int main()
{
    ///*改进版Z字编码
    const int d1 = 6;
    const int d2 = 6;
    int martix[d1][d2];
    int martix2[d1][d2];
    int *p = &martix[0][0];
    for (int u = 0; u < d1 * d2; ++u)
        *p++ = u;
    cout << "原始的数据: " << endl;
    for (int u = 0; u < d1; ++u)
    {
        for (int j = 0; j < d2; ++j)
        {
            std::cout << setw(4) << martix[u][j];
        }
        std::cout << endl;
    }
    int u = 0, j = 0; //XY是下一个的坐标
    int x, y;
    //z字型编码
    for (x = 0; x < d1; ++x)
    {
        for (y = 0; y < d2; ++y)
        {
            martix2[u][j] = martix[x][y];
            //u是纵坐标 j是横坐标
            if ((d1 % 2 == 0 && j % 2 == 0 && (u == 0 || u == d1 - 1)) || (d1 % 2 && (u == 0 && j % 2 == 0 && j != d1 - 1 || u == d1 - 1 && j % 2 == 1))) //防止在右上端点的问题
            {
                j++;
                continue;
            }
            if ((d1 % 2 == 0 && u % 2 == 1 && (j == 0 || j == d2 - 1)) || (d1 % 2 && (j == d2 - 1 && u % 2 == 0 || u % 2 == 1 && j == 0)))
            {
                u++;
                continue;
            }
            if ((u + j) % 2 == 0)
            {
                j++;
                u--;
            }
            else
            {
                u++;
                j--;
            }
        }
    }
    cout << "修改后的数据: " << endl;
    for (int u = 0; u < d1; ++u)
    {
        for (int j = 0; j < d2; ++j)
        {
            std::cout << setw(4) << martix2[u][j];
        }
        std::cout << endl;
    }
}