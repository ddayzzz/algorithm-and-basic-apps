#include <string>
#include <iostream>
#include <vector>
//˼·��Դ http://blog.csdn.net/liukx940818/article/details/44204411
//��֪����ô���� �����������޷�ͨ�� 
using namespace std;
char c[80002];
int main()
{
	//ֻ�����ڷ���ſ���
	int n;
	scanf("%d", &n);
	scanf("%s", &c[1]);

	int l = 1;
	int u = n;
	int ans=0;
	int sigle=0;
	while (l < u)
	{
		int left;
		int f = u;
		while (f >= l && c[f] != c[l])--f;
		if (f == l)
		{
			
			++sigle;
			//������ҵ���һ��ֻ��һ���ľ���Ҫ��������Ƶ��յ� ֻ������������
			if (n % 2 == 0 || sigle >= 2)
			{
				ans = -1;
				break;
			}
			else
			{
				ans += (n / 2 + 1) - l;
			}
			++l;
			continue;
		}
		//���н���
		if (f < u)
		{
			int cnt = 0;
			int cha = f + 1;
			while (cha <= u)
			{
				char t = c[cha];
				c[cha] = c[f];
				c[f] = t;
				++cnt;
				f = cha;
				cha = f + 1;
			}
			ans += cnt;
		}
		--u;
		++l;
	}
	if (ans == -1)
	{
		printf("Impossible");
	}
	else
	{
		printf("%d", ans);
	}
	
	return 0;
}
