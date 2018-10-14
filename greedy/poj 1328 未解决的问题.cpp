#include "stdio.h"
#include "stdlib.h"
#include <cmath>
#define N 1001
#include <algorithm>
struct point {
	double x; double y;
	double minx; double maxx;

};
point points[N];
//POJ 1328
//̰���㷨 ����Ϊ�ǿ��Ե� ���ǻ��ǲ��� ����� 
int res[N];
int np, d;
bool cmp(const point &l, const point &p)
{
	return l.x < p.x;
}
bool set_min_xpoint(point *dest)
{
	int mm, mmmax;
	bool flag = false;
	if (dest->y > d)
	{
		flag = true;
	}
	else
	{
		int sr = sqrt(d*d-dest->y * dest->y);
		dest->minx = dest->x- sr;
		dest->maxx = dest->x+ sr;
		flag = false;
	}
	return flag == false;
}
int main()
{
	int pos = 0;
	while (~scanf("%d %d", &np, &d) && (np != 0 && d != 0))
	{
		bool res1 = true;
		for (int i = 0; i<np; ++i)
		{
			scanf("%lf %lf", &points[i].x, &points[i].y);
			if (!set_min_xpoint(&points[i]))
			{
				res1 = false;
				continue;
			}
			//printf("---%d %d\n", points[i].minx, points[i].maxx);
		}
		if (res1 == false)
		{
			printf("Case %d: %d\n", ++pos, -1);
			continue;
		}
		std::sort(points, points + np, cmp);
		/*
		int sum = 1;
		for (int i = 0; i < np - 1; ++i)
		{
			if (points[i + 1].minx >= points[i].minx && points[i + 1].minx <= points[i].maxx)
			{
				--sum;
			}
		}
		*/
		//ѡȡ֮ǰ�����״��λ�� Ȼ�������һ������˵��Ƿ��ڵ�ǰ���ұ߽�ģ�1.�ұߣ���ô�ڵ�ǰλ�õ��ұ߷����״�
		//2.��ߣ���ô�϶��ǿ��Ը��ǵ�
		//�����һ����λ�õ��ұ߽���֮ǰ�����״��λ�����  ��ô��Ҫ����������λ�÷����״� ��ô֮ǰ�Ķ����Ը�����
		//������ұ�Ҳ�ڸ��Ƿ�Χ��
		int sum = 1;
		int right = points[0].maxx;
		for (int i = 0; i < np - 1; ++i)
		{
			if (points[i + 1].minx > right)
			{
				++sum;
				right = points[i + 1].maxx;
			}
			else if(points[i+1].maxx < right)
			{
				right = points[i + 1].maxx;
			}
		}
		//++sum; 
		//*/
		
		printf("Case %d: %d\n", ++pos, sum);
	}

	return 0;
}
