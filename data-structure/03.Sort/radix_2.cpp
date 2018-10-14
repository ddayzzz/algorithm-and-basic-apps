// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "../stdafx.h"
#include <iostream>
#include <cmath>
#include "Node.h"
using std::cout;
using std::endl;
unsigned getDigit(int x, unsigned d)
{
	int ar[] = { 1,10,100,1000 };
	return (x / ar[d-1]) % 10;
}
//基数排序算法(有问题)  数组首元素地址, 起始索引, 结束索引 , 排序的最大数的位数(控制扫描次数)
void radixSort(int arrp[], unsigned beg, unsigned end, unsigned d) 
{
	int i;
	int j, k;
	constexpr unsigned radix = 10;//控制基数
	int count[radix];//计数的数组 这个数组可以控制数字出现的位置
	//置空
	for (i = 0; i <10; ++i)
	{
		count[i] = 0;
	}
	int *sorted = (int*)malloc((end-beg+ 1) * sizeof(int));
	for (i = 1; i <= d; ++i)
	{
		for (k = beg; k <= end; ++k)
		{
			count[getDigit(arrp[k],i)]++;//统计当前扫描次数的I位的位数
		}
		for (k = 1; k < radix; ++k)
		{
			count[k] += count[k - 1];
		}
		for (k = end; k >= 0; --k)
		{
			j = getDigit(arrp[k], i);
			sorted[count[j] - 1] = arrp[k];
			--count[j];
		}
		for (j = 0, k = beg; k <= end; j++, k++)
		{
			arrp[k] = sorted[j];
		}
	}
	for (k = 0; k < end -beg +1; ++k)
	{
		printf("%d ", arrp[k]);
	}
	free(sorted);
}

