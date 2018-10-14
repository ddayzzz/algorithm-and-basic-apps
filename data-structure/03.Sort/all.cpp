#include "../Sort.h"
#include <random>

#include <iostream>
int main()
{
    const int maxsz = 100000;
	int arr[maxsz];
	int a2[maxsz];
	int sz = sizeof(arr) / sizeof(arr[0]);
	std::uniform_int_distribution<int> u(-100,900000);
	std::default_random_engine e;
	for (int i = 0; i < sz; ++i)
	{
		arr[i] = u(e);
	}
	std::cout << "排序前,前100个:";
	for(int i=0;i<100;++i)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << "插入排序用时：" << (getRunningTime<int, decltype(MergeSort<int>)>(arr, sz, MergeSort));
    #ifdef _WIN32
    std::cout << "秒";
    #elif __linux__
    std::cout << "CPU 时间";
    #endif
	std::cout << "排序后,前100个:";
	for(int i=0;i<100;++i)
	{
		std::cout << arr[i] << " ";
	}
	
	//insert_sort<int>(arr, sz);
	//binarysort<int>(arr, sz);
	//shellSort<int>(arr, sz);
	//directSelectSort<int>(arr, sz);
	//BubbleSort<int>(arr, sz);
	//ShakerSort(arr, sz);
	//QuickSort(arr, sz);
	//QuickSort4(arr, sz);
	//MergeSort<int>(arr, sz);
	//CountingSort(100,arr, sz);
}