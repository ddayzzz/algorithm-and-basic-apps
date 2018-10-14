#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <iterator>
using namespace std;
//����ĳ�����������
class Vertex
{
private:
	string name;//���涥�������
public:
	Vertex(const string &n):name(n){}
	const string getName() const { return name; }
	void setName(const string &n) { name = n; }
};
class Edge
{
	typedef Vertex *VertexNode;//����Ŀ�궥���ָ������
private:
	VertexNode src;//����Ǳ������
	VertexNode dest;//��������յ�
	string edgename;//�ߵ�����
	int weight;//�ߵ�Ȩֵ
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
	//������Դ洢�Ļ����е�㲻�� �����Ժ��ܷ�ʵ����
	friend Graph union_Graph(Graph &g1, Graph &g2);
	friend Graph intersection_Graph(Graph &g1, Graph &g2);
	friend Graph complementary_Graph(Graph &g1, Graph &g2);
private:
	vector<Vertex> vertexSet;//�㼯
	vector<Edge> edgeSet;//�߼�

	//������������Ѳ���Ҫ��Ԫ�شӼ�����ɾ�� beg����������remove_if���ص��������������һ��һ��Ԫ��֮���λ��
	template<typename T> void do_erase_unnecessary(vector<T> &cont,typename vector<T>::iterator beg,typename vector<T>::iterator end)
	{
		cont.erase(beg, end);
	}
public:
	Graph(){}
	Graph(vector<Vertex> verset,vector<Edge> edges):vertexSet(verset),edgeSet(edges){}
	//�ж��Ƿ�Ϊ��ͼ
	bool isEmpty() { return vertexSet.empty(); }
	//����һ������
	void insertVertex(const Vertex &vertex) {
		vertexSet.push_back(vertex);
	}
	//����һ����
	void insertEdge(const Edge &edge)
	{
		edgeSet.push_back(edge);
	}
	//ɾ��һ������ �Լ����ı�
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
			//find it;( ����ɾ������õ�ı�
			auto bb=std::remove_if(edgeSet.begin(), edgeSet.end(),
				[&vertex](Edge &e) {return e.getDest()->getName() == vertex.getName() || e.getSrc()->getName() == vertex.getName(); }
			);
			do_erase_unnecessary(edgeSet, bb, edgeSet.end());//��ȫɾ������Щ����Ҫ�ĵ�
			vertexSet.erase(dest);//ɾ�������

		}


	}
	//ɾ���� ���㲻��ɾ��
	void deleteEdge(Edge &edge)
	{
		
		vector<Edge>::iterator b=std::remove_if(edgeSet.begin(), edgeSet.end(), [&edge](Edge &o) {return o.getEdgeName() == edge.getEdgeName(); });
		do_erase_unnecessary<Edge>(edgeSet,b, edgeSet.end());
	}
	//��ȡ��Ϊname�Ķ���
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
	//��ȡ��Ϊname�ı�
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
	//���ָ�����Ƶıߵ�Ȩ
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
	//��ñߵĻ��� �յ�
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
	//��ñߵĻ�β ���
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
	//���vertex���׸��ڽӵ� û�еĻ��ͷ���nullptr
	Vertex *getFirstAdjVex(Vertex &vertex1);
	//�����һ���ڽӵ� û�еĻ��ͷ���nullptr
	Vertex *getNextAdjVex(Vertex &vertex,Vertex &vertex2);
	//��ver��ʼ��ͼ��������ȱ���
	void DFSTraverse(Vertex &ver);
	//��vex��ʼ��ͼ�Ĺ�����ȱ���
	void BFSTraverse(Vertex &vex);
	//��ô�v1��v2��һ����̵�·��
	vector<Edge*> getShortPath(Vertex &v1, Vertex &v2);
	
	//debug
	void print_detail()
	{
		for (auto i = vertexSet.cbegin(); i != vertexSet.cend(); ++i)
			cout << "���㣺" << i->getName() << "\n";
		for (auto j = edgeSet.cbegin(); j != edgeSet.cend(); ++j)
			cout << "��" << j->getEdgeName() << "���� " << j->getSrc()->getName() << "��" << j->getDest()->getName() << "\n";
		cout << endl;
	}
};
//��������
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
//������
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
//��g�Ĳ��� g1-g2 �ȼ���C(g1)(g2)
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

