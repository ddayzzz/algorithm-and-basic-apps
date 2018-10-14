//杨辉三角
//辅助函数 用于交换
#include <iostream>
#include <list>
#include <iomanip>
#include "../Queue.hpp"

void show_exchange_queue(LinkQueueList<int> &old,LinkQueueList<int> &newone,int jieshu,int maxjieshu)
{
	old.makeEmpty();
	for (int i = maxjieshu - jieshu; i >= 1; --i)
	{
		std::cout << "   ";
	}
	while (!newone.isEmpty())
	{
		int dep = newone.DeQueue();
		old.EnQueue(dep);
		std::cout << std::setw(6) << dep;
	}
	newone.makeEmpty();
	std::cout << std::endl;
}
void Yanghui_Triangle(int n)
{
	LinkQueueList<int> ori,curr;
	int ini = 1;
	int precnt = 0; int nextcnt = 1;
	for (int i = 1; i <= n; ++i)
	{
		/* 我的代码实现
		for (int u = 1; u <= i; ++u)
		{
			if (u == 1) { precnt = 0; nextcnt = 1; if (!ori.isEmpty()) { ori.DeQueue(); } //这个判断用于处理从第二阶开始的上次队列的计数问题
			}
			else if (u == i) { nextcnt = 0; }
			curr.EnQueue(precnt + nextcnt);
			int temp = nextcnt;
			if (!ori.isEmpty())
			{
				nextcnt = ori.DeQueue();
			}
			precnt = temp;
			
		}
		*/
		curr.EnQueue(ini);
		while (!ori.isEmpty())
		{
			int h = ori.DeQueue();
			if (ori.isEmpty() == false)
			{
				h += ori.GetFront();
				curr.EnQueue(h);
			}
			if (ori.isEmpty())
				curr.EnQueue(h);
		}
		show_exchange_queue(ori, curr,i,n);

	}
}
//杨辉三角 数组解法
void display(int *p,int curr, int maxline)
{
	for (int u = maxline; u > curr; --u)
		std::cout << "   ";
	for (int i = 1; i <= curr; ++i)
		std::cout << std::setw(6) << p[i - 1];
	std::cout << std::endl;
}
void Yanghui_Triangle_array(int n)
{
	if (n >= 1)
	{
		int **ptr = new int*[n];
		int **start = ptr;
		for (int j = 1; j <= n; ++j)
		{
			*ptr++ = new int[j];
		}
		//内存分配完成
		
		for (int i = 1; i <= n; ++i)
		{
			(*(start + i - 1))[0] = 1;
			int lcnt = 0;
			int rcnt = 1;
			
			for (int u = 2; u <= i; ++u)
			{
				if (u <= i - 1)
				{
					int tem = rcnt;
					rcnt = (*(start + i - 2))[u - 1];
					lcnt = tem;
				}
				else
				{
					lcnt = rcnt;
					rcnt = 0;
				}
				(*(start + i - 1))[u - 1] = lcnt + rcnt;
			}
			display(start[i - 1], i, n);
		}
		for (int u = 1; u <= n; ++u)
			delete start[u-1];
		delete start;
	}
	
}
int main()
{
    Yanghui_Triangle(10);
}