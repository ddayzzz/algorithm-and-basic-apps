// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include <iostream>
#include <cstdlib>
#include <string.h>

int getnumbercount(int lastnum)
{
	int acc = 1;
	if (lastnum == 1)
		return 1;
	for (int k = 1; k <= lastnum / 2; ++k)
		acc += getnumbercount(k);
	return acc;
}
int main()
{
	int num;
	while (std::cin >> num)
	{
		int output;
		output = getnumbercount(num);
		std::cout << output << std::endl;

	}

}


