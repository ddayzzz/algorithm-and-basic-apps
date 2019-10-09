#include "stdio.h"
//这个是数组的大小 也是任务的数量
const int n =7;
#include <algorithm>
const int N=100000;
//int t[N]={3,5,7,9,10};//持续的时间+起始位置 
//int s[N]={1,2,4,6,8};//起始的位置 
//测试数据二
int t[N]={4,6,8,11,14,18,20};//持续的时间+起始位置 
int s[N]={1,3,5,7,10,12,17};//起始的位置 
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
	int t=0;//t是最后一次的工作的位置结束的位置 
	for(;pos < n;++pos)
	{
		if(t < tasks[pos].start)
		{
			++cnt;
			t=tasks[pos].end;//更新为下一个位置 
		}
		//如果t不能<=tasks[pos].start 忽略t 
	}
	printf("%d",cnt);
	return 0;
} 
