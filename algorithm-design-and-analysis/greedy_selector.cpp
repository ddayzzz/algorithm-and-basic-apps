
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;
 
typedef struct {
    int start;
    int end;
} activity;


void GreedSlector(int n, activity *sf)
{
	bool A[11] = {};
	A[0] = true;
	int j = 0;
	for (int i = 1; i <= n; i++) {
		if(sf[i].start > sf[j].end){
            A[i] = true;
            j = i;
        }else{
            A[i] = false;
        }
	}
	cout << "安排的活动如下\n";
	for(int i=0;i<n;++i)
    {
        if(A[i]){
            cout << "Act "<< setw(2) << i + 1 << ", Start: " << setw(2) << sf[i].start << ", End:" << setw(2)<< sf[i].end << "\n";
        }
    }
}


activity activities[11] = {
    {1,4},
    {3,5},
    {0,6},
    {5,7},
    {3,8},
    {5,9},
    {6,10},
    {12,14},
    {2,13},
    {8,12},
    {8,11}
};
int main()
{
    cout << "11个活动的开始时间和结束时间原始排列如下：\n";
	for(int i=0;i<11;++i)
    {
        cout << "Act "<< setw(2) << i + 1 << ", Start: " << setw(2) << activities[i].start << ", End:" << setw(2)<< activities[i].end << "\n";
    }
	sort(activities, activities + 11, [](activity &lhs, activity &rhs){return lhs.end < rhs.end;});
	cout << "11个活动的开始时间和结束时间按结束时间按非减序列排列如下：\n";
	for(int i=0;i<11;++i)
    {
        cout << "Act "<< setw(2) << i + 1 << ", Start: " << setw(2) << activities[i].start << ", End:" << setw(2)<< activities[i].end << "\n";
    }
	GreedSlector(11, activities);
    return 0;
}
