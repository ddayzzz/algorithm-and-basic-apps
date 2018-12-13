// 8 皇后问题

#include <cstdio>
#include <cmath>
#define N 8

int queen[N]; // queen[i] = j 表示保存皇后 i 的列号 j
bool placeable(int i)
{
    // 检查将皇后放在 i 行是否可行
    for (int j = 0; j < i; ++j)
    {
        if (std::abs(i - j) == std::abs(queen[i] - queen[j]) || queen[i] == queen[j])
        {
            return false;
        }
    }
    return true;
}
int main()
{
    // 非递归形式

    int sum = 0;
    int row = 0; // row 用于控制行号
    queen[row] = 0;
    while (row >= 0) 
    {
        ++queen[row];
        while(queen[row] <= N && !placeable(row))
        {
            ++queen[row];
        }
        if(row == N - 1 && queen[row] <= N)
        {
            // 这是一个结果
            ++sum;
        }
        else
        {
            queen[row] > N ? --row : queen[++row] = 0; // 这里判断是不是已经探测了皇后的所有可能的位置。如果是， 回溯到上一个皇后， 算法会自动移动她到下一列；否则，当前的位置可以放下皇后同时搜索这个结果的下一个子树的位置。
        }
    }
    printf("Sum of solutions: %d\n", sum);
}