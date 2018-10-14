#include <queue>
#include <iostream>
using namespace std;


//FIFO策略
bool ExitOrNot(int num, std::queue<int> que)
{
	while (!que.empty())
	{
		if (que.front() == num)
			return true;
		else
			que.pop();
	}
	return false;
}
void Queyezhongduan(int *p, int size)
{
	using std::queue;
	queue<int> mem;
	int queyecnt = 0;
	for (int i = 0; i < size; ++i)
	{
		if (mem.size() < 3)
		{
			mem.push(p[i]);
			++queyecnt;//首次载入内存
		}
		else
		{
			if (ExitOrNot(p[i], mem))
			{

			}
			else
			{
				mem.pop();
				mem.push(p[i]);
				queyecnt++;
			}
			int sz = mem.size();
			while (sz > 0)
			{
				cout << mem.front() << " ";
				int tmpvalue = mem.front();
				mem.pop();
				mem.push(tmpvalue);
				--sz;
			}
			cout << endl;
		}
	}
	std::cout << "使用FIFO策略 共发生内存缺页 " << queyecnt << " 次\n";
}
//LRU策略
void Queue_memory_pagemgr_LRU(int *p, int size)
{
	std::queue<int> mem;
	int queye = 0;
	for (int i = 0; i < size; ++i)
	{
		if (mem.size() < 3)
		{
			mem.push(p[i]);
			++queye;
		}
		else
		{
			if (ExitOrNot(p[i], mem))
			{
				if (p[i] == mem.front())
				{
					mem.pop();
					mem.push(p[i]);
				}
				else
				{
					queue<int> tempfor;//这是临时保存pop出来的数据
					int sz = mem.size();//记录没有删除前的mem大小
					while (!mem.empty())
					{
						int getit = mem.front();//获取对头
						if (getit == p[i])
						{
							mem.pop();
							int need = sz - tempfor.size()-1;//这个用来控制入队之后需要循环的次数
							//这是把内存页中找到的那个内存之前的数据压入到mem 
							while (!tempfor.empty())
							{
								mem.push(tempfor.front());
								tempfor.pop();
							}
							//但此时内存之前的内存在对尾部 所以需要通过找到内存之后的尾部元素大小来循环 吧对尾的元素改到对头
							while (need > 0)
							{
								int tmp = mem.front();
								mem.pop();
								mem.push(tmp);
								--need;
							}
							mem.push(p[i]);
							break;
						}
						else
						{
							tempfor.push(getit);
							mem.pop();
						}
					}
				}
			}
			else
			{
				mem.pop();
				mem.push(p[i]);
				++queye;
			}
			int sz = mem.size();
			while(sz > 0)
			{
				int m = mem.front();
				cout << m << " ";
				mem.pop();
				mem.push(m);
				--sz;
			}
			cout << endl;
		}
	}
	cout << "使用LRU策略缺页发生 " << queye << " 次" << endl;
}
int main()
{
    // 内存分配模拟
    int me[] = { 4,3,2,1,4,3,5,4,3,2,1,5 };
    Queyezhongduan(me, 12);
    Queue_memory_pagemgr_LRU(me, 12);
    
}