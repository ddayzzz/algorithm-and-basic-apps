#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
int main()
{
	int na, nb,n;
	std::vector<int> sa;
	std::vector<int> sb;
	while (std::cin >> na)
	{
		for (int i = 0; i < na; ++i)
		{
			std::cin >> n;
			sa.push_back(n);
		}
		std::cin >> nb;
		for (int i = 0; i < nb; ++i)
		{
			std::cin >> n;
			sb.push_back(n);
		}
		std::sort(sa.begin(), sa.end());
		std::sort(sb.begin(), sb.end());
		std::vector<int> bing(2000);
		std::vector<int> jiao(1000);
		std::vector<int> bu(1000);
		auto iter1 = std::set_intersection(sa.begin(), sa.end(), sb.begin(), sb.end(), jiao.begin());
		for (auto i = jiao.begin(); i != iter1; ++i)
			std::cout << *i << " ";
		std::cout << std::endl;
		auto iter2 = std::set_union(sa.begin(), sa.end(), sb.begin(), sb.end(),bing.begin());
		for (auto i = bing.begin(); i != iter2; ++i)
			std::cout << *i << " ";
		std::cout << std::endl;
		auto iter3 = std::set_difference(sa.begin(), sa.end(), sb.begin(), sb.end(), bu.begin());
		for (auto i = bu.begin(); i != iter3; ++i)
			std::cout << *i << " ";
		std::cout << std::endl;

	}
	return 0;
}
