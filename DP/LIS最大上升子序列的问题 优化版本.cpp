
#include "stdio.h"
#include <algorithm>
#include "string.h" 

//������нϵ͸��Ӷȵ�������������е����� 
//dp[i] ��ʾ����Ϊi+1������������ĩβԪ�ص���Сֵ ��С��Ԫ��ӵ�еĳ�Ϊ�����������е����� 
const int N = 11;

int a[N] = { -5,-3,0,-9,-7,-18,-17,3,6,9,10 };
const int INF = 655;
int dp[N];

int main()
{
	//memset(dp, INF, N);//memset������ASCIIֵ �����ﲻ��
	for (int i = 0; i < N; ++i)
	{
		dp[i] = INF;
	}
	int n = N;
	for (int i = 0; i<n; ++i)
	{
		int lower = 0;
		int upper = n;
		while (lower <= upper)
		{
			int mid = (lower + upper) / 2;
			if (dp[mid] < a[i])
				lower = mid + 1;
			else if (dp[mid] > a[i])
				upper = mid - 1;
			else { lower = mid; upper = mid + 1; }
		}
		dp[lower] = a[i];//�ҵ��߽� ����Ҳʹ��lower_bound  ͬ�·��Ľ��� ��ֵdp[i]����ľ��ǵ�������i��λ�� �ܱ���������ĩβԪ�ص���Сֵ 
	}
	int *r = std::lower_bound(dp, dp + n, INF);
	printf("%d\n", r - dp);//lower_boundѰ�ҵ�һ�����Բ����INF��λ�� ���ص�λ��-1�������һ��������Ԫ�ص�λ�� ��Ϊ����dp�����ǵ����� Ȼ���ȥ��ʼλ�þ����ܸ���
	return 0;
}
