#include <vector>
#include "../Maze.h"
#include "../Queen.h"
int main()
{
    // 迷宫求解
    printf("Maze:\n");
    std::vector<Crossing> cros;
    Crossing c1(2, 0, 0);
    Crossing c2(4, 0, 0);
    Crossing c3(0, 0, 0);
    Crossing c4(5, 3, 0);
    Crossing c5(6, 0, 0);
    Crossing c6(0, 7, 0);
    Crossing c7(8, 9, 0);
    Crossing c8(0, 0, 0);
    Crossing c9(10, 0, 0);
    Crossing c0(0, 0, 0);
    cros.push_back(c0);
    cros.push_back(c1);
    cros.push_back(c2);
    cros.push_back(c3);
    cros.push_back(c4);
    cros.push_back(c5);
    cros.push_back(c6);
    cros.push_back(c7);
    cros.push_back(c8);
    cros.push_back(c9);
    Maze ma(cros, 10);
    ma.FindExit();
    printf("N Queens:\n");
    //n皇后问题
    QueenPuzzle qz(8);
    qz.PlaceQueen(0);
}