

//斐波那契查找
//数组地址 起始位置 末尾位置 关键字（注意从1开始的）
template<typename _ty> int fibnonacci_find(_ty *arr, int i, int n, int key)
{
	//thinking from http://blog.csdn.net/shenbo2030/article/details/44559937
	int fibnonacci1[] = { 0,1,1,2,3,5,8,3,21,34 };//保存斐波那契数列+
	int low = i;//这个是起始的位置
	int upper = n;//上界的位置
	int k = 0;//斐波那契数列的位置
	while (fibnonacci1[k] < n+1)
	{
		++k;//将这个k递增到不会小于总和的后一个位置
	}
	for (int buzu = n; buzu < fibnonacci1[k]-1; ++buzu)
	{
		arr[buzu] = arr[n];//将不足的位置填入最后一个元素
	}
	while (low <= upper)
	{
		int mid = low + fibnonacci1[k - 1] - 1;//确定终点值 约0.618的位置
		if (key < arr[mid])
		{
			--k;
			upper = mid -1;
		}
		else if (key > arr[mid])
		{
			k = k - 2;//位于
			low = mid + 1;//提升下界
		}
		else {
			if (mid <= n)
				return mid;
			else return n;//这个属于补全的位置 所以直接返回n

		}
	}
	return -1;
}
//插值查找
template<typename _ty> int insert_find(_ty *arr,_ty key, int lower, int upper)
{
	//有些不存在的数字会出现问题 索引是从0开始的
	while(lower <=upper)
	{
		int mid = lower + (key - arr[lower])*(upper - lower) / (arr[upper] - arr[lower]);
		if (key > arr[mid])
			lower = mid + 1;
		else if (key < arr[mid])
			upper = mid - 1;
		else return mid;
	}
	return -1;
}