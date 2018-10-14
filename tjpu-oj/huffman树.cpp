#include <iostream>
#include <queue>
#include <vector>
#include <numeric>
#include <functional>
int main() {
	std::priority_queue<int,std::vector<int>,std::greater<int>> que;
	int num;
	std::cin >> num;
	
		for (int i = 0; i<num; ++i)
		{
			int h;
			std::cin >> h;
			que.push(h);
		}
		long total = 0;
		while (!que.empty())
		{
			int fir = que.top();
			que.pop();
			if (que.empty())
			{
				break;
			}
			int sec = que.top();
			que.pop();
			total += sec + fir;
			que.push(sec + fir);
		}
		std::cout << total << std::endl;
	
	return 0;
}
