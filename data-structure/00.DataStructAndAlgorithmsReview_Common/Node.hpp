#pragma once
#include "../stdafx.h"
#include <list>
//这是节点的头文件
//修改于2017年2月24日
//这是一个普通的节点类的定义 含有一个指针域一个数据域
template<typename ty>
class Node
{
private:
	Node *next;
	ty data;
	
public:
	//这里不用实现与接口分离
	Node():next(nullptr){}
	Node(ty _da,Node *_next=nullptr):data(_da),next(_next){}
	Node(const Node&) = delete;
	Node(Node &&) = delete;
	Node &operator=(const Node&) = delete;
	Node &operator=(Node &&) = delete;
	~Node() {}
	//数据访问
	//获取数据的引用
	ty &Data() { return data; }
	//获取下一节点的指针
	Node *getNext()const { return next; }
	//设置下一节点的指针
	void setNext(Node *_next) { next = _next; }
};
//这是一个普通的双节点类的定义 含有两个指针域一个数据域
template<typename ty>
class DoubleNode
{
private:
	DoubleNode *next;
	DoubleNode *prev;
	ty data;

public:
	
	//这里不用实现与接口分离
	DoubleNode() :next(nullptr) {}
	DoubleNode(ty _da, DoubleNode *_next = nullptr,DoubleNode *_prev=nullptr) :data(_da), next(_next),prev(_prev) {}
	DoubleNode(const DoubleNode&) = delete;
	DoubleNode(DoubleNode &&) = delete;
	DoubleNode &operator=(const DoubleNode&) = delete;
	DoubleNode &operator=(DoubleNode &&) = delete;
	~DoubleNode() {}
	//数据访问
	//获取数据的引用
	ty &Data() { return data; }
	const ty &Data() const  { return data; }
	//获取下一节点的指针
	DoubleNode *getNext()const { return next; }
	//设置下一节点的指针
	void setNext(DoubleNode *_next) { next = _next; }
	//获取上一节点的指针
	DoubleNode *getPrev()const { return prev; }
	//设置上一节点的指针
	void setPrev(DoubleNode *_p) { prev = _p; }
};