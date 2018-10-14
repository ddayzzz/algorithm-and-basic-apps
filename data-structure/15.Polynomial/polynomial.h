#pragma once
#include "../stdafx.h"
#include "../00.Algorithms_Design_In_C_Common/list.h"
int max1(int a, int b) { return a > b ? a : b; }
/*用于保存多项式的系数的结构体
使用时请一定要用initpolynomal来初始化
使用完毕时请使用free_poly释放分配的资源
*/
struct polynomial
{
	Node nd;//保存各项系数
	int maxdegree;//规定多项式的项数
	int unknownvalue = 0;//未知数的值
	//用于初始化多项式 未知数的值，系数数组的首元素地址，项数
	void initpolynomal(int unknown, int *addofxishu, int num)
	{
		//初始化内置的成员
		unknownvalue = unknown;
		maxdegree = num;
		//firstxishuadd = addofxishu;
		int c;
		nd.makeempty();//初始化一个新的节点
		Node::Position pos = nd.head;
		for (c = 1; c <= num; ++c)
		{
			nd.insert(*addofxishu++, pos);//插入系数
			pos = pos->next;//更新位置
		}
		

	}
	//用于初始化多项式（可以使用指定的系数默认值，用于初始化保存结果的多项式） 项数，未知数的值，系数默认值
	void initpolynomal_zero(int num,int unknown,int xishu=1)
	{
		//初始化成员
		maxdegree = num;
		unknownvalue = unknown;
		int c;
		nd.makeempty();//创建新的节点
		Node::Position pos = nd.head;
		for (c = 1; c <= num; ++c)
		{
			nd.insert(xishu, pos);
			pos = pos->next;
		}
	}
	//使加法运算的左右操作数的长度保持一致 长度小的系数被初始化为1 参数:右操作数
	void make_p1_p2_size_equal(polynomial *p2)
	{
		int i;
		int maxcount = max1(maxdegree, p2->maxdegree);
		if (maxdegree > p2->maxdegree)
		{
			Node *pos = p2->nd.last(&p2->nd);
			for (i = p2->maxdegree; i < maxcount; ++i)
			{
				p2->nd.insert(0, pos);
				pos = pos->next;
			}
		}
		else
		{
			if (maxdegree < p2->maxdegree)
			{
				Node *pos = nd.last(&p2->nd);
				for (i = maxdegree; i < maxcount; ++i)
				{
					nd.insert(0, pos);
					pos = pos->next;
				}
			}
		}
	}
	//进行多项式加法运算 右操作数，目标写入的多项式地址，未知数的值（可以与左右操作数不同）
	void plus_xishuofpoly( polynomial *p2,polynomial *dest, int unknown)
	{
		int i;
		int maxcount = max1(maxdegree, p2->maxdegree);
		make_p1_p2_size_equal(p2);
		dest->initpolynomal_zero(maxcount,unknown);
		Node::Position pos = dest->nd.head->next;

		Node::Position pos1 = nd.head->next;
		Node::Position pos2 = p2->nd.head->next;
		for (i = 0; i < maxcount; ++i)
		{
			pos->data= (pos1->data + pos2->data);
			pos1 = pos1->next;
			pos2 = pos2->next;
			pos = pos->next;
		}
		//dest->nd.print_all_elements();
	}
	// 进行多项式乘法运算 右操作数，目标写入的多项式地址，未知数的值（可以与左右操作数不同）
	void multiply_xishuopoly(polynomial *p2, polynomial *dest,int unknown)
	{
		int i, k;
		int maxexp = maxdegree + p2->maxdegree;
		dest->initpolynomal_zero(maxexp - 1, unknown, 0);//乘法后的多项式的项数是左右最高项的指数之和 -1
		Node::Position pp1 = nd.head->next;
		Node::Position pp2;
		for (i = 0; i < maxdegree; ++i)
		{
			pp2 = p2->nd.head->next;
			for (k = 0; k < p2->maxdegree; ++k)
			{
				*dest->nd.get_position_byindex(k + i) += pp1->data * pp2->data;
				pp2 = pp2->next;
			}
			pp1 = pp1->next;
		}
	}
	//显示多项式的含未知数的表达式 结束字符，未知数的形式 如果结尾字符是退格的转义序列 那么就会在结尾字符前多出一个空格用于删除
	void show_unary_mode(char endchar = '\n', char c = 'X')
	{
		/* 原则是
		1.常数项不显示未知数
		2.一次项不显示1次方
		3.所有系数为0的项都不显示）
		4.最高项不太可能会为0（待验证）
		
		*/
		Node::Position pos = nd.head->next;
		int cnt = 0;
		char previous_symbol = '\0';//保存项数的符号
		bool firstobj = true;//是否是第一个项 用于处理是否显示项数符号
		int val;
		if (pos == NULL) { return; }//如果不存在元素

		
		while (pos != NULL)
		{ 
			val = pos->data;
			if (val > 0)
			{
				if (firstobj == true)//如果是正数 并且是第一个项数 那么就不显示正数符号 这个可以输出一个常数项
				{
					previous_symbol = '\0';
					firstobj = false;//下一次就必须显示符号
				}
				else
				{
					previous_symbol = '+';//这不是第一个项数 算哦以显示符号
				}
			}
			else
			{
				if (val < 0)
				{
					previous_symbol = '-'; val = -val;//显示负号 同时val取绝对值
					firstobj = false;//同时也关闭第一项不显示符号的策略
				}
				else
				{
					if (val == 0)
					{
						if (pos->next == NULL)//如果第一项为0 同时以后没有项了 那么就显示0
						{
							printf("0");
							break;
						}
						else
						{
							//如果为0 且不是最后一想那么直接跳过 不显示
							++cnt;
							pos = pos->next;
							continue;
						}
					}
				}
			}
			//已确定显示的val 以及符号
			switch (cnt)
			{
			case 0:
				if(previous_symbol !='\0'){ printf("%c%d", previous_symbol, val); }else{ printf("%d", val); }//如果项的符号为\0那么就不显示了
				break;
			case 1:
				 if(previous_symbol !='\0')
				 { 
					 if (val != 1)
					 {
						 printf("%c%d%c", previous_symbol, val, c);
					 }
					 else {
						 printf("%c%c", previous_symbol, c);
					 }
				 }
				 else
				 { 
					 if (val != 1)
					 {
						 printf("%d%c", val, c);
					 }
					 else
					 {
						 printf("%c", c);
					 }
				 }
				break;
				
			default:
				if (cnt == maxdegree - 1)
				{
					//默认不显示\0字符
					if (endchar == '\b')
					{
						//如果是退格 那么就留出一个空格用于删除  更紧凑
						if (val == 1)//系数为1则不显示
						{
							if (previous_symbol != '\0')
							{
								printf("%c%c^%d %c", previous_symbol, c, cnt, endchar);
							}
							else
							{
								printf("%c^%d %c", c, cnt, endchar);
							}
						}
						else
						{
							if (previous_symbol != '\0')
							{
								printf("%c%d%c^%d %c", previous_symbol, val, c, cnt, endchar);
							}
							else
							{
								printf("%d%c^%d %c", val, c, cnt, endchar);
							}
						}
					}
					else
					{
						if (val == 1)
						{
							if (previous_symbol != '\0')
							{
								printf("%c%c^%d%c", previous_symbol, c, cnt, endchar);
							}
							else
							{
								printf("%c^%d%c", c, cnt, endchar);
							}
						}
						else
						{
							if (previous_symbol != '\0')
							{
								printf("%c%d%c^%d%c", previous_symbol, val, c, cnt, endchar);
							}
							else
							{
								printf("%d%c^%d%c", val, c, cnt, endchar);
							}
						}
					}
				}
				else
				{
					if (previous_symbol != '\0')
					{
						printf("%c%d%c^%d", previous_symbol, val, c, cnt);
					}
					else
					{
						printf("%d%c^%d", val, c, cnt);
					}
				}
				break;
			}
			++cnt;//递增次数
			pos = pos->next;//更新地址
		}
	}
	//返回计算得到的值（未知数的值由初始化给出）
	int show_calced_value()
	{
		Node::Position pos = nd.head->next;
		int res = 0;
		int val;
		int cnt = 0;
		if (pos == NULL) { return 0; }
		while (pos != NULL)
		{
			val = pos->data;
			res = res + val*(power(unknownvalue, cnt));
			pos = pos->next;
			++cnt;
		}
		return res;
	}
	//释放资源
	void free_poly()
	{
		nd.free_list();
		//free(nd.head);
	}
	//返回e的X次方
	int power(int e,int x)
	{
		if (x == 0) return 1;
		int val = e;
		int i;
		for (i = 1; i < x; ++i)
		{
			val *= e;
		}
		return val;
	}
};