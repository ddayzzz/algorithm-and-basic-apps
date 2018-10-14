#include "stdafx.h"
#include <string>
#include <iomanip>
#include <queue>
#include <list>
#include <vector>
#include <functional>
#include <iostream>
#include <stack>
#include <cstring>
#include <algorithm>
#include <fstream>
using namespace std;
const int NOEDGE = 65535;//这个表示无穷 即(VI,V2)不属于E
const int SAME = 0;//这个表示矩阵对角线的值 即I=J
//如果有边的话就用权来代替

struct EdgeInfo
{
	int src;
	int dest;
	int weight;
	EdgeInfo(int _s,int _d,int _w):src(_s),dest(_d),weight(_w){}
	EdgeInfo():EdgeInfo(-1,-1,NOEDGE){}

};
struct vertex
{
	std::string name;
	vertex(string n) :name(n) {}
	vertex() = default;
	~vertex() {}
};

//邻接矩阵存储无向图或有向图 线图
class GraphMartix
{
private:
	bool direct=false;//是否为有向图
	int **martix = nullptr;//保存的矩阵
	int size = 0;//多少阶的矩阵
	vector<vertex> names;//顶点的名称
	int **init(vector<vertex> &namep)
	{
		cout << "请输入有多少个顶点：";
		int n;
		int **ptr = nullptr;
		cin >> n;
		if (n > 0)
		{
			size = n;
			ptr = new int*[n];
			for (int i = 0; i < n; ++i)
				ptr[i] = new int[n];
			//二位数组创建完毕
			for (int i = 1; i <= n; ++i)
			{
				cout << "请输入第" << i << "顶点的名字：";
				string name;
				cin >> name;
				names.push_back(vertex(name));
				cout << "请输入第" << i << "行的数据：(可以输如权的大小。如果没有连接请输入"<<NOEDGE<<"）";
				int wr;
				int cnt = 0;
				while (cnt < n && cin >> wr)
				{
					ptr[i - 1][cnt++] = wr;
				}
				
			}
		}
		return ptr;
	}
	void initbyFile(string fn)
	{
		ifstream ifs(fn);
		int numbers;
		string name;
		int rn;
		ifs >> numbers;
		size = numbers;
		if (numbers > 0)
		{
			martix = new int*[numbers];
			
			for (int i = 0; i < numbers; ++i)
			{
				martix[i] = new int[numbers];
				ifs >> name;
				names.push_back(name);
				for (int j = 0; j < numbers; ++j)
				{
					ifs >> rn;
					martix[i][j] = rn;
				}
			}
		}
		ifs.close();
	}
	//获取图中存在的所有的边（无向图只考虑一次）
	int getAllEdgesNum()
	{
		int num = 0;
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if (martix[i][j] != NOEDGE && martix[i][j] !=SAME)
					++num;
			}
		}
		if (direct == false)
			num /= 2;
		return num;
	}
	//计算出度 indexwei[1，size]
	int getCHUDU(int index)
	{
		int cnt = 0;
		for (int i = 0; i < size; ++i)
		{
			if (martix[index - 1][i] != NOEDGE && martix[index-1][i] != SAME)
			{
				++cnt;
			}
		}
		return cnt;
	}
	//计算入度 indexwei[1，size]
	int getRUDU(int index)
	{
		int cnt = 0;
		for (int i = 0; i < size; ++i)
		{
			if (martix[i][index-1] != NOEDGE && martix[i][index-1] !=SAME)
			{
				++cnt;
			}
		}
		return cnt;
	}
	//获得已vex为起点的终点的索引集合
	void getDESTs(int vex,vector<int> &vec)
	{
		//vector<int> vec;
		for (int i = 0; i < size; ++i)
		{
			if (martix[vex][i] != SAME && martix[vex][i] != NOEDGE)
				vec.push_back(i);
		}
		//return vec;
	}
	//获得已vex为起点的终点的索引集合（这个函数用于使用队列）
	void getDESTs(int vex,queue<int> &que)
	{
		//vector<int> vec;
		for (int i = 0; i < size; ++i)
		{
			if (martix[vex][i] != SAME /*不包含自身*/&& martix[vex][i] != NOEDGE)
				que.push(i);
		}
		//return vec;
	}
	//辅助函数 用于广度优先遍历 order返回的各个顶点的索引值 不是名字 DFS也是
	void do_BFSTraverse(int startindex,bool *flags,vector<int> &order)
	{
		queue<int> bevisited;
		getDESTs(startindex, bevisited);
		if (flags[startindex] == false)
		{
			flags[startindex] = true;
			order.push_back(startindex);
		}
		while (!bevisited.empty())
		{
			int pos = bevisited.front();
			bevisited.pop();
			if (flags[pos] == false)
			{
				flags[pos] = true;
				order.push_back(pos);
				//检测他的子节点
				queue<int> subvex;
				getDESTs(pos, subvex);
				while (!subvex.empty())
				{
					bevisited.push(subvex.front());
					subvex.pop();
				}
			}
		}

	}
	//找到顶点名称为n的顶点在矩阵的索引
	int findVertex(string n)
	{
		int j = -1;
		for (int i = 0; i < names.size(); ++i)
		{
			if (names[i].name == n)
			{
				j = i;
				break;
			}

		}
		return j;
	}
	//辅助函数 用于深度优先遍历 orders板寸访问顺序 flags保存访问的信息 inex是起始的位置
	void do_DFSTraverse(int startindex, bool *flags,vector<int> &orders)
	{
		queue<int> need_be_searched;
		getDESTs(startindex, need_be_searched);
		if (flags[startindex] == false)
		{
			flags[startindex] = true;
			orders.push_back(startindex);
		}
		while (!need_be_searched.empty())
		{
			int pos = need_be_searched.front();
			need_be_searched.pop();
			if (flags[pos] == false)
			{
				//cout << "Find way from \"" << startindex << "\" to \"" << pos <<"\""<< endl;
				flags[pos] = true;
				orders.push_back(pos);
				do_BFSTraverse(pos, flags, orders);
			}
		}
	}
	//根据两个顶点的位置 返回边的权
	int getWeight(int srcindex,int destindex)
	{
		if (martix)
		{
			if (srcindex >= 0 && destindex >= 0 && srcindex < size && destindex < size)
			{
				return martix[srcindex][destindex];
			}
		}
	}
	//思路来源 http://www.cnblogs.com/biyeymyhjob/archive/2012/07/31/2615833.html 大话数据结构

	//这个用于初始化从v开始到任意一个可以连接的顶点的权值
	void dijkstra_setWeightSummary(int v, vector<int> &vec)
	{
		if (v >= 0 && v < size)
		{
			for (int u = 0; u < size; ++u)
			{
					vec.push_back(martix[v][u]);
			}
		}
	}
	void do_dijkstra(int v0,vector<int> &Patharc,vector<int> &PathWeights)
	{
		
		vector<int> finalPath(size);//标志信息 保存前驱顶点
		int v, w, k, min;//
		//初始化数据 patharc保存的是从v0->vi的路径数组 pathweight表示的v0点有连线的顶点+权值
		for (v = 0; v < size; ++v)
		{
			finalPath[v] = 0;
			Patharc.push_back(0);
		}
		dijkstra_setWeightSummary(v0,PathWeights);//这个从起始点开始 吧从v0能到的点的边设置权值
		PathWeights[0] = 0;//出事的v0->v0的权为0
		finalPath[v0] = 1;//这个表示v0这个路径被访问
		for (v = 0; v < size; ++v)
		{
			min = NOEDGE;//这个是最小的权值 w为第一个可能的节点
			for (w = 0; w < size; ++w)
			{
				if (!finalPath[w] && PathWeights[w] < min)
				{
					k = w;//这个k表示的就是第一个要被替换的位置（因为从V0到vw的权更小）
					min = PathWeights[w];//保存这个最小的权值 继续比较找到更小的位置
				}
			}
			finalPath[k] = 1;//目前找到的最小的权的目标点设为1 表示已经搜索了
			for (w = 0; w < size; ++w)
			{
				if (!finalPath[w]/*如果是0的话 表示这个位置可以替换 如果是1的话表示这个位置之前已经定下来了*/ && (min + getWeight(k, w) < PathWeights[w]))
				{
					PathWeights[w] = min + getWeight(k, w);
					Patharc[w] = k;//设置前驱节点 如果目标的权比之前得到地权要小的话。。更新那个最小权的点的前驱
				}
			}
		}
		//delete finalPath;
	}
	//堆优化的dijkstra算法
	void do_dijkstra_heap(int v0,vector<int> &pre,vector<int> &weight)
	{
		typedef std::pair<int, int> P;//P类型是保存从v0到该点second的最短的距离 每次从v0搜索路径的时候总是可以先进行搜索
		std::priority_queue<P, std::vector<P>, std::greater<P>> que;//保存距离的最小队列.
		weight[v0] = 0;//weight[i]是保存从v0出发到顶点为i的距离
		que.push(P(0, v0));
		while (!que.empty())
		{
			P p = que.top();
			que.pop();//弹出
			int v = p.second;//v是最短的点
			if (p.first > weight[v])
				continue;//如果这个边还要大 就不要再继续比较了
			//定义weight[i]表示v0->i的距离 weight[v]=min(weight[v],weight[w]+weight(w->v))
			for (int w = 0; w < size; ++w)
			{
				if (martix[v][w] != NOEDGE && martix[v][w] != SAME)//如果从v->w有捷径可走的话
				{
					int weight_vw = martix[v][w];
					if (weight[w] > weight[v] + weight_vw)//v0->w 和v0->v(认为是最短的)->w哪一个更短?
					{
						weight[w] = weight[v] + weight_vw;
						pre[w] = v;//前驱
						que.push(P(weight[w], w));//把这个最小的权值放进去
					}
				}
			}


		}
	}
	//弗洛伊德算法
	void do_floyd(vector<vector<int>> &P, vector<vector<int>> &D)
	{
		for (int i = 0; i < size; ++i)
		{
			dijkstra_setWeightSummary(i, D[i]);
			for (int j = 0; j < size; ++j)
			{
				P[i].push_back(j);
			}
		}
		int v, w, k;
		//v是起始顶点左边 w是结束点坐标 k是中转点坐标 所有的顶点都会在Vk中转
		for (k = 0; k < size; ++k)
		{
			for (v = 0; v < size; ++v)//行
			{
				for (w = 0; w < size; ++w)//列
				{
					if (D[v][w] > D[v][k] + D[k][w]) /*D[v][w] 表示的是整个二维数组需要搜索的范围 D[v][k]表示的是以k列的一列 D[k][w]表示以k为一行*/
					{
						
						D[v][w] = D[v][k] + D[k][w];
						P[v][w] = P[v][k];
					}
				}
			}
		}
	}
	//最小生成树算法 Kruskal算法
	int do_MST_Kruskal_getEnd(int beg, vector<int> &vec)
	{
		//这用于获取最大的已生成的顶点的最大的顶点 一般用于判断是否组成回路 最大的顶点是已经加入的顶点按编号从小大排列的最大的顶点
		while (vec[beg] > 0)
		{
			beg = vec[beg];
		}
		return beg;//返回的这个beg就是不在beg集合的位置
	}
	void do_MST_Kruskal()
	{
		vector<EdgeInfo> allEdges;//保存所有的边的信息
		vector<int> vends(size);//保存顶点信息
		for (int i = 0; i<size; ++i)
		{
			vends[i] = 0;//初始化顶点信息
			for (int j = 0; j < size; ++j)
			{
				if (martix[i][j] != NOEDGE && martix[i][j] != SAME)
				{
					allEdges.emplace_back(i, j, martix[i][j]);//构建对象
				}
			}
		}
		
		sort(allEdges.begin(), allEdges.end(), [](const EdgeInfo &e1, const EdgeInfo &e2) {return e1.weight < e2.weight; });//排序
		int index;//遍历的节点索引
		int n, m;
		for (index = 0; index <allEdges.size(); ++index)
		{
			n = do_MST_Kruskal_getEnd(allEdges[index].src, vends);//n是获得的最小边的起始点（需要判断是否形成回路，如果是返回与m相同值，否则返回的是还是n 表示的可插入的位置）
			m = do_MST_Kruskal_getEnd(allEdges[index].dest, vends);//m是获得的最小边的终点
			if (m != n)
			{
				vends[n] = m;//表示边n->m是可以插入的 那么就需要吧边
				printf("(%d,%d) %d\n", allEdges[index].src, allEdges[index].dest, allEdges[index].weight);
			}
		}
	}
	//最小生成树算法 Prim算法
	void do_MST_Prim(int startindex)
	{
		vector<int> adjvex(size);//保存相关邻接点的下标
		vector<int> lowweight(size);//保存指定的节点的周围能连接的点的权值
		adjvex[startindex] = 0;//adjvex[i]=0表示的就是该点Vi已经被加入生成生成树
		lowweight[startindex] = 0;//lowweight[i]=0表示的就是该点Vi已经被加入生成生成树
		int min, i, j, k;
		for (i = 0; i < size; ++i)
		{
			if (i != startindex)
			{
				lowweight[i] = getWeight(startindex, i);
			}
			else
			{
				lowweight[i] = NOEDGE;//如果是相同的那么就需要把这个点视为无穷大
			}
			adjvex[i] = startindex;
		}
		for (i = 0; i < size; ++i)//这一步需要求出具有最小的权的终点 标记为k 最小的权为min
		{
			if (i == startindex)
				continue;//不考虑当遍历到起始的顶点 因为它可能会导致重复的添加顶点 因为从到达Vstartindex的点会有 而且权不一定就是NOEDGE
			min = NOEDGE;//设置最大的值
			j = 0; k = 0;
			for (; j < size; ++j)
			{
				if (lowweight[j] != 0 && lowweight[j] < min)
				{
					min = lowweight[j];
					k = j;
				}
			}
			lowweight[k] = 0;//那个k点是我要添加的点 他的任务完成了！
			printf("(%d,%d) %d\n", adjvex[k], k,min);//输出来
			for (j = 0; j < size; ++j)
			{
				if (j == startindex)
					continue;//同理
				if (lowweight[j] != 0 && getWeight(k, j) < lowweight[j]) //更改除不等于0的所有的其实坐标点为k
				{
					lowweight[j] = getWeight(k, j);
					adjvex[j] = k;
				}
			}
		}

	}
	//有向无回路的图的拓扑排序算法 reference http://blog.csdn.net/dm_vincent/article/details/7714519
	//算法一 Khan算法
	void do_TopologicalSort_Khan(queue<int> &result)
	{
		int alledges = getAllEdgesNum();//获取所有的边的条数
		queue<int> setOfRUDUZERO;//记录入度为零的点
		int *ruducount = new int[size];//ptr[i] 表示索引为i的顶点的入度大小
		int i;//临时的变量
		for (i = 0; i < size; ++i)
			ruducount[i] = getRUDU(i + 1);//设置顶点的索引的入度
		//for (i = 0; i < size; ++i)
			//printf("%3d", ruducount[i]);
		for (i = 0; i < size; ++i)
		{
			if (ruducount[i] == 0)
				setOfRUDUZERO.push(i);//设置入度为0的顶点保存到队列中 我们从这些顶点开始
		}
		while (!setOfRUDUZERO.empty())//只要保存入度为0的队列为空那么久循环
		{
			int v = setOfRUDUZERO.front(); setOfRUDUZERO.pop();//选择第一个开始的入度为0的顶点  这里我们以对头作为开始
			result.push(v);//先把结果压入
			std::vector<int> paths;
			getDESTs(v, paths);//获取以v作为起点的边的中点
			for (auto iter = paths.cbegin(); iter != paths.cend(); ++iter)
			{
				--alledges;//没找到一个边 总的边数就减少
				if (0 == --ruducount[*iter])//注意要减去已经找到的顶点 如果目标的终点的入度为0了那么这个顶点就是可以入队的
					setOfRUDUZERO.push(*iter);
			}
		}
		delete[] ruducount;

		if (alledges > 0)
			throw std::runtime_error("do_TopologicalSort_Khan: 图不是有向无回路图！");

	}
	//算法二 依赖于DFS
	void do_TopologicalSort_DFS_visit(stack<int> &result,int beginindex, bool *flags,bool *visited)
	{
		//flag防止重复的顶点访问
		//visited表示的就是在从beginindex开始的一次访问的路径中是否存在回路的判断 如果存在回路那么当访问到这些节点的时候 会是true（此时没有判断flags）
		if (visited[beginindex] == true)
		{
			//delete[] flags;
			//delete[] visited;
			throw std::runtime_error("do_TopologicalSort_DFS_visit:该图不是一个有向无环图！");
		}
		if (flags[beginindex] == false)
		{
			visited[beginindex] = true;//临时标记因为下一次完整的访问有可能经过了同一个顶点
			flags[beginindex] = true;
			vector<int> paths;
			getDESTs(beginindex, paths);
			for (auto i = paths.cbegin(); i != paths.cend(); ++i)
			{
				do_TopologicalSort_DFS_visit(result, *i, flags,visited);
			}
			visited[beginindex] = false;//取消标记
			result.push(beginindex);//注意是循环结束后 因为算法可以保证入栈的顶点是一条路径上的最后一个顶点（没有入度的顶点）注意结果的保存是栈 所以输出的时候满足路劲的关系
			//如果一开始的顶点不是入度为0的点 那么他会被的入度为0的点“挤”下去（因为入度为0的顶点不会存在于一条已知的路径上，他必是一个起点）
		}
	}
