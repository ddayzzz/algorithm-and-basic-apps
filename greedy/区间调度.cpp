#include "stdio.h"
//���������Ĵ�С Ҳ�����������
const int n =7;
#include <algorithm>
const int N=100000;
//int t[N]={3,5,7,9,10};//������ʱ��+��ʼλ�� 
//int s[N]={1,2,4,6,8};//��ʼ��λ�� 
//�������ݶ�
int t[N]={4,6,8,11,14,18,20};//������ʱ��+��ʼλ�� 
int s[N]={1,3,5,7,10,12,17};//��ʼ��λ�� 
struct task
{
	int start;
	int end;
	

};


task tasks[n];
int main()
{
	 for(int i=0;i<n;++i)
	 {
	 	tasks[i].start=s[i];
	 	tasks[i].end=t[i];
	 }
	 std::sort(tasks,tasks+n,[](const task &l,const task &r){
	 	return l.end < r.end;});
	int cnt=0;
	int pos=0;
	int t=0;//t�����һ�εĹ�����λ�ý�����λ�� 
	for(;pos < n;++pos)
	{
		if(t < tasks[pos].start)
		{
			++cnt;
			t=tasks[pos].end;//����Ϊ��һ��λ�� 
		}
		//���t����<=tasks[pos].start ����t 
	}
	printf("%d",cnt);
	return 0;
} 
