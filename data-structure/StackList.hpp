#pragma once
#include "stdafx.h"
template<typename T> class StackListNode
{
	typedef StackListNode *Node;
public:
	T &getData() { return data; }
	Node getNext() { return next; }
	void setNext(Node nt) { next = nt; }
	void setData(T da) { data = da; }
private:
	T data;
	Node next;
};
template<typename T> class StackList
{
public:
	typedef StackListNode<T> NodeType;
	typedef NodeType *Node;
	StackList():ptr(nullptr){}
	bool isEmpty()
	{
		return ptr == nullptr;
	}
	void Pop()
	{
		if (!isEmpty())
		{
			Node fir = ptr->getNext();
			delete ptr;
			ptr = fir;
		}
		else
		{
			
		}
	}
	T &Top()
	{
		if (!isEmpty())
		{
			return ptr->getData();
		}
		else
		{

		}
	}
	T TopAndPop()
	{
		if (!isEmpty())
		{
			Node fir = ptr->getNext();
			T data = ptr->getData();
			delete ptr;
			ptr = fir;
			return data;
		}
		else
		{
			throw std::runtime_error("无法弹出空栈的元素！");
		}
	}
	void Push(T da)
	{
		Node n = new NodeType();
		if (n)
		{
			if (isEmpty())
			{
				n->setNext(nullptr);
				n->setData(da);
				ptr = n;
			}
			else
			{
				n->setNext(ptr);
				n->setData(da);
				ptr = n;
			}
		}
	}
	~StackList()
	{
		Node d;// = ptr->getNext();
		while (!isEmpty())
		{
			d = ptr->getNext();
			delete ptr;
			ptr = d;
		}
	}
private:
	Node ptr;
};