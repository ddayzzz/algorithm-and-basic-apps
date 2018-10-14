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
//�߼�����
struct EdgeNode
{
	int v;//���
	int w;//�յ�
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
			std::cout << "�����붥������ƣ�";
			std::cin >> names[i];
			std::cout << "�������" << i + 1 << "�е����ݣ�û����������\"" << NO_EDGE << "\"��ʾ��:";
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
		//ע���ڽӱ�洢���ǳ���
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
					break;//������ƽ�б�
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
		std::vector<int> visited(size);//����Ƿ��ʵı��
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
						pathswiehgt[w] = minweight +tempweg ;//minweight ��V->TARW tempweg�� TARW->W ����minweight+tempweg = V->TARW->W
						pre[w] = tarw;
					}
				}
			}
		}
	}
	void do_MST_Prim(int v0)
	{
		std::vector<int> adjvex(size);//adjvex[i]==j��ʾi->j��һ����С�ı�
		std::vector<int> lowweight(size);//����Ѿ����ʵĽڵ� lowweight[vi]==_SAME��ʾ����vi�Ѿ�����

		int i, j, k;
		for (i = 0; i < size; ++i)
		{
			if (i != v0)
				lowweight[i] = getEdgeWeight(v0, i);
			adjvex[i] = v0;//�����Ķ���
		}
		lowweight[v0] = _SAME;//���v0���Ѿ���������
		for (i = 0; i < size; ++i)
		{
			if (i == v0)
				continue;
			int min=NO_EDGE;
			k = 0;
			for (j = 0; j < size; ++j)
			{
				if (lowweight[j] !=_SAME && lowweight[j] < min) //��i->j��һ����Сֵ
				{
					min = lowweight[j];
					k = j;
				}
			}
			lowweight[k] = _SAME;//k�ǵ�ǰ��С�ߵ��յ��id
			std::cout << "( " << adjvex[k]/*���adjvex[k]���ϴ���ӵĻ�ͷ*/ << " -> " << k << " ,"<<min<<" )\n";
			for (j = 0; j < size; ++j)
			{
				if (j == v0)
					continue;
				if (lowweight[j] !=_SAME)
				{
					int tempweg = getEdgeWeight(k, j);//������С�ıߵ�Ȩֵ �Լ�ǰ�� ���ǲ����޸��Ѿ����ʵĽڵ���
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
		while (parent[v] > 0)//ÿ��ѭ���ͻ����Ż�β��ǰ�� ���û�д����Ƕ�Ӧλ�þ���0 ����v
			v = parent[v];//vΪԭ�ߵĻ�β
		return v;
	}
	void do_MST_Kruskal()
	{
		std::vector<EdgeNode> edges;//����Ǳ���ߵ����Ա�
		std::vector<int> parents(size);//parents[i]��ʾ����IDΪi��ͷ��������С����ʱ��
		//�����߼�����
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
		//����Ȩֵ�Ĵ�С����
		std::sort(edges.begin(), edges.end(), [](const EdgeNode &lhs, const EdgeNode &rhs)->bool {return lhs.weight < rhs.weight; });
		//�߼����鴴�����
		for (int i = 0; i < edges.size(); ++i)
		{
			int m = do_MST_Kruskal_getEnd(edges[i].v,parents);//��ȡ�ߵ����Ļ�β
			int n = do_MST_Kruskal_getEnd(edges[i].w, parents);//��ȡ�ߵ��յ�Ļ�β
			if (m != n)//��������ߵ����յĻ�β����� ��ô�Ϳ��Լ���������
			{
				parents[n] = m;
				printf("(%d,%d) %d\n", edges[i].v, edges[i].w, edges[i].weight);
			}
		}
	}
	//���������㷨
	void do_topologicalSort(std::queue<int> &result)
	{
		std::vector<int> INDeginfo(size);//�����Ϣ
		std::stack<int> sta;//������ʵ�˳��
		for (int i = 0; i < size; ++i)
		{
			int in= getINDegree(i);
			INDeginfo[i] = in;
			if (in == 0)
			{
				sta.push(i);//���Ⱦ�Ҫ�����Ϊ0�Ķ��㿪ʼ
			}
		}
		//���ȶ�ȡ���еĶ���������Ϣ
		int visitcount = 0;//����ͳ�ƣ����������ͼ�����Ǵ���������ͼ(û�����Ϊ0�Ķ���) ��ôvisitcount !=size
		while (!sta.empty())
		{
			visitcount++;
			int vex = sta.top();
			sta.pop();
			result.push(vex);
			GraphNode *pnd = data[vex].pnext;
			while (pnd)
			{
				if (--INDeginfo[pnd->vertexID] == 0)//�ǲ����µ����Ϊ0�Ķ���
				{
					sta.push(pnd->vertexID);
				}
				pnd = pnd->pnext;
			}
		}
		if (visitcount != size)
			throw std::runtime_error("���������޻�ͼ��");

	}
	//visited ��ʾ�Ѿ��������Ķ��㣨��ʱ��ǣ������жϻ�·��
	//flags�Ѿ�����Ĳ���
	void do_topologicalSort_DFS_visit(std::vector<int> &flags,std::vector<int> visited,int v, std::stack<int> &result) {
		if (visited[v] == 1)
			throw std::runtime_error("���������޻�ͼ��");
		visited[v] = 1;//����ڱ��ε������б����
		GraphNode *nd = data[v].pnext;
		if (flags[v] == 0)
		{
			while (nd)//�ݹ�DFS��������֧����
			{
				do_topologicalSort_DFS_visit(flags, visited, nd->vertexID, result);
				nd = nd->pnext;
			}
			flags[v] = 1;//���ñ�� ����ڵ㲻���ٷ���
			visited[v] = 0;//����������������һ������һ���ڵ㿪ʼ���ܻ�������� ���ǲ�һ�����ǻ�������flags���ñ���ˣ�
			result.push(v);//�����·����ĩ�˵ص㣨�����Ǵ���ĩ�Ķ��㣩����Ϊ0

		}

	}
	//�ؼ����� �Ƚ��а���Ȩֵ����ԭ�����������
	//�Ľ���������������etv���¼����緢����
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
		//INDEG�Ǹ����������ȱ�
		int viscount = 0;//��¼���ʵ�˳��
		while (!vis.empty())
		{
			viscount++;
			int top = vis.top();
			vis.pop();
			sta2.push(top);//sta2�������������˳��
			GraphNode *gnd = data[top].pnext;
			while (gnd)
			{
				if (--inDeg[gnd->vertexID] == 0)
					vis.push(gnd->vertexID);//��һ�����Ϊ0�Ķ���
				if ((etv[top] + gnd->weight > etv[gnd->vertexID]))//���etv���ڵ����·��+��top��ʼ��һ��·����Ȩ>��һ���etv�������һ���etvֵ Ҳ����˵�����Ϊ0�ĵ㵽Ŀ���ľ���ȴ�top����һ��ľ���ҪС
					etv[gnd->vertexID] = etv[top] + gnd->weight;
				gnd = gnd->pnext;
			}
		}
		if (viscount != size)
			throw std::runtime_error("���������޻�ͼ��");


	}
	//AOV�����ϱߵ�Ȩֵ����AOE��
	void do_criticalSort()
	{
		//etv�¼������緢��ʱ�� ��
		//ltv�¼���������ʱ�� ��
		//ete��������ʱ�� ��->��
		//lte�������ʱ�� ��->Ȩ
		//����֮ǰ��Ȩ���ǻ�ĳ���ʱ��
		//etv ���� ete�ſ��ܷ���
		std::vector<int> etv(size);
		std::stack<int> vex;
		do_topologicalSor_WeightFirst(etv, vex);
		std::vector<int> ltv(size,etv.back());
		//���йؼ�����
		int ete, lte; int vextop;
		while (!vex.empty())
		{
			vextop = vex.top();
			vex.pop();
			for (GraphNode *gnd = data[vextop].pnext; gnd != nullptr; gnd = gnd->pnext)
			{
				int k = gnd->vertexID;
				if (etv[k] - gnd->weight < ltv[vextop])//��ͷ����Ŀ�ʼʱ��-�����ߵ�Ȩֵ��Ҳ���������β��������翪ʼʱ�� �� С�ڻ�β���������ʼʱ��
				{
					ltv[vextop] = etv[k] - gnd->weight;//���»�β��ʱ��
				}
			}
		}
		for (int i = 0; i < size; ++i)//�����ж��ǲ��ǹؼ���·��
		{
			for (GraphNode *gnd = data[i].pnext; gnd; gnd = gnd->pnext)
			{
				int k = gnd->vertexID;
				ete = etv[i];//����������Ŀ�ʼʱ�� �����ܴ������Ķ���Ŀ�ʼ��ʱ��etv[i]
				lte = ltv[k] - gnd->weight;//����������Ŀ���ʱ��=��ͷ������ʼʱ��-�û�ĳ���ʱ��
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
				std::cout << names[psrc] << "��" << names[i] << "��Ȩ·����СΪ��" << tar[i] << ", ·��Ϊ��";
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
			do_topologicalSort_DFS_visit(flags, visited, i, seq);//���Ϊ0����Ҫ���� ��ӵ�ջ��
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