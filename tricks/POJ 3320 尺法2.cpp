#include "stdio.h"
#include <map>
#include <algorithm>
#include <set>
using namespace std;
map<int, int> se;//��ʾҳ��->ʣ����Ŀ�ļ���
const int MAXN = 1000001;
int P[MAXN] = { 0 };//P[i]��ʾ����iҳ��֪ʶ���ID 
int main()
{

	int N;
	scanf("%d", &N);
	
	int mix = N;
	for (int i = 0; i<N; ++i)
	{
		scanf("%d", P + i);
	}
	set<int> aid;
	for (int i = 0; i < N; ++i)
		aid.insert(P[i]);//���Ŀ���ǻ�ȡ֪ʶ������� ����ȥ�ظ� 
	int start = 0;//��� 
	int e = 0;//�յ� 
	//��ȡ��˼·�������s��ʼ ��e �����Ķ��� ��ô��s+1��ʼ�Ļ� ������Ҫ�Ķ���e+1 ������e��ҳ��ſ��� �ҵ�Ŀ�����ҵ���Сֵ �����Ҿ���Ҫ��ǰ����ȡ�ܹ�������С������ҳ��ĳ��� 
	while (1)
	{
		int num = 0;
		while (e < N && num < aid.size())
		{
			if (se[P[e++]]++ == 0)//�����һ���µ�֪ʶ�� ��ô�͸��¼���num 
			{
				++num;
			}
		}
		if (num < aid.size()) {
			break;//��num����С����Ŀ�ĸ��� ��ʾe�Ѿ������յ��� �����˳� mix������С��ֵ 
		}
		mix = min(mix, e - start);//ע�� ����e-start ��Ϊwhille�˳� ����Ҫ����Ҫ+1. ���е������ʾ�Ѿ��ҵ����Ķ����еĳ��� ������Ҫ������Сֵ  ++starts 
		if (--se[P[start++]] == 0)//���������һ��֪ʶ�� ��ô�Ѿ��������������-1 
		{
			--num;
		}
	}
	printf("%d", mix);
	return 0;
}
