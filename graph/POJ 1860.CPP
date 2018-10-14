#include "stdio.h"
#include <algorithm>
using namespace std;
const int MAXN = 105;
double R[MAXN][MAXN] = { 0.0 };//�����i��j�ı���
double C[MAXN][MAXN] = { 0.0 };//����������
double gra[1000];
int N;//������������
int M;//�һ�����Ŀ
int S;//����Ǯ������
double V;//����Ǯʵ�ʽ��
//thinking from http://blog.csdn.net/yslcl12345/article/details/50574213
bool floyd()
{
	double d[MAXN];
	int i, j, k;
	for (i = 1; i <= N; i++) d[i] = gra[i];
	//d��������Ӷһ����͵�i���������������ʵ���
	for (k = 1; k<=N; ++k)
	{
		for (i = 1; i<=N; ++i)
		{
			for (j = 1; j<=N; ++j)
			{
				if ((gra[i] - C[i][j])*R[i][j] > gra[j]) 
					gra[j] = (gra[i] - C[i][j])*R[i][j];//�����i�һ��õ���ǮȻ��һ�λj��ǮҪ��ֱ�Ӵ�ĳһ���һ��㵽j�Ķһ��ļ۸�Ҫ�� ��ô����Ҫ�滻
			}
		}

	}
	for (i = 1; i<=N; ++i)
	{
		if (d[i]<gra[i])return true;//������ֵõ�����ʵ�Ľ��Ҫ�ߣ���ô��YES
	}
	return false;

}
int main()
{
	scanf("%d %d %d %lf", &N, &M, &S, &V);
	for (int i = 0; i<M; ++i)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		scanf("%lf", &R[a][b]);
		scanf("%lf", &C[a][b]);
		scanf("%lf", &R[b][a]);
		scanf("%lf", &C[b][a]);
	}
	gra[S] = V;
	floyd();//��һ���������ܶһ��õ���Ǯ���б�
	//��ô����Ŀ���ǣ��п�����Щ������̫С������ڶ������ӵıȵ�һ���࣬��ô����n�Σ������ǵ�n�ε�ת��>����
	if (floyd())//�ڶ�����Floyd�е�����ѭ������ִ�У�Ȼ����Ҫ�ж��Ƿ��ܸ����������Ҳ���Ǵ���һ��������
		printf("YES\n");
	else
		printf("NO\n");
	return 0;
}
