

//쳲���������
//�����ַ ��ʼλ�� ĩβλ�� �ؼ��֣�ע���1��ʼ�ģ�
template<typename _ty> int fibnonacci_find(_ty *arr, int i, int n, int key)
{
	//thinking from http://blog.csdn.net/shenbo2030/article/details/44559937
	int fibnonacci1[] = { 0,1,1,2,3,5,8,3,21,34 };//����쳲���������+
	int low = i;//�������ʼ��λ��
	int upper = n;//�Ͻ��λ��
	int k = 0;//쳲��������е�λ��
	while (fibnonacci1[k] < n+1)
	{
		++k;//�����k����������С���ܺ͵ĺ�һ��λ��
	}
	for (int buzu = n; buzu < fibnonacci1[k]-1; ++buzu)
	{
		arr[buzu] = arr[n];//�������λ���������һ��Ԫ��
	}
	while (low <= upper)
	{
		int mid = low + fibnonacci1[k - 1] - 1;//ȷ���յ�ֵ Լ0.618��λ��
		if (key < arr[mid])
		{
			--k;
			upper = mid -1;
		}
		else if (key > arr[mid])
		{
			k = k - 2;//λ��
			low = mid + 1;//�����½�
		}
		else {
			if (mid <= n)
				return mid;
			else return n;//������ڲ�ȫ��λ�� ����ֱ�ӷ���n

		}
	}
	return -1;
}
//��ֵ����
template<typename _ty> int insert_find(_ty *arr,_ty key, int lower, int upper)
{
	//��Щ�����ڵ����ֻ�������� �����Ǵ�0��ʼ��
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