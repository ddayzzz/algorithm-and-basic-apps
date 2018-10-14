#pragma once
#include "stdafx.h"
#include <cstdlib>
#include <iterator>
#include <list>
#include <iostream>
template<typename T> class DoubleCirList;
template<typename T> class DoubleCirNode
{
	template<typename T> friend  class  DoubleCirList;
public:
	typedef T DataType;
	typedef DoubleCirNode<DataType> *Node;
	typedef DoubleCirNode<DataType> NodeType;
	//构造
	DoubleCirNode():prior(nullptr),next(nullptr){}
	DoubleCirNode(DataType d) :prior(nullptr), next(nullptr),data(d) {}
	template<typename X> DoubleCirNode(const DoubleCirNode<X>&) = delete;
	template<typename X> DoubleCirNode(DoubleCirNode<X>&&) = delete;
	//操作
	template<typename X> DoubleCirNode<DataType> &operator=(const DoubleCirNode<X>&) = delete;
	template<typename X> DoubleCirNode<DataType> &operator=( DoubleCirNode<X>&&) = delete;
	DataType &getData() { return data; }
private:
	DoubleCirNode<DataType> *prior;
	DoubleCirNode<DataType> *next;
	DataType data;
};
template<typename T> class DoubleCirList {
	typedef T DataType;
	typedef DoubleCirNode<T> NodeType;
	typedef NodeType *Node;
public:
	//构造函数
	DoubleCirList():curr(nullptr),first(nullptr){}
	template<typename X> DoubleCirList(const DoubleCirList<X>&) = delete;//删除所有的拷贝构造函数和拷贝运算符
	template<typename X> DoubleCirList(DoubleCirList<X>&&) = delete;
	~DoubleCirList()
	{
		freeList();
	}
	//操作
	 DoubleCirList<T> &operator=(const DoubleCirList<T>&) = delete;
	 DoubleCirList<T> &operator=(DoubleCirList<T>&&) = delete;
	 class iterator
	 {
	 public:
		 friend void erase(iterator pos);
		 typedef bidirectional_iterator_tag iterator_category;//双向迭代器
		 typedef T&                        reference;
		 typedef T                         value_type;
		 typedef int                        difference_type;
		 typedef T*                         pointer;
		 //构造函数
		 iterator(Node d) :p(d) {}
		 iterator() :p(nullptr) {}
		 iterator(const iterator& y) :p(y.p) {}
		 //运算符
		 T &operator->()
		 {
			 return p;
		 }
		 T &operator*()
		 {
			 if (p != nullptr)
			 {
				 return p->getData();
			 }
			 else
			 {
				 throw std::runtime_error("非法的解引用操作：试图解引用nullptr");
			 }
		 }
		 iterator &operator++() {
			 if (p != nullptr)
			 {
				 p = p->next;
			 }
			 return *this;
		 }
		 iterator &operator--() {
			 if (p != nullptr)
			 {
				 p = p->prior;
			 }
			 return *this;
		 }
		 iterator operator++(int) {
			 if (p != nullptr)
			 {
				 iterator temp(*this);
				 p = p->next;
				 return temp;
			 }
			 else { return this; }
		 }
		 iterator operator--(int) {
			 if (p != nullptr)
			 {
				 iterator temp(*this);
				 p = p->prior;
				 return temp;
			 }
			 else { return this; }
		 }
		 bool operator==(const iterator &rhs) const { return p == rhs.p; }
		 bool operator!=(const iterator &rhs) const { return p != rhs.p; }
		 std::ostream &operator<<(std::ostream &os) {
			 os << p->getData();
			 return os;
		 }
		 const Node getNodePtr()
		 {
			 return p;
		 }
	 private:
		 Node p;
	 };
	bool isempty()
	{
		return first == nullptr;
	}
	//将元素插入到末尾
	void push_back(DataType da) { insert_element_back(da); }
	//将元素插入到指定位置的后面
	void insert_back(DataType da, Node n) { insert_element_back(da, n); }
	//将元素插入到指定位置的前面
	void insert_front(Node n);
	//将元素删除
	void erase(Node n) { delete_element(n); }
	//将curr递增 可循环
	void setNext() {
		if (curr != nullptr)
		{
			curr = curr->next;
		}
	}
	void setPrior()
	{
		if (first != nullptr)
		{
			curr = curr->prior;
		}
	}
	//得到当前指向的节点
	Node getCurrent() { return curr; }
	//获取当前节点的值
	DataType &getData() { if (curr != nullptr) { return curr->getData(); } else { return 0; } }
	//获取指定位置的节点的值
	DataType &getData(Node n) { if (n != nullptr) { return n->getData(); } else { return 0; } }
	//销毁所有元素
	void free() { freeList(); }
	//删除指定区间的链表元素[beg,end)
	void deleteList(Node beg, Node end,int direct);
	//计数
	void deleteList(Node beg, int cnt);
	Node getFirst()
	{
		return first;
	}
	//迭代器设计
	
	//支持迭代器的操作
	iterator begin()
	{
		return first;
	}
	iterator end()
	{
		
		if (first != nullptr)
		{
			return first->prior;
		}
	}
	void erase(iterator pos)
	{
		delete_element(pos.getNodePtr());
	}
	
	const iterator cbegin()
	{
		return begin();
	}
	const iterator cend()
	{
		/*
		if (first != nullptr)
		{
			return first->prior;
		}
		*/
		
		return end();
	}
private:
	Node curr;
	Node first;
	//私有函数区
	Node findlast()
	{
		if (first != nullptr)
		{
			return first->prior;
		}
		else
		{
			return nullptr;
		}
	}
	void insert_element_back(DataType value, Node pos = nullptr)
	{
		Node nNode = new NodeType();
		if (nNode)
		{
			//allocate success
			nNode->getData() = value;
			Node las = nullptr;
			if (pos == nullptr)
			{
				las = findlast();
				if (las != nullptr)
				{
					las->next = nNode;
					nNode->prior = las;
					nNode->next = first;
					first->prior = nNode;
				}
				else
				{
					//向空的链表插入
					first = nNode;
					nNode->next = first;
					nNode->prior = first;
					curr = nNode;
				}
			}
			else
			{
				//从指定位置插入
				if (pos == findlast())
				{
					insert_element_back(value);
				}
				else
				{
					nNode->next = pos->next;
					nNode->next->prior = nNode;
					nNode->prior = pos;
					pos->next = nNode;
				}
			}

		}
	}
	void freeList()
	{
		if (!isempty())
		{
			Node p = first->next;
			while (p != nullptr && p != first)
			{
				Node temp = p->next;
				delete p;
				p = temp;
			}
			delete p;
			first = curr = nullptr;
		}
	}
	void delete_element(Node pos)
	{
		if (!isempty() && pos !=nullptr)
		{
			if (pos != first)
			{
				Node nt = pos->next;
				nt->prior = pos->prior;
				pos->prior->next = nt;
				if (curr == pos)
					curr = nt;
				delete pos;
			}
		}
	}

};