public:
	GraphMartix(bool isd=false):direct(isd)
	{
		martix = init(names);
	}
	GraphMartix(string fn, bool isd = false):direct(isd)
	{
		initbyFile(fn);
	}
	void print()
	{
		cout << "矩阵元素如下：" << endl;
		for (int i = 0; i < size; ++i)
		{
			cout << setw(5) << names[i].name;
		}
		cout << endl;
		for (int i = 0; i < size; ++i)
		{
			cout << names[i].name;
			for (int j = 0; j < size; ++j)
			{
				cout << setw(4);
				if (martix[i][j] == NOEDGE)
					cout << "∞";
				else
					cout << martix[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}
	//判断这个无向图是否可以无重复通过 有且仅有两个
	bool Eulercircle()
	{
		int cnt = 0;
		vertex s1, s2;
		if (!direct)
		{
			//无向图
			for (int i = 0; i < size; ++i)
			{
				int deg = 0;
				for (int k = 0; k < size; ++k)
				{

					if (martix[i][k] != NOEDGE && martix[i][k] != SAME)
					{
						deg++;
					}
				}
				if (deg % 2)
				{
					cnt++;
				}

			}
			if (cnt == 2)
			{
				return true;
			}
			return false;
		}
		else
		{
			//有向图判断
			for (int i = 1; i <= size; ++i)
			{

				if (getCHUDU(i) != getRUDU(i))
					return false;
			}
			return true;
		}
	}
	~GraphMartix() {
		if (martix == nullptr) { return; }
		for (int i = 0; i < size; ++i)
		{
			delete martix[i];
		}
		delete martix;
	}
	//接口函数 需要提供深度遍历的起始位置 和需要保存顺序的vector容器
	void DFS_Traverse(int start, vector<int> &order)
	{
		bool *flags = new bool[size];

		for (int i = 0; i < size; ++i)
			flags[i] = false;
		do_DFSTraverse(start, flags, order);
		delete flags;
		
	}
	//接口函数 需要提供广度优先遍历的起始位置 和需要保存顺序的vector容器
	void BFS_Traverse(int start, vector<int> &order)
	{
		bool *flags = new bool[size];

		for (int i = 0; i < size; ++i)
			flags[i] = false;
		do_BFSTraverse(start, flags, order);
		delete flags;

	}
	void Find_MinPath_Dijkstra()
	{
		vector<int> arc, weight;
		int v0;
		cout << "请输入起始点：（0~" << size - 1 << "）：";
		cin >> v0;
		do_dijkstra(v0, arc, weight);
		for (int i = 0; i < size; ++i)
		{
			if (i == v0)
				continue;
			std::cout << "从" << names[v0].name << "到" << names[i].name << "的最小的权为：" << weight[i] << ", 路径为："<<names[v0].name<<"->";
			int vex = i;
			std::stack<int> ids;
			while (arc[vex] != v0)
			{
				ids.push(arc[vex]);
				vex = arc[vex];//因为我每次加入的是前驱 所以只要vex与这arc[vex]是前驱关系就可以了
			}
			while (!ids.empty())
			{
				std::cout << names[ids.top()].name << "->";
				ids.pop();
			}
			std::cout << names[i].name << std::endl;
		}
	}
	void Find_MinPath_Dijkstra_Heap()
	{
		int v0;
		std::cout << "请输入起点:";
		std::cin >> v0;
		std::vector<int> pre(size),weight(size,NOEDGE);
		do_dijkstra_heap(v0, pre,weight);
		//打印前驱
		for (int i = 0; i < size; ++i)
		{
			if (i != v0)
			{
				std::stack<int> pathpoint;
				pathpoint.push(i);
				int k = i;
				while (pre[k] != v0)
				{
					pathpoint.push(pre[k]);
					k = pre[k];
				}
				pathpoint.push(v0);
				while (!pathpoint.empty())
				{
					std::cout << names[pathpoint.top()].name;
					pathpoint.pop();
					if (!pathpoint.empty())
						std::cout << "->";
				}
				std::cout << " min path weight : " << weight[i];
				std::cout << std::endl;
			}
		}
	}
	void Find_MinPath_Floyd()
	{
		vector<vector<int>> arc(size), weight(size);
		int v0,vx;
		cout << "请输入起始点和终止点：（0~" << size - 1 << "）：";
		cin >> v0>>vx;
		do_floyd(arc, weight);
		if (v0 >= 0 && v0 < size && vx >= 0 && vx < size)
		{
			int beg = v0;
			int wei = v0;
			while (beg != vx)
			{
				wei= arc[beg][vx];
				cout << names[beg].name << "--("<<weight[beg][wei]<<")-->";
				beg = wei;
			}
			//记得最后一个元素
			cout << names[beg].name << endl;
		}
	}
	void MST_Kruskal()
	{
		do_MST_Kruskal();
	}
	void MST_Prim(int n)
	{
		do_MST_Prim(n);
	}
	void debug_print()
	{
		for(int i=0;i<size;++i)
		{
			for(int j=0;j<size;++j)
			{
				printf("%6d ", martix[i][j]);
			}
			printf("\n");
		}

	}
	void TopologicalSort_Khan()
	{
		debug_print();
		queue<int> res;
		do_TopologicalSort_Khan(res);
		while (!res.empty())
		{
			std::cout << names[res.front()].name << "->";
			res.pop();
		}
		std::cout << std::endl;
	}
	void TopologicalSort_DFS()
	{
		int v;
		stack<int> sta;
		bool *bs = new bool[size];//标记的数组
		bool *vis = new bool[size];//记录路径是否存在回路的bool数组
		memset(bs, false, sizeof(bool)*size);
		memset(vis, false, sizeof(bool)*size);
		for(v=0;v<size;++v)//这个是深度优先遍历
			do_TopologicalSort_DFS_visit(sta, v, bs,vis);//从顶点开始进行搜索
		delete[] bs;
		delete[] vis;
		while (!sta.empty())
		{
			v = sta.top();
			sta.pop();
			std::cout << names[v].name << "->";
		}
		std::cout << std::endl;
	}
	void TopologicalSort_ForCritical(std::stack<int> &vex,std::vector<int> &etv)
	{
		//etv一定要先初始化为0
		//详细的解释参看list的版本
		std::vector<int> indeg(size);
		std::stack<int> tra;
		int k;
		for (int i = 0; i < size; ++i)
		{
			k = getRUDU(i + 1);
			if (k == 0)
				tra.push(i);
			indeg[i] = k;
		}
		int top;
		int viscount = 0;
		int i;
		while (!tra.empty())
		{
			top = tra.top();
			tra.pop();
			vex.push(top);
			++viscount;
			for (i = 0; i < size; ++i)//这个最好是可以建立一个边集数组 不然的话需要每次遍历复杂度On*n
			{
				if (martix[top][i] != SAME && martix[top][i] != NOEDGE)
				{
					if (--indeg[i] == 0)
						tra.push(i);
					//只考虑带有权值的弧头
					if (etv[top] + martix[top][i] > etv[i])
					{
						etv[i] = etv[top] + martix[top][i];
					}
					
				}
			}
		}
		if (viscount != size)
			throw std::runtime_error("该图不是有向无环图！");

	}
	//这个是矩阵版本的关键排序
	void CriticalSort()
	{
		std::vector<int> etv(size);
		std::stack<int> vex;
		TopologicalSort_ForCritical(vex, etv);
		int ete, lte;
		std::vector<int> ltv(size, etv.back());
		while (!vex.empty())
		{
			int top = vex.top();
			vex.pop();
			for (int v = 0; v < size; ++v)
			{
				if (martix[top][v] != NOEDGE && martix[top][v] != SAME)
				{
					if (ltv[v] - martix[top][v] < ltv[top])
					{
						ltv[top] = ltv[v] - martix[top][v];
					}
				}
			}
		}
		//判断是否是关键路径
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if (martix[i][j] != SAME && martix[i][j] != NOEDGE)
				{
					ete = etv[i];
					lte = ltv[j] - martix[i][j];
					if (ete == lte)
						printf("<v%d,v%d> length: %d\n", i, j, martix[i][j]);
				}
			}
		}
	}
};