void lsdradix_sort(int arr[], int begin, int end, int d)
{
	const int radix = 10;
	int count[radix], i, j;

	int *bucket = (int*)malloc((end - begin + 1) * sizeof(int));  //所有桶的空间开辟   

																  //按照分配标准依次进行排序过程
	for (int k = 1; k <= d; ++k)
	{
		//置空
		for (i = 0; i < radix; i++)
		{
			count[i] = 0;
		}
		//统计各个桶中所盛数据个数
		for (i = begin; i <= end; i++)
		{
			count[getDigit(arr[i], k)]++;
		}
		//count[i]表示第i个桶的右边界索引
		for (i = 1; i < radix; i++)
		{
			count[i] = count[i] + count[i - 1];
		}
		//把数据依次装入桶(注意装入时候的分配技巧)
		for (i = end; i >= begin; --i)        //这里要从右向左扫描，保证排序稳定性   
		{
			j = getDigit(arr[i], k);        //求出关键码的第k位的数字， 例如：576的第3位是5   
			bucket[count[j] - 1] = arr[i]; //放入对应的桶中，count[j]-1是第j个桶的右边界索引 
			--count[j];               //对应桶的装入数据索引减一  
		}

		//注意：此时count[i]为第i个桶左边界  

		//从各个桶中收集数据
		for (i = begin, j = 0; i <= end; ++i, ++j)
		{
			arr[i] = bucket[j];
		}
	}
	free(bucket);
}
//基数排序 我写的
void my_radix_sort(int arr[], int beg, int end, int d)
{
	constexpr int base = 10;//基数
	int count[base];//这个数组保存要基数数字的个数
	int copied_count[base];
	int fornextd[base];
	int **sorted = (int**)malloc(sizeof(int*)* base);//用于保存数字的桶
	int i, j, k,t;
	
	//初始化计个数的数组
	for (i = 1; i <=base; ++i)
	{
		count[i - 1] = 0;
		copied_count[i - 1] = 0;
		fornextd[i - 1] = 0;
	}
	//统计各个数字出现的总数 一次节省空间地分配数组
	for (i = 1; i <= d; ++i)
	{
		for (j = beg; j <= end; ++j)
		{
			k = getDigit(arr[j], i);
			++count[k];
			++copied_count[k];
		}
	}
	
	
	//统计每个数字需要的空间
	for (i = 0; i < base; ++i)
	{
		j = count[i];
		if (j == 0)
		{
			sorted[i] = NULL;
		}
		else
		{
			sorted[i] = (int*)malloc(sizeof(int) *j);
		}
	}
	//所有数组分配完毕
	//进行排序
	for (i = 1; i <= d; ++i)
	{
		for (int u = 1; u <= base; ++u)
		{
			count[u - 1] = 0;
			//copied_count[u - 1] = 0;
		}
		for (int y = beg; y <= end; ++y)
		{
			k = getDigit(arr[y], i);
			count[k]++;
			//copied_count[k]++;
		}


		if (i == 1)
		{
			for (int w = 0; w < base; ++w)
			{
				fornextd[w] = count[w];
			}
			for (j = end; j >=beg; --j)
			{
				k = getDigit(arr[j], i);
				t = count[k];
				int index = t - 1;
				sorted[k][index] = arr[j];
				--count[k];
			}
			//copy保存元素
			for (int w = 0; w < base; ++w)
			{
				copied_count[w] = fornextd[w];
			}
		}
		else
		{
			for (int w = 0; w < base; ++w)
			{
				fornextd[w] = copied_count[w];
			}
			for (j = 0; j < base; ++j)
			{
				for (k = 0; k < copied_count[j]; ++k)
				{
					int tv = sorted[j][k];
					t = getDigit(tv, i);
					int tmpi = copied_count[t] - count[t];
					sorted[t][tmpi] = sorted[j][k];
					count[t]--;
					count[j]++;
				}
			}
			//copy保存元素
			for (int w = 0; w < base; ++w)
			{
				copied_count[w] = fornextd[w];
			}
		}
	}
	for (i = 0; i < base; ++i)
	{
		if (sorted[i] == NULL) continue;
		for (j = 0; j < fornextd[i]; ++j)
		{
			printf("%d ", sorted[i][j]);
		}
	}
	for (i = 0; i < base; ++i)
	{
		if (sorted[i] == NULL) continue;
		for (j = 0; j < copied_count[i]; ++j)
		{
			arr[beg++] = sorted[i][j];
		}
	}
}
//归并排序 排序
void merge_sort_sort(int arr[], int beg, int end)
{
	int i, j,w;
	for (i = beg; i < end; ++i)
	{
		for (j = beg; j < end-i; ++j)
		{
			if (arr[j] > arr[j+1])
			{
				 w = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = w;
			}
		}
	}
}
void merge_sort_divide(int arr[], int b, int e)
{
	if ((e - b) % 2 == 1)
	{
		//偶数个
		int *sorted = (int*)malloc(sizeof(int) * (e - b + 1));
		int pos=b; int end=e; int mid;
		mid = (end - pos) / 2;
		while (mid - pos != 1)
		{
			
		}
	}
}

int main()
{
	/* 桶排序
	int arr[11] = { 0,4,2,5,1,0,8,5,2,5,19 };//处理的数组
	int con[20] = { 0};//出现的次数
	int sorted[11];
	int i;
	for (i = 0; i < 11; ++i)
	{
		con[arr[i]]++;
	}
	int k;
	int pos = 0;
	for (i = 0; i < 20; ++i)
	{
		for (k = 1; k <= con[i]; ++k)
		{
			sorted[pos+k-1] = i;
		}
		pos = pos + con[i];
	}
	*/
	/* 基数排序
	*/
	int  br[10+5] = { 1,1,3,1,20, 80, 90, 589, 998, 965,90, 852, 123, 456, 789 };
	lsdradix_sort(br, 0, 9+4, 3);
	/*插入排序
int ar[] = { 5,7,3,1,8,9,4 };
	int i, j,k; int t;
	int len = sizeof(ar) / sizeof(int);
	for (i = 1; i < len; ++i)
	{
		int key = ar[i];
		j = i - 1;
		while (j >= 0 && ar[j] > key)
		{
			ar[j + 1] = ar[j];
			--j;
		}
		ar[j + 1] = key;
	}
	*/
	/*
	List<int> l;
	l.push_back(23);
	l.push_back(55);
	l.push_back(0.3);
		list_iterator<int> li = l.begin(),end;
	
	for (; li != end; ++li)
	{
		cout << *li << " "<<endl;
	}
	*/

    return 0;
}

