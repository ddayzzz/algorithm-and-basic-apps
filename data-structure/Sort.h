#include <string.h>

//����һ����������Ԫ�صĽ�������
template<typename t> void swap1(t* arr,int i,int j)
{
	t tmp = arr[j];
	arr[j] = arr[i];
	arr[i] = tmp;
}
//��������
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
		while (j > 0 && insert < newarr[j-1])//�ȽϴӺ��濪ʼ�Ƚ� ע����j-1 ��Ϊj���λ�û�û��Ԫ�ز��� �������Ǹ�Ĭ��ֵ ��������Ҫ�Ƚϵ����ȴ�[0��J-1]��Ԫ��
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
	//����Ҫ�����µĿռ�Ĳ�������
	for (int i = 1; i < sz; ++i)//ע���Ǵ�I=1��ʼ�� ��Ϊ������Ϊarr[1...1]�������
	{
		if (arr[i] < arr[i - 1])//һ���ҵ������λ�� ��ô���в�������
		{
			int tempv = arr[i];//������С��ֵ
			int j;
			for (j = i - 1; j >= 0 && arr[j] > tempv; --j)
				arr[j+1] = arr[j];
			arr[j + 1] = tempv;//�������λ�ø�ֵ
		}
		
	}
}
//���ֲ�������
template<typename t> void binarysort(t *arr, int sz)
{
	/*�������Ҫ����ռ���㷨 �ռ临�Ӷ�ΪOn
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
			//���ַ� ��Ԫ�ز��뵽С�ڵ���insert��ǰ��
			mid = (left + right) / 2;
			if (newarr[mid] > insert)
				right = mid - 1;
			else if (newarr[mid] <= insert)
				left = mid + 1;
		}
		for (int j = i; j > left; --j)
			newarr[j] = newarr[j - 1];//Ϊ�²����Ԫ����λ
		newarr[left] = insert;
	}
	for (i = 0; i < sz; ++i)
	{
		arr[i] = newarr[i];
	}
	delete[] newarr;
	*/
	//��Ϊ�������� ����ΪǮARR[0...I-1]������� ���Կ���ʹ�ö��������ҵ�����λ�� �������λ��lower
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
				else if (arr[mid] >= tempv)//�������ֵ <=mid ��ô�Ϳ����ھ�����ֵͬ������Ԫ�صģ���ʱupper==lower==mid) �������ǵݼ�upper ���Ա�֤�Ƴ�ѭ�� �����ܹ���֤lowerʱ��д��λ�á�ͬʱ ���ʱ��ͬԪ��Ҳ���Ա�֤
					upper = mid - 1;
			}
			
			for (int j = i-1; j >= lower; --j)
				arr[j+1] = arr[j];
			/*�ȼ�д��
			for (int j = i; j > lower; --j)
				arr[j] = arr[j-1];
			*/
			arr[lower] = tempv;

		}
	}
}
//ϣ������
template<typename t> void shellSort(t *arr, int sz)
{
	int insert;
	int gap = sz / 2;
	while (gap >= 1)
	{
		for (int i = gap; i < sz; ++i)//����Ϊgap��Ϊһ�飬ÿһ�������һ��Ԫ�ز��ܴ���sz
		{
			insert = arr[i];//�����ʾ���Ƚϵ�ֵ
			int j;
			//ģ�����һ����������
			for (j = i - gap/*��֮ǰ��һ��Ԫ�رȽ�*/; j >= 0 && insert < arr[j]/*����������Ԫ��<������˾*/; j = j - gap/*j��Ŀ��λ�õݼ�*/)
				arr[j + gap] = arr[j];//����Ԫ�ص�λ�� �ճ��ط���
			arr[j + gap] = insert;//�ڵ�һ������<=insert��Ԫ�ص�+gapλ�ò���Ԫ��
		}
		gap = gap / 2;//����gap����
	}
};
//ֱ��ѡ������
template<typename t> void directSelectSort(t *arr, int sz)
{
	int k;
	int i;
	for (i = 0; i < sz; ++i)
	{
		k = i;
		for (int j = i + 1; j < sz; ++j)
			if (arr[j] < arr[k])
				k = j;//ѡ����С��Ԫ�ص����� ���浽k
		//swap ����Ԫ��
		t temp = arr[i];//���浱ǰ��Ҫ�滻��Ԫ��
		arr[i] = arr[k];
		arr[k] = temp;
	}
}
//ð������
template<typename t> void BubbleSort(t *arr, int sz)
{
	int i, j;
	bool flag;
	for (i = 0; i < sz; ++i)
	{
		flag = false;//���ԭ���в���Ҫ���� ��ô��Ϊ�����������
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
//��β������
template<typename t> void ShakerSort(t *arr, int sz)
{
	int left=0, right=sz-1;
	int shift = 0;//�����������ÿһ�ε�ת�� �����Һʹ��ҵ���Ľ��������ת��
	while (left < right)//���left==right�Ͳ�����Ҫ�ȽϽ���
	{
		for (int i = left; i < right; ++i)//��������
		{
			if (arr[i + 1] < arr[i])
			{
				swap1(arr, i + 1, i);
				shift = i;//����shift��ֵ
			}
		}
		right = shift;//��С��һ�α仯�ıȽϵ�����
		for (int j = right; j > left; --j)
		{
			if (arr[j] < arr[j - 1])
			{
				swap1(arr, j, j - 1);
				shift = j;
			}
		}
		left = shift;//��С��һ�α仯�ıȽϵ�����
	}
}
//��������
template<typename t> void do_quickSort(t *arr, int left, int right)
{
	int i = left;
	int j = right;
	t pivot = arr[left];//��׼Ԫ��
	while (i < j)
	{
		while (i < j && arr[j] >= pivot) --j;//��j�ݼ���С�ڻ�׼��ֵ��λ�� Ϊʲôj�����أ���ΪҪȷ��i�����ߵ��Ͻ� ��ֹ����j < i�����
		if (i < j) arr[i] = arr[j];//swap1(arr, i, j);//�������ΪС�ڻ�׼��ֵ���˳���whileѭ�� �ͽ���i��j����Ӧ��ֵ
		while (i < j && arr[i] <= pivot) ++i;//��i��������һ�����ڻ�׼��ֵ��λ��
		if (i < j) arr[j] = arr[i];//����λ��
		//����֮�� pivot��Ӧ��λ����ߵ����� < pivot ���ұߵ�>pivot
		//�����εĽ������� ���ڵ�ֵ ��С�ڵ�ֵ�ý��� 
	}//�Ż��˶�αȽ� ��Ϊ��һ�ν���pivot����Ϊj��λ�� Ȼ���iѡ�������Ǹ�������Ҫ��pivot��i��λ�ý��� ����ֻ��Ҫ��arr[j]��λ�ø�Ϊarr[i]�Ͳ���Ҫ��θ�ֵpivot
	arr[i] = pivot;
	//int p;
	//for (p = 0; p < 10; ++p)
		//printf("%3d", arr[p]);
	//printf("\n");
	if (i != left) do_quickSort(arr, left, i - 1);//��[left,i-1]����������
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
//�����˵ݹ����
template<typename t> void do_quickSort_MinRecursion(t *arr, int low,int upper)
{
	int piv;
	while (low < upper)
	{
		piv = do_quickSort_MinRecursion_partition<t>(arr, low, upper);//����Ƿֿ���� ���ؽ����ı߽�piv��Ҳ����pivot�Ľ���λ�ã�
		do_quickSort_MinRecursion<t>(arr, low, piv - 1);//�ڶ���ߵ�λ�ý�������
		low = piv + 1;//�ڶ��ұߵ�����
	}
	//�������ò�����������С����
}
//����Ǵӵ�һ��Ԫ�ؿ�ʼɨ�� 
template<typename t> void do_quickSort2(t *arr, int lower, int upper)
{
	if (lower >= upper)
		return;
	int m = lower;//m�ǲ��Ե�ֵ ��ʾ�½�
	t temp = arr[lower];//����ǱȽϵ�ֵ
	for (int i = lower + 1; i <= upper;++i)//�Ƚ�arr[l+1,,,,u]��Χ�ڵ�����
	{
		if (arr[i] < temp)
		{
			swap1(arr, ++m, i);//���ǱȻ�׼ֵС�� ȫ��Ҫ���׼ֵ֮���һ��Ԫ�ؽ�����ע���ʱ�Ļ�׼ֵ������������1��
		}
	}
	swap1(arr, lower, m);//�����߽�ͻ�׼ֵ
	do_quickSort2(arr, lower, m - 1);//�ڶ��µĻ�׼ֵ���ҽ�������
	do_quickSort2(arr, m + 1, upper);
}
template<typename t> void do_quickSort3(t *arr, int lower, int upper)
{
	if (lower >= upper)
		return;
	int i, j;
	i = lower; j = upper+1;//���֮������Ҫ����һ��λ��
	t tag= arr[lower];//Ĭ�ϵĻ�׼ֵλ��
	while (true)
	{
		do { ++i; } while (i <= upper && arr[i] < tag);//������԰�i��������һ����С�ڻ�׼ֵ��λ��
		do { --j; } while (j >= lower && arr[j] > tag);//j�ݼ�����һ�������ڻ�׼ֵ��λ��
		if (i > j)//������ǵ�����λ�� ֱ���˳�ѭ�� �����ȫ������ȵĻ� ����Ҫlogn��ʱ�� ÿ�ζԳ���Сһ����λ ֪�� i==j
			break;
		swap1(arr, i, j);//���������������ֵ �������������������
		
	}
	swap1(arr, lower, j);//֮������Ҫ�����߽� ����Ϊarr[j]�����֮ǰ��tag��ע��֮ǰ��i j�����˶�Ӧ��ֵ�� ������ ����֮ǰ�ź���Ĳ����ǲ��ᶯ��
	//��һ����С��Χ
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
	swap1(arr, lower, randint(upper - lower+1));//�½��������λ�ý��� ���λ�ý��� i j֮��
	i = lower; j = upper + 1;//���֮������Ҫ����һ��λ��
	t tag = arr[lower];//Ĭ�ϵĻ�׼ֵλ��
	while (true)
	{
		do { ++i; } while (i <= upper && arr[i] < tag);//������԰�i��������һ����С�ڻ�׼ֵ��λ��
		do { --j; } while (j >= lower && arr[j] > tag);//j�ݼ�����һ�������ڻ�׼ֵ��λ��
		if (i > j)//������ǵ�����λ�� ֱ���˳�ѭ�� �����ȫ������ȵĻ� ����Ҫlogn��ʱ�� ÿ�ζԳ���Сһ����λ ֪�� i==j
			break;
		swap1(arr, i, j);//���������������ֵ �������������������

	}
	swap1(arr, lower, j);//֮������Ҫ�����߽� ����Ϊarr[j]�����֮ǰ��tag��ע��֮ǰ��i j�����˶�Ӧ��ֵ�� ������ ����֮ǰ�ź���Ĳ����ǲ��ᶯ��
	//��һ����С��Χ
	do_quickSort4(arr, lower, j - 1);
	do_quickSort4(arr, j + 1, upper);
}
//����ǿ�������Ľӿ�
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
	insert_sort(arr, sz);//ʹ�ò�������
}
template<typename t> void QuickSort5_MinRescursion(t *arr, int sz)
{
	do_quickSort_MinRecursion<t>(arr, 0, sz - 1);
}
//�鲢����
//�鲢�㷨�ĺϲ��㷨 ��һ������ԭ���� lowΪ��ʼ�ĵ�ַ mid
template<typename t> void do_mergeSort_hebing(t *arr,int low,int mid,int high)
{
	int i = low;//��һ�ε����е��±�
	int j = mid + 1;//�ڶ��ε������±�
	int k = 0;//����ʱ��źϲ����е��±�
	int *newarr = new t[high - low + 1];
	//ɨ���һ�θ��ڶ������� ֱ����һ��ɨ�����
	while (i <= mid && j <= high)
	{
		if (arr[i] <= arr[j])
		{
			newarr[k] = arr[i];
			++i;//����Сֵ�ĵ������С�����
			++k;//��ʱ���е��±����
		}
		else
		{
			newarr[k] = arr[j];//�����µ�ֵ
			++j;//ͬ��
			++k;//����k�������ҲҪ�仯
		}
	}
	//ע����ܻ���û��ɵ� ����Ĳ�����ǰ�����û��д�뵽�µı��е�Ԫ��д��
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
		arr[i] = newarr[k];//���¶�Ӧ��Ԫ���������ֵ
	delete[] newarr;
}
//�鲢����ķֽ��㷨
template<typename t> void do_mergeSort_divid(t *arr, int gap, int length)
{
	//gap��ʾ����ÿһ��ͬ���Ƚϵļ��
	/*     5    6    9    1    3     2   0    4       10
	gap=1    56        91         32        04        10
	����      56        19         23        04        10
	gap=2    ��5619��1569            ��2304��0234       10
	gap=4    01234569 10
	gap=8    0 1 2 3 4 5 6 9 10
	*/
	int i = 0;
	for (i = 0; i + 2 * gap - 1/* i+2*gap -1��ʾ���ǵ�һ����Ҫ�ϲ��� ���ֻ��һ����Ҫ�ϲ� ��ô���ѭ��ִ��һ��*/ < length; i = i + 2 * gap/*��һ���滻��һ�Ե���ʼλ��*/)
		do_mergeSort_hebing(arr, i, i + gap - 1, i + 2 * gap - 1);
	//�����������ӱ� ��Ϊ���ȵĴ�С�ǲ����������
	if (i + gap - 1 < length)
		do_mergeSort_hebing(arr, i, i + gap - 1, length - 1);
}
//���hi�ӿڵĺ���
template<typename t> void MergeSort(t *arr, int sz)
{
	for (int gap = 1; gap < sz; gap = gap * 2)
	{
		do_mergeSort_divid(arr, gap, sz);//ÿһ��gap����
	}
}
//orderedʮ�Ǳ����Ѿ���������� i�ǵ�һ�ε���� m�Ƿֽ�� n���յ� 
template<typename t> void do_MergeSort_Recursion_process(t *arr,int i,int m,int n){
	t *ordered = new t[n-i+1];//��һ������鲢���������
	int s1b = i;
	int s2b = m + 1;
	int k=0;//��ʱ������ʼд��λ��
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
	delete[] ordered;//����ʱ������ĸ��Ƶ�arr��Ӧ�ı߽�λ��
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
		do_MergeSort_Recursion<t>(arr,sz, begin, m);//�ֽ�
		do_MergeSort_Recursion<t>(arr, sz, m + 1, end);//�ֽ�
		do_MergeSort_Recursion_process<t>(arr,begin, m, end);//�ϲ�������
	}

}
template<typename t> void MergeSortRescursion(t *arr, int sz)
{
	
	do_MergeSort_Recursion<t>(arr,sz, 0, sz - 1);
}
//�������� ��Ҫ��֤arr��ÿһ��Ԫ��С��max
template<typename t=int> void CountingSort(int max,t *arr, int sz)
{

	int *count = new int[max];//����������ڵǼǶ�Ӧ��λ��
	t *result = new t[sz];//����������ʱ����
	memset(count, 0, sizeof(int)*max);
	for (int i = 0; i < sz; ++i)
		count[arr[i]]++;//arr[i] ��Ӧcount�ĵ�arr[i]��Ԫ�� ����Ϊarr[i]-1
	//������һ�α�
	//count[0] = 1;
	for (int i = 1; i < max; ++i)
		count[i] += count[i - 1];//��ʽ���� �����=ԭ��[i]������Ϊ������Ԫ��λ�ã�+�����[i-1]
	for (int i = sz - 1; i >= 0; --i)
	{
		result[count[arr[i]] - 1/*-1��EΪ���ܹ��ѵ�ַ������ ��Ϊ����֮ǰ����count�Ƕ�Ӧ�ĵ�arr[i]��Ԫ��*/] = arr[i];//���ݼ�¼�Ѷ�Ӧ��Ԫ�ظ��Ƶ�ԭ���ģ���ϸ�Ľ��ͼ�CountingSortForRadixSort
		count[arr[i]]--;
	}
	for (int i = 0; i < sz; ++i)
		arr[i] = result[i];
		
	delete[] result;
	delete[] count;
}
//���������GrapMartix
//��������
//��ȡx�е�nλ�����֣�������
int getDigit(int x, int n)
{
	int arr[] = { 1,1,10,100,1000 };
	return ((x / arr[n]) % 10);
}
//��λ������� expindex�������ݵڼ�λ����
template<typename t> void CountingSortForRadixSort(t *arr,int sz, int expIndex)
{
	int k = 9;//��һ�˵Ļ�������Ͱ�ı��ֻ��0~9
	int *base = new int[sz];//����Ǳ�����ʱ���������
	int *bucks = new int[k + 1];//Ͱ��
	int i;
	memset(bucks, 0, sizeof(int)*(k + 1));//���ó�ʼֵ
	for (i = 0; i < sz; ++i)
	{
		int index = getDigit(arr[i], expIndex);//��ȡ����
		bucks[index]++;//������+1
	}
	for (i = 1; i <= k; ++i)
	{
		bucks[i] += bucks[i - 1];//�и���ʽ���������� ���Ա�������λ��������ͬ�ؼ��ֵ����� ���� Ͱ0~9  1 0 0 0 3 4 0 0 1 0 �ؼ���Ϊ0
		/*
		�ؼ��֣�Ͱ��ţ� ��ʼ��    ����λ��     ��ʼ��=����λ��-1��ǰ����Ͱ����Ԫ�أ� ��֪����ǰ����Ҫ���ٸ�λ��
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
		int d = getDigit(arr[i], expIndex);//��ȡͰ��˳��
		base[bucks[d] - 1] = arr[i];//����ÿ��Ͱ�а����о�����ͬ�ؼ��ֵ��Ŷӽ���
		bucks[d]--;
	}
	//��������
	for (i = 0; i < sz; ++i)
		arr[i] = base[i];
	delete[] base;
	delete[] bucks;
}
template<typename t> void RadixSort(t *arr, int sz,int maxdigit/*����λ��*/)
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
// //ͳ���������õ�ʱ��
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
//���������
//����ʹ�ô��
//���µ��� ������
template<typename _ty> void HeapSort_Modify_TopDown(_ty *arr,int lower, int upper)
{
	int parent = lower;
	int child= parent * 2 + 1;
	_ty tempv = arr[lower];//����Ҫ�����޸ĵ�ֵ
	while (child <= upper)
	{
		if (child + 1 <= upper && arr[child] < arr[child + 1])
			++child;//������ֵ������
		if (arr[child] <= tempv) break;
		//swap1<_ty>(arr, child, parent);//��������ֵ ���ؽ��� ��Ϊ�Ƚϵ���tempv ��ֻ��Ҫ�ɱ�tempv��������� ���Ǵ��ڻ����tempv�Ķ�������
		arr[parent] = arr[child];
		parent = child;
		child = parent * 2 + 1;
	}
	if (parent <= upper && parent >= lower)
		arr[parent] = tempv;
}
template<typename _ty> void HeapSort(_ty *arr, int sz)
{
	for (int i = sz/2; i > 0; --i)//����һ����� i������λ�� ֻ��Ҫ��1/2��λ������Ϳ�����
	{
		HeapSort_Modify_TopDown<_ty>(arr, i, sz-1);
	}
	for (int i = sz - 1; i > 0; --i)
	{
		HeapSort_Modify_TopDown<_ty>(arr, 0, i);
		swap1<_ty>(arr, 0, i);
	}
}
//ͳ���������õ�ʱ��
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