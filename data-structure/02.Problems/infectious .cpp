//传染病问题
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
struct Cell
{
	int Isvirus;
	bool bechecked=false;
};
class CellsGroup
{
public:
	//celllist 是表示细胞状态的数组，nb表示细胞组的边长个数
	CellsGroup(int celllist[6][6], int n) :units(n)
	{
		for (int i = 0; i < n; ++i)
		{
			std::vector<Cell> tmp;
			for (int j = 0; j < n; ++j)
			{
				Cell c;
				c.Isvirus = celllist[i][j];
				tmp.push_back(c);
			}
			cellsgroup.push_back(tmp);
		}

	}
	//这个是显示原始数据
	void display_grid()
	{
		for (auto iter = cellsgroup.cbegin(); iter != cellsgroup.cend(); ++iter)
		{
			for (auto b = iter->cbegin(); b != iter->cend(); ++b)
			{
				cout << b->Isvirus << " ";
			}
			cout << endl;

		}
	}
	//这个用于已被检查的返回感染细胞数组
	void display_grid_check()
	{
		for (auto iter = cellsgroup_check.cbegin(); iter != cellsgroup_check.cend(); ++iter)
		{
			for (auto b = iter->cbegin(); b != iter->cend(); ++b)
			{
				if (b->bechecked == true)
				{
					cout << std::setw(3) <<"+"<< b->Isvirus;
				}
				else
				{
					cout << std::setw(3) << b->Isvirus;
				}
			}
			cout << endl;

		}
	}
	void find_virus(int x, int y)
	{
		cellsgroup_check = cellsgroup;//建立一个新的副本
		numberofVirus_check = 0;//感染计数为0
		do_findvirus(x, y);//开始检查
	}
	void do_findvirus(int x, int y)
	{
		if (x < 0 || y<0 || x>=units || y >=units|| cellsgroup_check[x][y].Isvirus==0)//退出条件
		{
			return;
		}
		if (cellsgroup[x][y].Isvirus == 1)//原始数据的位置是否为感染的细胞 如果是就检查周围
		{
			if (cellsgroup_check[x][y].bechecked == false)//防止重复搜索
			{
				numberofVirus_check++;
				cellsgroup_check[x][y].Isvirus = 1;
				cellsgroup_check[x][y].bechecked = true;
				do_findvirus(x - 1, y - 1);//LEFT UP
				do_findvirus(x - 1, y);//UP
				do_findvirus(x - 1, y + 1);//right up
				do_findvirus(x, y - 1);//left
				do_findvirus(x, y + 1);//right
				do_findvirus(x + 1, y - 1);//left down
				do_findvirus(x + 1, y);//down
				do_findvirus(x + 1, y + 1);//right down
			}
		}
	
	}
	
private:
	std::vector<std::vector<Cell>> cellsgroup;
	std::vector<std::vector<Cell>> cellsgroup_check;
	int numberofVirus_check;
	int units;
};
int main()
{
    int bb[6][6] = {
{1,0,0,0,0,0},
{0,1,0,0,0,0},
{0,0,1,1,0,1},
{0,0,1,1,0,1},
{1,0,1,1,0,1},
{1,0,0,0,0,0}
};
CellsGroup ce(bb, 6);
ce.find_virus(1, 1);
ce.display_grid_check();
}