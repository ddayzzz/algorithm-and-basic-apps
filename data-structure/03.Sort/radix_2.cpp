// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
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
//���������㷨(������)  ������Ԫ�ص�ַ, ��ʼ����, �������� , ������������λ��(����ɨ�����)
void radixSort(int arrp[], unsigned beg, unsigned end, unsigned d) 
{
	int i;
	int j, k;
	constexpr unsigned radix = 10;//���ƻ���
	int count[radix];//���������� ���������Կ������ֳ��ֵ�λ��
	//�ÿ�
	for (i = 0; i <10; ++i)
	{
		count[i] = 0;
	}
	int *sorted = (int*)malloc((end-beg+ 1) * sizeof(int));
	for (i = 1; i <= d; ++i)
	{
		for (k = beg; k <= end; ++k)
		{
			count[getDigit(arrp[k],i)]++;//ͳ�Ƶ�ǰɨ�������Iλ��λ��
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

	int *bucket = (int*)malloc((end - begin + 1) * sizeof(int));  //����Ͱ�Ŀռ俪��   

																  //���շ����׼���ν����������
	for (int k = 1; k <= d; ++k)
	{
		//�ÿ�
		for (i = 0; i < radix; i++)
		{
			count[i] = 0;
		}
		//ͳ�Ƹ���Ͱ����ʢ���ݸ���
		for (i = begin; i <= end; i++)
		{
			count[getDigit(arr[i], k)]++;
		}
		//count[i]��ʾ��i��Ͱ���ұ߽�����
		for (i = 1; i < radix; i++)
		{
			count[i] = count[i] + count[i - 1];
		}
		//����������װ��Ͱ(ע��װ��ʱ��ķ��似��)
		for (i = end; i >= begin; --i)        //����Ҫ��������ɨ�裬��֤�����ȶ���   
		{
			j = getDigit(arr[i], k);        //����ؼ���ĵ�kλ�����֣� ���磺576�ĵ�3λ��5   
			bucket[count[j] - 1] = arr[i]; //�����Ӧ��Ͱ�У�count[j]-1�ǵ�j��Ͱ���ұ߽����� 
			--count[j];               //��ӦͰ��װ������������һ  
		}

		//ע�⣺��ʱcount[i]Ϊ��i��Ͱ��߽�  

		//�Ӹ���Ͱ���ռ�����
		for (i = begin, j = 0; i <= end; ++i, ++j)
		{
			arr[i] = bucket[j];
		}
	}
	free(bucket);
}
//�������� ��д��
void my_radix_sort(int arr[], int beg, int end, int d)
{
	constexpr int base = 10;//����
	int count[base];//������鱣��Ҫ�������ֵĸ���
	int copied_count[base];
	int fornextd[base];
	int **sorted = (int**)malloc(sizeof(int*)* base);//���ڱ������ֵ�Ͱ
	int i, j, k,t;
	
	//��ʼ���Ƹ���������
	for (i = 1; i <=base; ++i)
	{
		count[i - 1] = 0;
		copied_count[i - 1] = 0;
		fornextd[i - 1] = 0;
	}
	//ͳ�Ƹ������ֳ��ֵ����� һ�ν�ʡ�ռ�ط�������
	for (i = 1; i <= d; ++i)
	{
		for (j = beg; j <= end; ++j)
		{
			k = getDigit(arr[j], i);
			++count[k];
			++copied_count[k];
		}
	}
	
	
	//ͳ��ÿ��������Ҫ�Ŀռ�
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
	//��������������
	//��������
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
			//copy����Ԫ��
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
			//copy����Ԫ��
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
//�鲢���� ����
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
		//ż����
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
	/* Ͱ����
	int arr[11] = { 0,4,2,5,1,0,8,5,2,5,19 };//���������
	int con[20] = { 0};//���ֵĴ���
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
	/* ��������
	*/
	int  br[10+5] = { 1,1,3,1,20, 80, 90, 589, 998, 965,90, 852, 123, 456, 789 };
	lsdradix_sort(br, 0, 9+4, 3);
	/*��������
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

