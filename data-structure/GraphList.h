#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

const int NO_EDGE = 65535;
const int _SAME = 0;
struct GraphNode
{
	GraphNode *pnext;
	int vertexID;
	int weight;
	GraphNode(int id,int w, GraphNode *next) :vertexID(id), pnext(next),weight(w) {

	}
	GraphNode():pnext(nullptr){}
};
//边集数组
struct EdgeNode
{
	int v;//起点
	int w;//终点
	int weight;
	EdgeNode(int _v,int _w,int _weg):v(_v),w(_w),weight(_weg){}
};

class GraphList
{
private :
	int size;
	GraphNode *data;
	std::string *names;
	bool isdirect;
	void init_frominput()
	{
		
		int num;
		int da;
		std::cin >> num;
		size = num;
		data = new GraphNode[num];
		names = new std::string[num];
		for (int i = 0; i < num; ++i)
		{
			std::cout << "请输入顶点的名称：";
			std::cin >> names[i];
			std::cout << "请输入第" << i + 1 << "行的数据（没有连接请用\"" << NO_EDGE << "\"表示）:";
			data[i].vertexID = i;
			data[i].weight = _SAME;
			for (int j = 0; j < num; ++j)
			{
				
				std::cin >> da;
				if (da != NO_EDGE && da != _SAME)
				{
					data[i].pnext = new GraphNode(j, da, data[i].pnext);
				}
			}

		}
	}
	int getEdgeWeight(int pSrc, int pDest)
	{
		GraphNode *node = data[pSrc].pnext;
		while (node != nullptr)
		{
			if (node->vertexID == pDest)
				return node->weight;
			node = node->pnext;
		}
		return NO_EDGE;
	}
	int getINDegree(int v)
	{
		//注意邻接表存储的是出度
		int in = 0;
		for (int i = 0; i < size; ++i)
		{
			if (i == v)
				continue;
			GraphNode *gnd = data[i].pnext;
			while (gnd)
			{
				if (gnd->vertexID == v)
				{
					++in;
					break;//不考虑平行边
				}
				gnd = gnd->pnext;
			}
		}
		return in;
	}
	void getVertextAllEdgeInfo(int pSrc,std::vector<int> &container)
	{
		if (pSrc >= 0 && pSrc < size)
		{
			GraphNode *nd = data[pSrc].pnext;
			int idcount = size - 1;
			while (nd != nullptr)
			{
				int temp = nd->vertexID;
				for (int i = idcount; i > temp; --i)
				{
					container[i] = NO_EDGE;
				}
				container[temp] = nd->weight;
				idcount = temp - 1;
				nd = nd->pnext;
			}
			for (int i = idcount ; i >= 0; --i)
				container[i] = NO_EDGE;
		}
	}
	void do_FindShortPath_dijkstra(int v0, std::vector<int> &pathswiehgt,std::vector<int> &pre)
	{
		std::vector<int> visited(size);//这个是访问的标记
		//std::vector<int> pre(size);
		visited[v0] = 1;
		
		getVertextAllEdgeInfo(v0, pathswiehgt);
		pathswiehgt[v0] = 0;
		int v, w;
		for (v = 0; v < size; ++v)
		{
			int minweight = NO_EDGE;
			int tarw = v;
			for (w = 0; w < size; ++w)
			{
				int t = pathswiehgt[w];
				if (!visited[w] && t < minweight)
				{
					tarw = w;
					minweight = t;
				}
			}
			
			visited[tarw] = 1;
			for (w = 0; w < size; ++w)
			{
				if (!visited[w])
				{
					int tempweg = getEdgeWeight(tarw, w);
					if (minweight + tempweg < pathswiehgt[w])
					{
						pathswiehgt[w] = minweight +tempweg ;//minweight 是V->TARW tempweg是 TARW->W 所以minweight+tempweg = V->TARW->W
						pre[w] = tarw;
					}
				}
			}
		}
	}
	void do_MST_Prim(int v0)
	{
		std::vector<int> adjvex(size);//adjvex[i]==j表示i->j是一条最小的边
		std::vector<int> lowweight(size);//标记已经访问的节点 lowweight[vi]==_SAME表示顶点vi已经访问

		int i, j, k;
		for (i = 0; i < size; ++i)
		{
			if (i != v0)
				lowweight[i] = getEdgeWeight(v0, i);
			adjvex[i] = v0;//出发的顶点
		}
		lowweight[v0] = _SAME;//这个v0点已经被访问了
		for (i = 0; i < size; ++i)
		{
			if (i == v0)
				continue;
			int min=NO_EDGE;
			k = 0;
			for (j = 0; j < size; ++j)
			{
				if (lowweight[j] !=_SAME && lowweight[j] < min) //从i->j的一个最小值
				{
					min = lowweight[j];
					k = j;
				}
			}
			lowweight[k] = _SAME;//k是当前最小边的终点的id
			std::cout << "( " << adjvex[k]/*这个adjvex[k]是上次添加的弧头*/ << " -> " << k << " ,"<<min<<" )\n";
			for (j = 0; j < size; ++j)
			{
				if (j == v0)
					continue;
				if (lowweight[j] !=_SAME)
				{
					int tempweg = getEdgeWeight(k, j);//更新最小的边的权值 以及前驱 但是不会修改已经访问的节点了
					if (lowweight[j] > tempweg)
					{
						lowweight[j] = tempweg;
						adjvex[j] = k;
					}
				}
			}
		}

	}
	int do_MST_Kruskal_getEnd(int v, std::vector<int> &parent)
	{
		while (parent[v] > 0)//每次循环就会沿着弧尾向前推 如果没有创建那对应位置就是0 返回v
			v = parent[v];//v为原边的弧尾
		return v;
	}
	void do_MST_Kruskal()
	{
		std::vector<EdgeNode> edges;//这个是保存边的线性表
		std::vector<int> parents(size);//parents[i]表示顶点ID为i的头（创建最小树的时候）
		//创建边集数组
		for (int i = 0; i < size; ++i)
		{
			parents[i] = 0;
			GraphNode *gnd = data[i].pnext;
			while (gnd)
			{
				edges.emplace_back(i, gnd->vertexID, gnd->weight);
				gnd = gnd->pnext;
			}
		}
		//按照权值的大小排序
		std::sort(edges.begin(), edges.end(), [](const EdgeNode &lhs, const EdgeNode &rhs)->bool {return lhs.weight < rhs.weight; });
		//边集数组创建完成
		for (int i = 0; i < edges.size(); ++i)
		{
			int m = do_MST_Kruskal_getEnd(edges[i].v,parents);//获取边的起点的弧尾
			int n = do_MST_Kruskal_getEnd(edges[i].w, parents);//获取边的终点的弧尾
			if (m != n)//如果这条边的最终的弧尾不相等 那么就可以加入生成树
			{
				parents[n] = m;
				printf("(%d,%d) %d\n", edges[i].v, edges[i].w, edges[i].weight);
			}
		}
	}
	//拓扑排序算法
	void do_topologicalSort(std::queue<int> &result)
	{
		std::vector<int> INDeginfo(size);//入度信息
		std::stack<int> sta;//保存访问的顺序
		for (int i = 0; i < size; ++i)
		{
			int in= getINDegree(i);
			INDeginfo[i] = in;
			if (in == 0)
			{
				sta.push(i);//首先就要从入度为0的顶点开始
			}
		}
		//首先读取所有的顶点的入度信息
		int visitcount = 0;//访问统计，如果是无向图或者是带环的有向图(没有入度为0的顶点) 那么visitcount !=size
		while (!sta.empty())
		{
			visitcount++;
			int vex = sta.top();
			sta.pop();
			result.push(vex);
			GraphNode *pnd = data[vex].pnext;
			while (pnd)
			{
				if (--INDeginfo[pnd->vertexID] == 0)//是不是新的入度为0的顶点
				{
					sta.push(pnd->vertexID);
				}
				pnd = pnd->pnext;
			}
		}
		if (visitcount != size)
			throw std::runtime_error("不是有向无环图！");

	}
	//visited 表示已经被遍历的顶点（临时标记，用于判断回路）
	//flags已经排序的部分
	void do_topologicalSort_DFS_visit(std::vector<int> &flags,std::vector<int> visited,int v, std::stack<int> &result) {
		if (visited[v] == 1)
			throw std::runtime_error("不是有向无环图！");
		visited[v] = 1;//这个在本次的搜素中被标记
		GraphNode *nd = data[v].pnext;
		if (flags[v] == 0)
		{
			while (nd)//递归DFS遍历到分支顶点
			{
				do_topologicalSort_DFS_visit(flags, visited, nd->vertexID, result);
				nd = nd->pnext;
			}
			flags[v] = 1;//永久标记 这个节点不能再访问
			visited[v] = 0;//结束本次搜索（下一次以另一个节点开始可能还会遍历到 但是不一定就是环，但是flags永久标记了）
			result.push(v);//这个是路径最末端地点（或者是次最末的顶点）出度为0

		}

	}
	//关键排序 先进行按照权值最大的原则的拓扑排序
	//改进拓扑排序用于求etv（事件最早发生）
	void do_topologicalSor_WeightFirst(std::vector<int> &etv,std::stack<int> &sta2)
	{
		std::vector<int> inDeg(size);
		std::stack<int> vis;
		for (int i = 0; i < size; ++i)
		{
			int n = getINDegree(i);
			inDeg[i] = n;
			if (!n)
				vis.push(i);
		}
		//INDEG是各个顶点的入度表
		int viscount = 0;//记录访问的顺序
		while (!vis.empty())
		{
			viscount++;
			int top = vis.top();
			vis.pop();
			sta2.push(top);//sta2保存拓扑排序的顺序
			GraphNode *gnd = data[top].pnext;
			while (gnd)
			{
				if (--inDeg[gnd->vertexID] == 0)
					vis.push(gnd->vertexID);//下一个入度为0的顶点
				if ((etv[top] + gnd->weight > etv[gnd->vertexID]))//如果etv存在的最短路径+从top开始的一条路径的权>那一点的etv则更新那一点的etv值 也就是说从入度为0的点到目标点的距离比从top到这一点的距离要小
					etv[gnd->vertexID] = etv[top] + gnd->weight;
				gnd = gnd->pnext;
			}
		}
		if (viscount != size)
			throw std::runtime_error("不是有向无环图！");


	}
	//AOV网加上边的权值就是AOE网
	void do_criticalSort()
	{
		//etv事件的最早发生时间 点
		//ltv事件的最晚发生时间 点
		//ete活动最早结束时间 点->边
		//lte活动最晚开工时间 边->权
		//他们之前的权就是活动的持续时间
		//etv 发生 ete才可能发生
		std::vector<int> etv(size);
		std::stack<int> vex;
		do_topologicalSor_WeightFirst(etv, vex);
		std::vector<int> ltv(size,etv.back());
		//进行关键排序
		int ete, lte; int vextop;
		while (!vex.empty())
		{
			vextop = vex.top();
			vex.pop();
			for (GraphNode *gnd = data[vextop].pnext; gnd != nullptr; gnd = gnd->pnext)
			{
				int k = gnd->vertexID;
				if (etv[k] - gnd->weight < ltv[vextop])//弧头最早的开始时间-这条边的权值（也就是这个弧尾顶点的最早开始时间 ） 小于弧尾顶点的最晚开始时间
				{
					ltv[vextop] = etv[k] - gnd->weight;//更新弧尾的时间
				}
			}
		}
		for (int i = 0; i < size; ++i)//用于判断是不是关键的路径
		{
			for (GraphNode *gnd = data[i].pnext; gnd; gnd = gnd->pnext)
			{
				int k = gnd->vertexID;
				ete = etv[i];//这个活动的最早的开始时间 不可能大于他的顶点的开始的时间etv[i]
				lte = ltv[k] - gnd->weight;//这个活动的最晚的开工时间=弧头的最晚开始时间-该活动的持续时间
				if (ete == lte)
				{
					std::cout << "<v" << names[i] << ",v" << names[k] << "> length: " << gnd->weight << "\n";
				}
			}
		}
	}
public:
	GraphList(int sz) :size(sz), data(new GraphNode[sz]), names(new std::string[sz]) {  }
	GraphList(bool isdir):isdirect(isdir) { init_frominput(); }
	void FindMinWeightPath_Dijkstra(int psrc)
	{
		std::vector<int> tar(size),pre(size);
		do_FindShortPath_dijkstra(psrc, tar,pre);
		for (int i = 0; i < size; ++i)
		{
			if (i != psrc)
			{
				std::cout << names[psrc] << "到" << names[i] << "的权路径最小为：" << tar[i] << ", 路径为：";
				int vex = i;
				std::stack<int> sta;
				std::cout << names[psrc] << "->";
				while (pre[vex] != psrc)
				{
					sta.push(pre[vex]);
					vex = pre[vex];
				}
				while (!sta.empty())
				{
					std::cout << names[sta.top()] << "->";
					sta.pop();
				}
				std::cout << names[i] << std::endl;
			}
		}
	}
	void MST_Prim(int v)
	{
		do_MST_Prim(v);
	}
	void MST_Kruskal() { do_MST_Kruskal(); }
	void TopologicalSort()
	{
		std::queue<int> res;
		do_topologicalSort(res);
		int i;
		while (!res.empty())
		{
			std::cout << names[res.front()] << "->";
			res.pop();
		}
		std::cout << std::endl;
	}
	void TopologicalSort_DFS()
	{
		std::vector<int> flags(size), visited(size);
		std::stack<int> seq;
		for (int i = 0; i < size; ++i)
		{
			do_topologicalSort_DFS_visit(flags, visited, i, seq);//入度为0的需要遍历 添加到栈顶
		}
		while(!seq.empty())
		{
			std::cout << names[seq.top()] << "->";
			seq.pop();
		}
		std::cout << std::endl;
	}
	void CriticalSort()
	{
		do_criticalSort();
	}
	~GraphList()
	{
		int indx = size - 1;
		while (indx >= 0)
		{
			GraphNode *np = data[indx].pnext,*temp;
			while (np != nullptr)
			{
				temp = np->pnext;
				delete np;
				np = temp;
			}
			--indx;
		}
		delete[] data;
		delete[] names;
	}
};