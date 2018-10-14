// CA4.cpp : 定义控制台应用程序的入口点。
//

#include "../stdafx.h"
#include "../00.Algorithms_Design_In_C_Common/AVLTree.h"

int main()
{
	AVLTree a;
	//a = make_empty_avltree();
	a = NULL;
	for (int i = 1; i <= 1000; ++i)
	{
		a = insert_avltree(i, a);
	}
	print_all_elements_avltree(a);
	//getchar():
	free_avltree(a);
    return 0;
}

