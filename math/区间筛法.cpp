#include "stdio.h"
//thinking from http://www.cnblogs.com/nowandforever/p/4515612.html
//����ɸ�� ��Ҫ�������[a...b)����������
/*
ԭ��: �ж��Ƿ������������жϴ�2...sqrt(n)�Ƿ���Ա�n����(ɸ��һ��) Ȼ����ɸ����[a...sqrt(b)]��Χ�ڵ��������޳�
*/
#define N 5000
bool prime[N];//��Ŵ������
bool prime_small[N];//����޽�������
//�ж��Ƿ�������
bool isprime(int n)
{
	for (int i = 2; i*i <= n; ++i)
	{
		if (n % i == 0)
			return false;
	}
	return true;
}
//ɸѡ�����i..u��� 
void getPrime(int l, int u)
{
	//ע�� ��Ҫ����ƫ�� ��i�����������i-l��λ��
	//�����Χ��[l...u)������
	//��ɸ��һ��
	for (int i = 0; i*i <= u; ++i) prime_small[i] = 1;//Ĭ��ȫ������
	for (int i = 0; i<u - l; ++i) prime[i] = 1;
	for (int i = 2; i*i <= u; ++i)
	{
		if (isprime(i))
		{
			for (int j = i * 2; j*j <= u; j = j + i) prime_small[j] = 0;
			int multi = 2;//Ĭ�ϵı���
			//int calc = (l + i - 1) / i;
			int calc = ((l + i) % i == 0 ? ((l + i - 1) / i) : (l + i) / i);//�õ���l ��ӽ��ı��� ��С�ı���������2 �����������d   d*i >=l+i-1 d>=(l+i-1) / i   ����l+i������i�����,������ ��Ҫ����һ������ ���ⱻ����-1�Ϳ�����Сһ��;�粻����-1�в���Ҳ�޷�
			//���ǵ�һ��ʽ�Ӽ��һЩ
			if (calc > multi)
				multi = calc;
			for (int j = i * multi; j<u; j = j + i) prime[j - l] = 0;
		}

	}
	for (int i = 0; i < u - l; ++i)  //ͳ�Ƹ���
		if (prime[i])
			printf("%d ", i + l);
}
int main()
{
	getPrime(20,500);
}
