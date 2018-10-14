#include <string.h>

//这是一个用于数组元素的交换函数
template<typename t> void swap1(t* arr,int i,int j)
{
	t tmp = arr[j];
	arr[j] = arr[i];
	arr[i] = tmp;
}
//插入排序法
template<typename t>
void insert_sort(t *arr, int sz)
{
	/*
	t *newarr = new t[sz];
	memset(newarr, t(), sizeof(t) * sz);
	t insert;
	int i;
	for (i = 0; i < sz; ++i)
	{
		insert = arr[i];
		int j = i;
		while (j > 0 && insert < newarr[j-1])//比较从后面开始比较 注意是j-1 因为j这个位置还没有元素插入 所以这是个默认值 而真正需要比较的是先从[0，J-1]的元素
		{
			newarr[j] = newarr[j - 1];
			--j;
		}
		newarr[j] = insert;
	}
	for (i = 0; i < sz; ++i)
	{
		arr[i] = newarr[i];
	}
	delete[] newarr;
	*/
	//不需要分配新的空间的插入排序
	for (int i = 1; i < sz; ++i)//注意是从I=1开始的 因为我们认为arr[1...1]是有序的
	{
		if (arr[i] < arr[i - 1])//一旦找到反序的位置 那么进行插入排序
		{
			int tempv = arr[i];//保存最小的值
			int j;
			for (j = i - 1; j >= 0 && arr[j] > tempv; --j)
				arr[j+1] = arr[j];
			arr[j + 1] = tempv;//将正序的位置赋值
		}
		
	}
}
//二分插入排序
template<typename t> void binarysort(t *arr, int sz)
{
	/*这个是需要分配空间的算法 空间复杂度为On
	t *newarr = new t[sz];
	memset(newarr, t(), sizeof(t) * sz);
	t insert;
	int i,mid;
	for (i = 0; i < sz; ++i)
	{
		insert = arr[i];
		int left = 0;
		int right = i - 1;
		while (left <= right)
		{
			//二分法 八元素插入到小于等于insert的前面
			mid = (left + right) / 2;
			if (newarr[mid] > insert)
				right = mid - 1;
			else if (newarr[mid] <= insert)
				left = mid + 1;
		}
		for (int j = i; j > left; --j)
			newarr[j] = newarr[j - 1];//为新插入的元素让位
		newarr[left] = insert;
	}
	for (i = 0; i < sz; ++i)
	{
		arr[i] = newarr[i];
	}
	delete[] newarr;
	*/
	//因为插入排序 是认为钱ARR[0...I-1]是有序的 所以可以使用二分搜索找到插入位置 这个插入位置lower
	for (int i = 0; i < sz; ++i)
	{
		if (arr[i] < arr[i - 1])
		{
			int tempv = arr[i];
			int lower = 0;
			int upper = i - 1;
			int mid;
			while (lower <= upper)
			{
				mid = (lower + upper) / 2;
				if (arr[mid] < tempv)
					lower = mid + 1;
				else if (arr[mid] >= tempv)//如果插入值 <=mid 那么就可以在具有相同值得两个元素的（此时upper==lower==mid) 所以我们递减upper 可以保证推出循环 并且能够保证lower时刻写入位置。同时 如果时不同元素也可以保证
					upper = mid - 1;
			}
			
			for (int j = i-1; j >= lower; --j)
				arr[j+1] = arr[j];
			/*等价写法
			for (int j = i; j > lower; --j)
				arr[j] = arr[j-1];
			*/
			arr[lower] = tempv;

		}
	}
}
//希尔排序
template<typename t> void shellSort(t *arr, int sz)
{
	int insert;
	int gap = sz / 2;
	while (gap >= 1)
	{
		for (int i = gap; i < sz; ++i)//距离为gap分为一组，每一组的最后的一个元素不能大于sz
		{
			insert = arr[i];//这个表示待比较的值
			int j;
			//模拟的是一个插入排序
			for (j = i - gap/*从之前的一个元素比较*/; j >= 0 && insert < arr[j]/*如果待插入的元素<他的上司*/; j = j - gap/*j的目标位置递减*/)
				arr[j + gap] = arr[j];//交换元素的位置 空出地方来
			arr[j + gap] = insert;//在第一个满足<=insert的元素的+gap位置插入元素
		}
		gap = gap / 2;//更新gap分组
	}
};
//直接选择排序
template<typename t> void directSelectSort(t *arr, int sz)
{
	int k;
	int i;
	for (i = 0; i < sz; ++i)
	{
		k = i;
		for (int j = i + 1; j < sz; ++j)
			if (arr[j] < arr[k])
				k = j;//选出最小的元素的索引 保存到k
		//swap 交换元素
		t temp = arr[i];//保存当前需要替换的元素
		arr[i] = arr[k];
		arr[k] = temp;
	}
}
//冒泡排序
template<typename t> void BubbleSort(t *arr, int sz)
{
	int i, j;
	bool flag;
	for (i = 0; i < sz; ++i)
	{
		flag = false;//如果原序列不需要交换 那么认为数组是有序的
		for (j = 0; j < sz-i-1; ++j)
		{
			if (arr[j] > arr[j+1])
			{
				flag = true;
				t tmp = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = tmp;
			}
		}
		if (flag == false)
			break;
	}
}
//鸡尾酒排序
template<typename t> void ShakerSort(t *arr, int sz)
{
	int left=0, right=sz-1;
	int shift = 0;//这个用来控制每一次的转化 从左到右和从右到左的界限坐标的转换
	while (left < right)//如果left==right就不再需要比较交换
	{
		for (int i = left; i < right; ++i)//从做到右
		{
			if (arr[i + 1] < arr[i])
			{
				swap1(arr, i + 1, i);
				shift = i;//更改shift的值
			}
		}
		right = shift;//缩小下一次变化的比较的区间
		for (int j = right; j > left; --j)
		{
			if (arr[j] < arr[j - 1])
			{
				swap1(arr, j, j - 1);
				shift = j;
			}
		}
		left = shift;//缩小下一次变化的比较的区间
	}
}
//快速排序
template<typename t> void do_quickSort(t *arr, int left, int right)
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
	//int p;
	//for (p = 0; p < 10; ++p)
		//printf("%3d", arr[p]);
	//printf("\n");
	if (i != left) do_quickSort(arr, left, i - 1);//从[left,i-1]做快速排序
	if (j != right) do_quickSort(arr, j + 1, right);
}
template<typename t> int do_quickSort_MinRecursion_partition(t *arr,int low,int upper)
{

	int i, j;
	t pivot;
	i = low;
	j = upper;
	pivot = arr[i];
	while (i < j)
	{
		
		while(i < j && arr[j] >= pivot) --j;
		if (j > i) arr[i] = arr[j];
		while (i < j && arr[i] <= pivot) ++i;
		if (j > i) arr[j] = arr[i];
	}
	arr[i] = pivot;


	return i;
}
//减少了递归调用
template<typename t> void do_quickSort_MinRecursion(t *arr, int low,int upper)
{
	int piv;
	while (low < upper)
	{
		piv = do_quickSort_MinRecursion_partition<t>(arr, low, upper);//这个是分块进行 返回交换的边界piv（也就是pivot的交换位置）
		do_quickSort_MinRecursion<t>(arr, low, piv - 1);//在对左边的位置进行排序
		low = piv + 1;//在对右边的排序
	}
	//还可以用插入排序排序小数组
}
//这个是从第一个元素开始扫描 
template<typename t> void do_quickSort2(t *arr, int lower, int upper)
{
	if (lower >= upper)
		return;
	int m = lower;//m是测试的值 表示下界
	t temp = arr[lower];//这个是比较的值
	for (int i = lower + 1; i <= upper;++i)//比较arr[l+1,,,,u]范围内的数据
	{
		if (arr[i] < temp)
		{
			swap1(arr, ++m, i);//凡是比基准值小的 全部要与基准值之后的一个元素交换（注意此时的基准值的索引递增了1）
		}
	}
	swap1(arr, lower, m);//交换边界和基准值
	do_quickSort2(arr, lower, m - 1);//在对新的基准值左右进行排序
	do_quickSort2(arr, m + 1, upper);
}
template<typename t> void do_quickSort3(t *arr, int lower, int upper)
{
	if (lower >= upper)
		return;
	int i, j;
	i = lower; j = upper+1;//这个之所以需要扩大一个位置
	t tag= arr[lower];//默认的基准值位置
	while (true)
	{
		do { ++i; } while (i <= upper && arr[i] < tag);//这个可以吧i递增到第一个不小于基准值的位置
		do { --j; } while (j >= lower && arr[j] > tag);//j递减到第一个不大于基准值的位置
		if (i > j)//如果他们调换了位置 直接退出循环 如果是全部是相等的话 就需要logn的时间 每次对称缩小一个单位 知道 i==j
			break;
		swap1(arr, i, j);//交换两个不满足的值 交换后就满足了了性质
		
	}
	swap1(arr, lower, j);//之所以需要调换边界 是因为arr[j]相对于之前的tag（注意之前的i j交换了对应的值） 他更大 所以之前排好序的部分是不会动的
	//进一步缩小范围
	do_quickSort3(arr, lower, j - 1);
	do_quickSort3(arr, j + 1, upper);
}
#include <random>
const int cutoff = 1;
int randint(int sz)
{
	std::default_random_engine e;
	return e() % sz;
}
template<typename t> void do_quickSort4(t *arr, int lower, int upper)
{
	int i,j;
	if (upper -lower < cutoff)
		return;
	swap1(arr, lower, randint(upper - lower+1));//下界与随机的位置交换 这个位置介于 i j之间
	i = lower; j = upper + 1;//这个之所以需要扩大一个位置
	t tag = arr[lower];//默认的基准值位置
	while (true)
	{
		do { ++i; } while (i <= upper && arr[i] < tag);//这个可以吧i递增到第一个不小于基准值的位置
		do { --j; } while (j >= lower && arr[j] > tag);//j递减到第一个不大于基准值的位置
		if (i > j)//如果他们调换了位置 直接退出循环 如果是全部是相等的话 就需要logn的时间 每次对称缩小一个单位 知道 i==j
			break;
		swap1(arr, i, j);//交换两个不满足的值 交换后就满足了了性质

	}
	swap1(arr, lower, j);//之所以需要调换边界 是因为arr[j]相对于之前的tag（注意之前的i j交换了对应的值） 他更大 所以之前排好序的部分是不会动的
	//进一步缩小范围
	do_quickSort4(arr, lower, j - 1);
	do_quickSort4(arr, j + 1, upper);
}
//这个是快速排序的接口
template<typename t> void QuickSort(t *arr, int sz)
{
	do_quickSort(arr, 0, sz - 1);
}
template<typename t> void QuickSort2(t *arr, int sz)
{
	do_quickSort2(arr, 0, sz - 1);
}
template<typename t> void QuickSort3(t *arr, int sz)
{
	do_quickSort3(arr, 0, sz - 1);
	
}
template<typename t> void QuickSort4(t *arr, int sz)
{
	do_quickSort4(arr, 0, sz - 1);
	insert_sort(arr, sz);//使用插入排序
}
template<typename t> void QuickSort5_MinRescursion(t *arr, int sz)
{
	do_quickSort_MinRecursion<t>(arr, 0, sz - 1);
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
//ordered十是保存已经排序的序列 i是第一段的起点 m是分界点 n是终点 
template<typename t> void do_MergeSort_Recursion_process(t *arr,int i,int m,int n){
	t *ordered = new t[n-i+1];//创一个保存归并结果的数组
	int s1b = i;
	int s2b = m + 1;
	int k=0;//临时数组起始写入位置
	for (; s1b <= m && s2b <= n; ++k)
	{
		if (arr[s1b] < arr[s2b])
			ordered[k]=arr[s1b++];
		else
			ordered[k] = arr[s2b++];
	}
	if (s1b <= m)
		for (int i = 0; i <= m - s1b; ++i)
			ordered[k + i] = arr[s1b + i];
	if (s2b <= n)
		for (int i = 0; i <= n - s2b; ++i)
			ordered[k + i] = arr[s2b + i];
	int q = 0;
	int j = i;
	for (; j <= n; ++q, ++j)
		arr[j] = ordered[q];
	delete[] ordered;//将临时的数组的复制到arr对应的边界位置
}
template<typename t> void do_MergeSort_Recursion(t *arr,int sz,int begin,int end)
{
	
	int m;
	if (begin == end)
	{
		//ordered[begin] = arr[begin];
	}
	else
	{
		m = (begin + end) / 2;
		do_MergeSort_Recursion<t>(arr,sz, begin, m);//分解
		do_MergeSort_Recursion<t>(arr, sz, m + 1, end);//分解
		do_MergeSort_Recursion_process<t>(arr,begin, m, end);//合并这两组
	}

}
template<typename t> void MergeSortRescursion(t *arr, int sz)
{
	
	do_MergeSort_Recursion<t>(arr,sz, 0, sz - 1);
}
//计数排序 需要保证arr的每一个元素小于max
template<typename t=int> void CountingSort(int max,t *arr, int sz)
{

	int *count = new int[max];//这个数组用于登记对应的位置
	t *result = new t[sz];//保存结果的临时数组
	memset(count, 0, sizeof(int)*max);
	for (int i = 0; i < sz; ++i)
		count[arr[i]]++;//arr[i] 对应count的第arr[i]个元素 索引为arr[i]-1
	//反向填一次表
	//count[0] = 1;
	for (int i = 1; i < max; ++i)
		count[i] += count[i - 1];//公式定义 反向表=原表[i]（就是为了跳过元素位置）+反向表[i-1]
	for (int i = sz - 1; i >= 0; --i)
	{
		result[count[arr[i]] - 1/*-1是E为了能够把地址减回来 因为我们之前创建count是对应的第arr[i]个元素*/] = arr[i];//根据记录把对应的元素复制到原来的；详细的解释见CountingSortForRadixSort
		count[arr[i]]--;
	}
	for (int i = 0; i < sz; ++i)
		arr[i] = result[i];
		
	delete[] result;
	delete[] count;
}
//拓扑排序见GrapMartix
//基数排序
//获取x中第n位（数字）的数字
int getDigit(int x, int n)
{
	int arr[] = { 1,1,10,100,1000 };
	return ((x / arr[n]) % 10);
}
//多次基数排序 expindex就是依据第几位排序
template<typename t> void CountingSortForRadixSort(t *arr,int sz, int expIndex)
{
	int k = 9;//这一趟的基数排序桶的编号只有0~9
	int *base = new int[sz];//这个是保存临时排序的数组
	int *bucks = new int[k + 1];//桶子
	int i;
	memset(bucks, 0, sizeof(int)*(k + 1));//设置初始值
	for (i = 0; i < sz; ++i)
	{
		int index = getDigit(arr[i], expIndex);//获取数字
		bucks[index]++;//计数器+1
	}
	for (i = 1; i <= k; ++i)
	{
		bucks[i] += bucks[i - 1];//有个公式见计数排序 可以保留多少位给具有相同关键字的数字 例如 桶0~9  1 0 0 0 3 4 0 0 1 0 关键字为0
		/*
		关键字（桶序号） 起始点    保留位数     起始点=保留位数-1（前提是桶内有元素） 我知道了前面需要多少个位置
					0		0	1
					1		X	1
					2		X	1
					3		X	1
					4		3	4
					5		7	8
					6		X	8
					7		X	8
					8		X	9
					9		9	9
		*/
	}
	for (i = sz - 1; i >= 0; --i)
	{
		int d = getDigit(arr[i], expIndex);//获取桶的顺序
		base[bucks[d] - 1] = arr[i];//根据每个桶中包含有具有相同关键字的排队进入
		bucks[d]--;
	}
	//更新数组
	for (i = 0; i < sz; ++i)
		arr[i] = base[i];
	delete[] base;
	delete[] bucks;
}
template<typename t> void RadixSort(t *arr, int sz,int maxdigit/*最大的位数*/)
{
	int i;
	for (i = 0; i < maxdigit; ++i)
	{
		CountingSortForRadixSort(arr, sz, i + 1);
		int j;
		for (j = 0; j < sz; ++j)
			printf("%5d", arr[j]);
		printf("\n");
	}
}
// //统计排序所用的时间
// #include <Windows.h>
// template<typename t,typename fcn> double getRunningTime(t *arr,int sz,fcn funct)
// {
// 	LARGE_INTEGER begtime, endtime, freq;
// 	QueryPerformanceCounter(&begtime);
// 	QueryPerformanceFrequency(&freq);
// 	funct(arr, sz);
// 	QueryPerformanceCounter(&endtime);
// 	return (double)((endtime.QuadPart - begtime.QuadPart) / freq.QuadPart);
// }
//堆排序代码
//这里使用大堆
//向下调整 将最大的
template<typename _ty> void HeapSort_Modify_TopDown(_ty *arr,int lower, int upper)
{
	int parent = lower;
	int child= parent * 2 + 1;
	_ty tempv = arr[lower];//保存要冲新修改的值
	while (child <= upper)
	{
		if (child + 1 <= upper && arr[child] < arr[child + 1])
			++child;//将最大的值往上提
		if (arr[child] <= tempv) break;
		//swap1<_ty>(arr, child, parent);//交换两个值 不必交换 因为比较的是tempv 我只需要吧比tempv大的往上提 凡是大于或等于tempv的都向上提
		arr[parent] = arr[child];
		parent = child;
		child = parent * 2 + 1;
	}
	if (parent <= upper && parent >= lower)
		arr[parent] = tempv;
}
template<typename _ty> void HeapSort(_ty *arr, int sz)
{
	for (int i = sz/2; i > 0; --i)//建立一个大堆 i是起点的位置 只需要从1/2的位置排序就可以了
	{
		HeapSort_Modify_TopDown<_ty>(arr, i, sz-1);
	}
	for (int i = sz - 1; i > 0; --i)
	{
		HeapSort_Modify_TopDown<_ty>(arr, 0, i);
		swap1<_ty>(arr, 0, i);
	}
}
//统计排序所用的时间
#ifdef _WIN32
#include <Windows.h>
template<typename t,typename fcn> double getRunningTime(t *arr,int sz,fcn funct)
{
	LARGE_INTEGER begtime, endtime, freq;
	QueryPerformanceCounter(&begtime);
	QueryPerformanceFrequency(&freq);
	funct(arr, sz);
	QueryPerformanceCounter(&endtime);
	return (double)((endtime.QuadPart - begtime.QuadPart) / freq.QuadPart);
}
#elif __linux__
#include <ctime>
template<typename t,typename fcn> double getRunningTime(t *arr,int sz,fcn funct)
{
	clock_t  begin_tm = clock();
	funct(arr, sz);
	clock_t  end_tm = clock();
	return end_tm - begin_tm;
}
#endif