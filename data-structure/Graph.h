#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <iterator>
using namespace std;
//顶点的抽象数据类型
class Vertex
{
private:
	string name;//保存顶点的名字
public:
	Vertex(const string &n):name(n){}
	const string getName() const { return name; }
	void setName(const string &n) { name = n; }
};
class Edge
{
	typedef Vertex *VertexNode;//保存目标顶点的指针类型
private:
	VertexNode src;//这个是保存起点
	VertexNode dest;//这个保存终点
	string edgename;//边的名字
	int weight;//边的权值
public:
	Edge(const string &n,const VertexNode SRC=nullptr,const VertexNode DEST=nullptr):edgename(n),src(SRC),dest(DEST){}
	void setEdgeName(const string &n) { edgename = n; }
	void setSrc(const VertexNode SRC) { src = SRC; }
	void setDest(const VertexNode DEST) { dest = DEST; }
	void setWeight(int n) { weight = n; }

	 string &getEdgeName() { return edgename; }
	 VertexNode &getSrc() { return src; }
	 VertexNode &getDest() { return dest; }
	 int &getWeight() { return weight; }

	 string getEdgeName() const { return edgename; }
	 VertexNode getSrc() const { return src; }
	 VertexNode getDest() const { return dest; }
	 int getWeight() const { return weight; }
};
class Graph
{
	//这个线性存储的还是有点搞不清 看看以后能否实现他
	friend Graph union_Graph(Graph &g1, Graph &g2);
	friend Graph intersection_Graph(Graph &g1, Graph &g2);
	friend Graph complementary_Graph(Graph &g1, Graph &g2);
private:
	vector<Vertex> vertexSet;//点集
	vector<Edge> edgeSet;//边集

	//这个函数用来把不需要的元素从集合上删除 beg参数可以是remove_if返回的满足条件的最后一个一个元素之后的位置
	template<typename T> void do_erase_unnecessary(vector<T> &cont,typename vector<T>::iterator beg,typename vector<T>::iterator end)
	{
		cont.erase(beg, end);
	}
public:
	Graph(){}
	Graph(vector<Vertex> verset,vector<Edge> edges):vertexSet(verset),edgeSet(edges){}
	//判断是否为空图
	bool isEmpty() { return vertexSet.empty(); }
	//插入一个顶点
	void insertVertex(const Vertex &vertex) {
		vertexSet.push_back(vertex);
	}
	//插入一个边
	void insertEdge(const Edge &edge)
	{
		edgeSet.push_back(edge);
	}
	//删除一个顶点 以及他的边
	void deleteVertex(Vertex &vertex)
	{
		auto dest = vertexSet.begin();
		//????? = std::find(vertexSet.begin(), vertexSet.end(), [&vertex](const Vertex &vex) {return vex.getName() == vertex.getName(); });
		for (; dest != vertexSet.end(); ++dest)
		{
			if (dest->getName() == vertex.getName())
				break;
		}
		if (dest != vertexSet.end())
		{
			//find it;( 首先删除这个该点的边
			auto bb=std::remove_if(edgeSet.begin(), edgeSet.end(),
				[&vertex](Edge &e) {return e.getDest()->getName() == vertex.getName() || e.getSrc()->getName() == vertex.getName(); }
			);
			do_erase_unnecessary(edgeSet, bb, edgeSet.end());//完全删除掉那些不需要的点
			vertexSet.erase(dest);//删除这个点

		}


	}
	//删除边 顶点不必删除
	void deleteEdge(Edge &edge)
	{
		
		vector<Edge>::iterator b=std::remove_if(edgeSet.begin(), edgeSet.end(), [&edge](Edge &o) {return o.getEdgeName() == edge.getEdgeName(); });
		do_erase_unnecessary<Edge>(edgeSet,b, edgeSet.end());
	}
	//获取名为name的顶点
	Vertex* getVertex(const string &name)
	{
		for (auto i = vertexSet.begin(); i != vertexSet.end(); ++i)
		{
			if (i->getName() == name)
			{
				return &(*i);
			}
		}
		return nullptr;
	}
	//获取名为name的边
	Edge *getEdge(const string &name)
	{
		for (auto i = edgeSet.begin(); i != edgeSet.end(); ++i)
		{
			if (i->getEdgeName() == name)
			{
				return &(*i);
			}
		}
		return nullptr;
	}
	//获得指定名称的边的权
	const int getWeight(const string &name)
	{
		for (auto i = edgeSet.begin(); i != edgeSet.end(); ++i)
		{
			if (i->getEdgeName() == name)
			{
				return i->getWeight();
			}
		}
		return 0;
	}
	//获得边的弧顶 终点
	Vertex *getEdgeDest(const Edge &edge)
	{
		for (auto i = edgeSet.begin(); i != edgeSet.end(); ++i)
		{
			if (i->getEdgeName() == edge.getEdgeName())
			{
				return i->getDest();
			}
		}
		return nullptr;
	}
	//获得边的弧尾 起点
	Vertex *getEdgeSrc(const Edge &edge)
	{
		for (auto i = edgeSet.begin(); i != edgeSet.end(); ++i)
		{
			if (i->getEdgeName() == edge.getEdgeName())
			{
				return i->getSrc();
			}
		}
		return nullptr;
	}
	//获得vertex的首个邻接点 没有的话就返回nullptr
	Vertex *getFirstAdjVex(Vertex &vertex1);
	//获得下一个邻接点 没有的话就返回nullptr
	Vertex *getNextAdjVex(Vertex &vertex,Vertex &vertex2);
	//从ver开始的图的深度优先遍历
	void DFSTraverse(Vertex &ver);
	//从vex开始的图的广度优先遍历
	void BFSTraverse(Vertex &vex);
	//获得从v1到v2的一条最短的路径
	vector<Edge*> getShortPath(Vertex &v1, Vertex &v2);
	
