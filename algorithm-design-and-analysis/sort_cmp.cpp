// 用于进行排序算法之间的比较
#include <random>
#include <iostream>
#include <ctime>
#include <vector>
#include <iomanip>
// #define BINARY_SORT
#define SORT_DEMOS
#define DISPLAY
int binary_sort(int a[], int fnd, int l, int h)
{
    int mid;
    while(l <= h)
    {
        mid = (l + h) / 2;
        if(a[mid] == fnd)
            return mid;
        else if(a[mid] > fnd)
            h = mid -1;
        else
            l = mid + 1;
    }
    return -1;
}
//归并排序
//归并算法的合并算法 第一个参数原数组 low为开始的地址 mid
template<typename t> void do_mergeSort_hebing(t *arr,int low,int mid,int high)
{
	int i = low;//第一段的序列的下标
	int j = mid + 1;//第二段的序列下标
	int k = 0;//可临时存放合并序列的下标
	int *newarr = new t[high - low + 1];
	//扫描第一段个第二段序列 直到有一个扫描结束
	while (i <= mid && j <= high)
	{
		if (arr[i] <= arr[j])
		{
			newarr[k] = arr[i];
			++i;//有最小值的的数组的小标递增
			++k;//临时序列的下标递增
		}
		else
		{
			newarr[k] = arr[j];//填入新的值
			++j;//同理
			++k;//反正k无论如何也要变化
		}
	}
	//注意可能还有没完成的 这里的步骤就是把所有没有写入到新的表中的元素写入
	while (i <= mid)
	{
		newarr[k] = arr[i];
		++i;
		++k;
	}
	while (j <= high)
	{
		newarr[k] = arr[j];
		++j;
		++k;
	}
	for (k = 0, i = low; i <= high; ++i, ++k)
		arr[i] = newarr[k];//更新对应的元素数组里的值
	delete[] newarr;
}
//归并排序的分解算法
template<typename t> void do_mergeSort_divid(t *arr, int gap, int length)
{
	//gap表示的是每一次同级比较的间隔
	/*     5    6    9    1    3     2   0    4       10
	gap=1    56        91         32        04        10
	排序      56        19         23        04        10
	gap=2    （5619）1569            （2304）0234       10
	gap=4    01234569 10
	gap=8    0 1 2 3 4 5 6 9 10
	*/
	int i = 0;
	for (i = 0; i + 2 * gap - 1/* i+2*gap -1表示的是第一组需要合并的 如果只有一对需要合并 那么这个循环执行一次*/ < length; i = i + 2 * gap/*下一个替换的一对的起始位置*/)
		do_mergeSort_hebing(arr, i, i + gap - 1, i + 2 * gap - 1);
	//余下了两个子表 因为长度的大小是不可能满足的
	if (i + gap - 1 < length)
		do_mergeSort_hebing(arr, i, i + gap - 1, length - 1);
}
//这个hi接口的函数
template<typename t> void MergeSort(t *arr, int sz)
{
	for (int gap = 1; gap < sz; gap = gap * 2)
	{
		do_mergeSort_divid(arr, gap, sz);//每一次gap递增
	}
}

//快速排序
template<typename t> void QuickSort(t *arr, int left, int right)
{
	int i = left;
	int j = right;
	t pivot = arr[left];//基准元素
	while (i < j)
	{
		while (i < j && arr[j] >= pivot) --j;//将j递减到小于基准数值的位置 为什么j先走呢？因为要确定i所能走的上界 防止出现j < i的情况
		if (i < j) arr[i] = arr[j];//swap1(arr, i, j);//如果是因为小于基准数值而退出的while循环 就交换i与j所对应的值
		while (i < j && arr[i] <= pivot) ++i;//将i递增到第一个大于基准数值的位置
		if (i < j) arr[j] = arr[i];//交换位置
		//交换之后 pivot对应的位置左边的数字 < pivot 而右边的>pivot
		//上两次的交换就是 大于的值 与小于的值得交换 
	}//优化了多次比较 因为第一次交换pivot交换为j的位置 然后从i选择最大的那个交换需要吧pivot往i的位置交换 所以只需要把arr[j]的位置改为arr[i]就不需要多次赋值pivot
	arr[i] = pivot;
	if (i != left) QuickSort(arr, left, i - 1);//从[left,i-1]做快速排序
	if (j != right) QuickSort(arr, j + 1, right);
}
int main()
{
    #ifdef BINARY_SORT
    int arrays[10] = {1,2,4,5,9,10,11,12,20,30};
    int tofind;
    std::cout << "请输入查询的数字:";
    std::cin >> tofind;
    tofind = binary_sort(arrays, tofind, 0, 9);
    std::cout << "位置:" << tofind << (tofind == -1 ? ". 没有找到" : "") << std::endl;
    #endif
    #ifdef SORT_DEMOS
    constexpr int N = 999;
    int random_int;
    int *vector1 = new int[N];
    int *vector2 = new int[N];
	static std::uniform_int_distribution<int> und(1,99);// 均匀分布[1,99]
	static std::default_random_engine randomEng;// 随机数引擎
	randomEng.seed(time(NULL));
    for(int i=0;i<N;++i)
    {
        random_int = und(randomEng); // 产生随机数
        vector1[i] = vector2[i] = random_int;
    }
    //排序前
    #ifdef DISPLAY
	std::cout << "排序前" << std::endl << "vector1=vector2=";
    for(int i=0;i<N;++i)
    {
        std::cout << std::setw(3) << vector1[i];
    }
    std::cout << std::endl;
	#endif
    // 排序
    clock_t beg, end;
    beg = clock();
    MergeSort(vector1, N);
    end = clock();
    std::cout << "归并排序, 用时:"<< std::setw(8) << end - beg << " CPU时间单位" << std::endl;
    beg = clock();
    QuickSort(vector2, 0, N);
    end = clock();
    std::cout << "快速排序, 用时:"<< std::setw(8) << end - beg << " CPU时间单位" << std::endl;
    #ifdef DISPLAY
	std::cout << "排序后" << std::endl << "vector1=";
    for(int i=0;i<N;++i)
    {
        std::cout << std::setw(3) << vector1[i];
    }
    std::cout << std::endl << "vector2=";
    for(int i=0;i<N;++i)
    {
        std::cout << std::setw(3) << vector2[i];
    }
    std::cout << std::endl;
	#endif
    delete[] vector1;
    delete[] vector2;
    #endif
}
