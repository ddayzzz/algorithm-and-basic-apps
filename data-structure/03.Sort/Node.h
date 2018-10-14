#pragma once
#include "../stdafx.h"
#include <stdexcept>
#include <initializer_list>
template<typename T> struct Node
{
	template<typename X> Node(X e):pdata(e){}
	T pdata;
	Node *next=nullptr;
	Node *operator++(int) { return next; }
	Node *operator++() { return next; }

};

template<typename T> class List
{
public:
	typedef T elementtype;//元素类型
	typedef struct Node<T> *PtrtoList;//指向链表类型的类型别名
	typedef PtrtoList Position;//描述链表位置的指针的类型别名
	//构造函数(有关复制的话可以以后实现)
	List() :header(new Node<elementtype>(0)) {}
	List(const List&) = delete;
	List(List&&) = delete;
	//赋值运算符
	List &operator=(const List&) = delete;
	List &operator=(List&&) = delete;
	//析构函数
	~List() { delete_after_all(header); delete header; }
	//接口 数据访问
	elementtype &getdata(unsigned i) //返回当前链表节点所保存的数据
	{
		Position p = index(i);
		if (p != nullptr)
		{
			return p->pdata;
		}
		else
		{
			throw std::runtime_error("节点无效! ");
		}
	}
	elementtype &getdata(Position p) //返回当前链表节点所保存的数据
	{
		if (p != nullptr)
		{
			return p->pdata;
		}
		else
		{
			throw std::runtime_error("节点无效! ");
		}
	}
	template<typename X> void push_back(X e)
	{ 
		Position ek = getlast();
		if (ek != nullptr)
		{
			add_element_after(e, ek);
		}
	
	}//将数据加入到链表末尾
	template<typename X> Position insert_after(X e, Position pos) { return add_element_after(e, pos); }//将e添加到pos的后面 返回添加后的元素节点地址
	Position erase_after(Position pos) { return delete_after(pos); }//删除pos之后的一个元素 返回删除元素之后的节点地址
	//Position erase_range(Position pos, Position end) { return delete_range(pos, end); }//删除[pos,end)的所有元素 返回end
	void clear() { delete_after_all(header); }//删除所有元素 但是不删除表头
	//接口 信息
	Position head() { return header; }//返回表头节点地址
	Position begin() { return header->next; }//返回链表的首元素的地址
	Position back() { return getlast(); }//返回最后一个元素的笛子地址
	unsigned int size() { return getsize(); }//返回当前链表的大小 不包含表头
	Position find(elementtype t) { return find_matched(t); }//返回第一个等于指定元素的节点地址
	bool empty() { return header->next == nullptr; }
	//接口 运算符
	elementtype &operator[](unsigned int i) 
	{
		return getdata(i);
	}//通过索引访问数据
private:
	Position header = nullptr;//表头元素
	//添加元素
	template<typename X> Position add_element_after(X t, Position pos)
	{

		if (header == nullptr)
		{
			return nullptr;
		}
		else
		{
			Position p = new Node<elementtype>(t);
			p->next = pos->next;
			pos->next = p;
			return p;
		}
	}
	Position delete_after(Position pos)
	{
		if (pos != nullptr)
		{
			Position te = pos->next;
			if (te != nullptr)
			{
				pos->next = te->next;
				delete te;
				return pos->next;
			}
			else
			{
				//尾后元素不用删除
				return nullptr;
			}
		}
		else
		{
			return nullptr;
		}
	}
	Position delete_after_all(Position pos)
	{
		if (pos != nullptr)
		{
			Position te = pos->next;
			Position p;
			pos->next = nullptr;
			while (te != nullptr)
			{
				p = te->next;
				delete te;
				te = p;
			}
		}
		else
		{
			return nullptr;
		}
	}
	Position index(unsigned i)
	{
		unsigned id = 0;
		Position p = header->next;
		while (p != nullptr && id < i)
		{
			++id;
			p = p->next;
		}
		return p;
	}
	//查找第一个匹配的元素
	Position find_matched(elementtype t)
	{
		Position pos = head();
		pos = pos->next;
		while (pos != nullptr && pos->pdata != t)
		{
			pos = pos->next;
		}
		return pos;
	}
	Position getlast()
	{
		Position pos = head();
		while (pos !=nullptr && pos->next != nullptr)
		{
			pos = pos->next;
		}
		return pos;
	}
	unsigned getsize()
	{
		unsigned id = 0;
		Position p = header->next;
		while (p != nullptr)
		{
			++id;
			p = p->next;
		}
		return id;
	}
	Position delete_range(Position pos,Position end)
	{
		if (pos != nullptr)
		{
			if (pos != head())
			{
				Position te = pos;
				Position p;
				pos->next = end;
				while (te != end)
				{
					p = te->next;
					delete te;
					te = p;
				}
				return end;
			}
			else
			{
				throw std::runtime_error("不允许删除表头元素. ");
			}
		}
		else
		{
			return nullptr;
		}
	}
};
template<typename CONTAINER> class list_iterator
{
public:
	typedef CONTAINER eletype;//表示容器元素类型
	list_iterator() : pos(nullptr){}
	list_iterator(Node<eletype> *p) :pos(p) {}
	list_iterator &operator=(const list_iterator<eletype> &p) { pos = p.pos; return *this; }

	list_iterator &operator++() { pos = pos->next; return *this; }
	list_iterator operator++(int) { Node<eletype> *temp = pos; pos = pos->next; return temp; }
	bool operator==(const list_iterator<eletype> &i) { return i.pos == pos; }
	bool operator!=(const list_iterator<eletype> &i) { return i.pos != pos; }
	operator Node<eletype> *() { return pos; }
	eletype &operator*()
	{
		if (pos != nullptr)
		{
			return pos->pdata;
		}
		else
		{
			throw std::runtime_error("错误! 访问一个不存在的位置");
		}
	}
private:
	Node<eletype> *pos;
};