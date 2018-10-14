//最大子序列的和
#include <iostream>
//通用的函数
int max1(int a, int b) { return (a > b ? a : b); }

int MaxSubQueue_Value(const int *seq, int i,int e)
{
	if (i == e)
	{
		if (seq[i] > 0)
			return seq[i];
		else
			return 0;
	}
	int mid = (e + i) / 2;
	int left = MaxSubQueue_Value(seq, i, mid);
	int right = MaxSubQueue_Value(seq, mid + 1, e);
	int leftsum = 0; int maxleftsum = 0;
	int rightsum = 0; int maxrightsum = 0;
	for (int h = mid; h >= i; --h)
	{
		leftsum += seq[h];
		if (leftsum > maxleftsum)maxleftsum = leftsum;
	}
	for (int h = mid+1; h <= e; ++h)
	{
		rightsum += seq[h];
		if (rightsum > maxrightsum)maxrightsum = rightsum;
	}
	return max1(max1(maxleftsum, maxrightsum), maxleftsum + maxrightsum);
}
int main(){
    int a[] = { -2, 11, 8, -4, -1, 16, 5, 0};
    int v = MaxSubQueue_Value(a, 0, 8); // 35
    std::cout << "Max subseq sum:"<<v << std::endl;
}