//文字游戏题目
int graph[27][27];
int outdegree[30];// = new int[30];
int indegree[30];// = new int[30];
void DFS(int index)
{
	//无向图的深度优先遍历
	//graph是一个可以存储26个字母的二维数组
	for (int i = 0; i < 26; ++i)
	{
		if (graph[index][i])
		{
			//这个表示出度
			--graph[index][i];
			--graph[i][index];//注意 对于无向图 需要把对称位置也要做遍历标志
			DFS(i);//再从i位置开始遍历本来i与index有通路 所以从当前的便遍历位置转移到i
		}
	}
}
void PlaysOnWord()
{
	int t;//表示判断次数
	
	cout << "请输入判断的次数：";
	cin >> t;
	while (t--)
	{
		cout << "请输入一共有多少个门：";
		string word;
		int begin, end;
		int n;//这个用来控制有多少个单词
		memset(graph, 0, sizeof(graph));
		memset(outdegree, 0, sizeof(outdegree));
		memset(indegree, 0, sizeof(indegree));//每次读取一次就复写一次
		cin >> n; 
		cout << "请依次输入" << n << "个门上的单词：";
		while (n--)
		{
			
			cin >> word;
			begin = word[0] - 'a';
			end = word[word.size() - 1] - 'a';
			outdegree[end]++;//这个用来保存以最后一个字符的出度
			indegree[begin]++;//保存第一个字符的入度
			++graph[begin][end];//begin到end的有边连接
			++graph[end][begin];//从end到begin也有同样的边连接
			//如果前一个单词与后一个单词是尾字母和首字母相等 那么他们对应的出度=入度 每一对单词差分出首字母到末字母的路径
			//条件1.对于每个点出度与入度相等 2.或者是出度和入度的绝对值的差为1 并且这样的点每种类型（出度>入度和入度>出度）不能超过2个（相差1 那么出度和入度中有一个是奇数）
		}
		//开始遍历
		DFS(0);
		int flag = false;//这个标志表示是否有没有遍历到的边
		int sumout= 0;
		int sumin = 0;
		//是否有没有遍历到的边
		for (int i = 0; i < 26; ++i)
		{
			for (int j = 0; j < 26; ++j)
			{
				if (graph[i][j])
				{
					flag = true; break;
				}
			}
			
			if (outdegree[i] || indegree[i])
			{
				if (outdegree[i] == indegree[i])
					continue;
				else if (outdegree[i] + 1 == indegree[i])
					sumin++;
				else if (indegree[i] + 1 == outdegree[i])
					sumout++;
				else {
					flag = true;
					break;
				}
				if (flag || sumin >= 2 || sumout >= 2)//如果已经不满足条件了 就终止循环
				{
					break;
				}
			}
		}
		if (flag || sumin >= 2 || sumout >= 2)
		{
			cout << "门不能打开" << endl;
		}
		else
		{
			cout << "门可以打开" << endl;
		}
	}
}
//骑士周游问题
struct Nodeinfo
{
	int ways;
	int x;
	int y;
};
struct Board
{
	int dirs[8][2] = {
		{-2,-1},
		{-2,1},
		{-1,-2},
		{-1,2},
		{1,-2},
		{1,2},
		{2,-1},
		{2,1}
	};
	//这个函数用来检测目标位置x y是否可以合法
	bool canbePlaced(int x, int y)
	{
		if (x >= 0 && y >= 0 && x < size && y < size && arr[x][y] == -1)
			return true;
		return false;
	}
	int size;
	int **arr;
	Board(int n=8) :size(n) 
	{
		arr = nullptr;
		if (n > 0)
		{
			arr = new int*[n];
			for (int i = 0; i < n; ++i)
				arr[i] = new int[n];
			for (int i = 0; i < n; ++i)
			{
				memset(arr[i], -1, n*sizeof(int));
			}
		}
		
	}
	~Board() {
		if (!arr)
		{
			for (int i = 0; i < size; ++i)
				delete arr[i];
			delete arr;
		}
	}
	