	//debug
	void print_detail()
	{
		for (auto i = vertexSet.cbegin(); i != vertexSet.cend(); ++i)
			cout << "顶点：" << i->getName() << "\n";
		for (auto j = edgeSet.cbegin(); j != edgeSet.cend(); ++j)
			cout << "边" << j->getEdgeName() << "连接 " << j->getSrc()->getName() << "和" << j->getDest()->getName() << "\n";
		cout << endl;
	}
};
//做交交集
Graph intersection_Graph(Graph &g1, Graph &g2)
{
	/*
	set<Edge> edg1(g1.edgeSet.begin(), g1.edgeSet.end());
	set<Edge> edg2(g2.edgeSet.begin(), g2.edgeSet.end());
	vector<Edge> in_set;
	auto dest = std::insert_iterator<vector<Edge>>(in_set,in_set.begin());
	set_intersection(edg1.begin(), edg1.end(), edg2.begin(), edg2.end(), dest);

	set<Vertex> vex1(g1.vertexSet.begin(), g1.vertexSet.end());
	set<Vertex> vex2(g2.vertexSet.begin(), g2.vertexSet.end());
	vector<Vertex> in_vex_set;
	auto dest_vex = std::insert_iterator<vector<Vertex>>(in_vex_set, in_vex_set.begin());
	set_intersection(vex1.begin(), vex1.end(),vex2.begin(), vex2.end(), dest_vex);
	newgr.edgeSet=std::move(in_set);
	newgr.vertexSet=std::move(in_vex_set);
	*/
	Graph newgr;
	
	return newgr;
}
//做并集
Graph union_Graph(Graph &g1, Graph &g2)
{
	Graph newgr;
	/*
	for (auto i = g1.edgeSet.begin(); i != g1.edgeSet.end(); ++i)
	{
		for (auto j = g2.edgeSet.begin(); j != g2.edgeSet.end(); ++j)
		{
			newgr.insertEdge(*i);
			if (i->getEdgeName() != j->getEdgeName())
				newgr.insertEdge(*j);
		}
	}
	for (auto i = g1.vertexSet.begin(); i != g1.vertexSet.end(); ++i)
	{
		for (auto j = g2.vertexSet.begin(); j != g2.vertexSet.end(); ++j)
		{
			newgr.insertVertex(*j);
			if (i->getName() != j->getName())
				newgr.insertVertex(*i);
		}
	}
	*/
	return newgr;
}
//做g的补集 g1-g2 等价于C(g1)(g2)
Graph complementary_Graph(Graph &g1, Graph &g2) 
{
	Graph newgr;
	/*
	for (auto i = g1.edgeSet.begin(); i != g1.edgeSet.end(); ++i)
	{
		for (auto j = g2.edgeSet.begin(); j != g2.edgeSet.end(); ++j)
		{
			if (i->getEdgeName() != j->getEdgeName())
				newgr.insertEdge(*i);
		}
	}
	for (auto i = g1.vertexSet.begin(); i != g1.vertexSet.end(); ++i)
	{
		for (auto j = g2.vertexSet.begin(); j != g2.vertexSet.end(); ++j)
		{
			
			if (i->getName() != j->getName())
				newgr.insertVertex(*i);
		}
	}
	*/
	
	return newgr;
}

