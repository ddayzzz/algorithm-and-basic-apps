#include "../Sort.h"
#include <iostream>
int main()
{
    	///*基数排序
    int arr[] = { 10,89,123,7,4,500,444,32 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	RadixSort(arr, sz,4);
    for(int i=0;i<8;++i)
    {
        std::cout << arr[i] << " ";
    }
}