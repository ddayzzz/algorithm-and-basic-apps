#include "UnionFind.hpp"
int main()
{
    	
	UnionFind<int> uf(12);
	uf.Union(9, 7);
	uf.print_ids();
	uf.Union(7, 5);
	uf.Union(5, 3);
	uf.print_ids();
	uf.Union(3, 0);
	uf.Union(10, 8);
	uf.print_ids();
	uf.print();
	bool f1 = uf.find(11, 5);
	bool f2 = uf.find(0, 5);
}