#include "stdio.h"
#include <algorithm>
#include <cmath>
#include <vector>
//其实是统计 
using namespace std;
struct node {
	int dis;
	int dir;
	bool ill;
	node(int d, int di, bool i) :dis(d), dir(di), ill(i) {
	}
};
vector<node> nn;
const int L = 2;
const int R = 3;
int main()
{
	int N;
	int ill = 1;
	int pos; int dir;
	scanf("%d", &N);
	int read;
	for (int o = 1; o <= N; ++o)
	{
		scanf("%d", &read);
		if (read < 0)
		{
			pos = -read;
			dir = L;
		}
		else
		{
			pos = read;
			dir = R;
		}
		if (o == 1)
		{
			nn.emplace_back(pos, dir, true);
		}
		else nn.emplace_back(pos, dir, false);

	}
	sort(nn.begin(), nn.end(), [](const node &n, const node &r) { return n.dis < r.dis; });
	int bb;
	for (bb = 0; bb <N; ++bb)
	{
		if (nn[bb].ill == true)
			break;
	}

	for (int i = 0; i<bb; ++i)
	{
		if (nn[i].dir == R)
			++ill;
	}
	for (int b = bb + 1; b<N; ++b)
		if (nn[b].dir == L)
			++ill;
	printf("%d", ill);
	return 0;
}
