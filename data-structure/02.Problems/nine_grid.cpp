#include <iomanip>
#include <iostream>
int main()
{
    ////普通模式的九宫格算法??

    int line;
    std::cout << "请输入格子数:";
    std::cin >> line;
    int **arr = new int *[line];
    for (int i = 0; i < line; ++i)
    {
        arr[i] = new int[line];
        for (int j = 0; j < line; ++j)
        {
            arr[i][j] = 0;
        }
    }
    delete[] arr;
}