	bool do_getPath_digui(int x,int y,int start = 0)
	{
		int i, xx, yy;
		for (i = 0; i < 8; ++i)//遍历可能的方向
		{
			xx = x + dirs[i][0];
			yy = y + dirs[i][1];
			if (canbePlaced(xx, yy))//如果位置合法
			{
				arr[xx][yy] = start;//那么先插入这个位置
				if (start == 64)//如果已经到达末尾了
				{
					print();
					return true;
				}
				if (do_getPath_digui(xx, yy, start + 1))//还没有到达最后一次
				{
					return true;
				}
				else
				{
					arr[xx][yy] = -1;//如果这个位置不行 只能把这个位置退回 然后再次从x位置搜索一下可行的位置
				}
			}
		}
		return false;
	}
	void findPath_digui(int x, int y)
	{
		arr[x][y] = 1;//目标位置
		do_getPath_digui(x, y, 2);//从第二步开始
	}
	//打印矩阵
	void print()
	{
		for (int i = 0; i < size; ++i)
		{
			for (int o = 0; o < size; ++o)
			{
				cout << setw(4) << arr[i][o];
			}
			cout << endl;
		}
	}

	//计算x y周围的点的周围可以放置的点
	int count_ways(int x, int y)
	{
		int xx, yy;
		int con = 0;
		if (canbePlaced(x, y) == false) { return -1; }//如果x y本身不合法 那么直接退出
		for (int i = 0; i < 8; ++i)
		{
			xx = x + dirs[i][0];
			yy = y + dirs[i][1];
			if (canbePlaced(xx, yy))
			{
				++con;
			}
		}
		return con;//con==0的话 表示周围的周围没有可放置的点 这个点一般是最后一个放置的即dep=64
	}
	void sortways(Nodeinfo *ar)
	{
		//这个按照冒泡排序 ways小的放前面
		Nodeinfo tmp;
		for (int i = 0; i < 8; ++i)
		{
			for (int j=i;j<8;++j)
			{
				if (ar[i].ways > ar[j].ways)
				{
					tmp = ar[i];
					ar[i] = ar[j];
					ar[j] = tmp;
				}
			}
		}
	}
	void do_getPath_tanxin(int x, int y, int dep)
	{
		if (dep > 64)
		{
			//arr[x][y] = 64;
			print();
			return;
		}

		int i, xx, yy;
		Nodeinfo cha[8];//way为 x y周围的点的周围的可以放置的点的个数 x y（成员） 为那个x y 的可插入点的位置
		for (i = 0; i < 8; ++i)
		{
			xx = x + dirs[i][0];
			yy = y + dirs[i][1];
			cha[i].ways = count_ways(xx, yy);//统计位置
			cha[i].x = xx;
			cha[i].y = yy;

		}
		sortways(cha);
		for (i = 0; cha[i].ways < 0; ++i);//排除掉way <0 即x y 不合法 注意当way=0的时候表示就是那个x y的周围点可插入但是没有继续插入的点了（这个适用于dep=64)的情况
		for (; i < 8; ++i)//从第一个可插入的点的位置开始
		{
			xx = cha[i].x;
			yy = cha[i].y;
			arr[xx][yy] = dep;//目标位置插入深度
			//print();
			//printf("---------------\n");
			//system("cls");
			do_getPath_tanxin(xx, yy, dep + 1);//从新的位置开始遍历
			// arr[xx][yy] = -1;//这个问题：如果去掉注释的作用的话 那么就会曲线的循环 我的认为是他的前一次递归调用的前一次递归的最后一个周围插入位置就是这个被改为-1的点 那么这个点又会在新一次的迭代被使用
		}
	}
	void findPath_tanxin(int x, int y)
	{
		arr[x][y] = 1;//首先插入
		do_getPath_tanxin(x, y, 2);//从当前位置开始
	}
};





