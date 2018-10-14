
#include <cstdio>
template<typename _Ty> class UnionFind
{
private:
	int size;
	int *ids;//这个是保存某个节点对应的根节点 当ids[i]=i表示的就是i是根节点.
	//不过我们有一个更好地方法 sizecount初始化每个ID为1 表示有1个点
public:
	explicit UnionFind(int sz) :size(sz)
	{
		if (sz > 0)
		{
			ids = new int[sz];
			
			for (int i = 0; i < sz; ++i)
			{
				ids[i] = -1;//默认所有的根节点初始化为-1 
			}
		}
		else
		{
			ids = nullptr;
		}
			
	}	  
	//寻找
	int findRoot(int i)
	{
		if (ids[i] < 0)//如果是根节点
			return i;
		return ids[i] = findRoot(ids[i]);//路径压缩 将i的父亲改为他的爷爷
	}
	void Union(int p, int q)
	{
		int pp = findRoot(p);
		int qp = findRoot(q);
		if (pp == qp)
			return;//有一个相同的根节点
		if (ids[pp] < ids[qp])//注意是-的 保存的是最大的高
		{
			//qp是小子树 所以吧小子树合并到大子树p 所以要将q的根改为pp
			ids[qp] = pp;
			//sizecount[q] += sizecount[p];
		}
		else
		{
			if (ids[qp] < ids[pp])
			{
				ids[pp] = qp;
				//sizecount[p] += sizecount[q];
			}
			else
			{
				//等高
				ids[pp] -= 1;//等高的话会上升一个高度 所以要-1
				ids[qp] = pp;
			}
		}
	}
	bool find(int i, int j)
	{
		return findRoot(i) == findRoot(j);
	}
	void print()
	{
		for (int i = 0; i < size; ++i)
		{
			if (ids[i] <-1)
			{
				printf("顶点%d有关系：", i);
				for (int j = 0; j < size; ++j)
				{
					if (findRoot(j) == i)
						printf("%d ", j);

				}
				printf("\n");
			}
			else
			{
				printf("顶点%d有关系：空\n", i);
			}
		}
		
	}
	void print_ids()
	{
		for (int i = 0; i < size; ++i)
			printf("%d ", ids[i]);
		printf("\n");
	}
};