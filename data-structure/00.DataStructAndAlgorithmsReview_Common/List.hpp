#pragma once
#include "Node.hpp"
//链表类
/*
修改于2017年2月24日
*/
//单链表
template<typename _Ty>
class SingleLinkList
{
	typedef Node<_Ty> NodeType;
private:
	NodeType *head;
	void do_insert_element(const _Ty &data)
	{
		//将新的元素插入到后面
		NodeType *node = head;//要确保node 不为nullptr
		while (node->getNext() != nullptr)
		{
			node = node->getNext();
		}
		node->setNext(new NodeType(data));
	}
	void do_remove_element(const _Ty &data)
	{
		NodeType *prior,*node;
		prior = head;
		node = head->getNext();
		while (node != nullptr && node->Data() !=data)
		{
			prior = node;
			node = node->getNext();
		}
		if (node)//如果为null表示没有找到元素 所以这里要判断一下
		{
			prior->setNext(node->getNext());
			delete node;
		}

	}
	void do_clear_allElemets()
	{
		NodeType *nd = head->getNext();
		NodeType *temp;
		while (nd != nullptr)
		{
			temp = nd->getNext();
			delete nd;
			nd = temp;
		}
		head->setNext(nullptr);
	}
	void do_sort_allElements()
	{
		head->Data() = 4410;
		//类似冒泡排序的一个算法
		NodeType *node = head;
		_Ty tempdata;//临时的数据
		if (node == nullptr || node->getNext() == nullptr)
			return;//如果表头为空或者是没有一个节点 那就结束
		int sz = size();//设置大小
		for (int i = 0; i < sz; ++i)
		{
			node = head->getNext();//每一次重新的循环都要从第一个元素开始
			for (int j = 0; j < sz - i-1; ++j)
			{
				if (node && node->getNext()/*这个是节点的判断*/ && (node->Data() > node->getNext()->Data()))
				{
					//如果后面的元素小于前面那么交换顺序
					tempdata = node->Data();
					node->Data() = node->getNext()->Data();
					node->getNext()->Data() = tempdata;
				}
				node = node->getNext();//next
			}
		}
	}
	void do_reverse_allElement_Traverse()
	{
		NodeType *curr, *prev,*temp;
		prev = head->getNext();
		if (prev == nullptr || prev->getNext()==nullptr)
			return;//none or only one element
		curr = prev->getNext();//获取第二个节点的指针
		prev->setNext(nullptr);//第一个节点变成了最后一个了
		while (curr != nullptr)
		{
			temp = curr->getNext();//保存下一个
			curr->setNext(prev);//前驱变成了后继
			prev = curr;
			curr = temp;
		}
		head->setNext(prev);//表头指向新的第一个节点

	}
public:
	SingleLinkList():head(new NodeType()){}
	SingleLinkList(const SingleLinkList&) = delete;
	SingleLinkList(SingleLinkList&&) = delete;
	SingleLinkList &operator=(const SingleLinkList&) = delete;
	SingleLinkList &operator=(SingleLinkList&&) = delete;
	~SingleLinkList() { do_clear_allElemets(); delete head; }
	//接口
	void insert(const _Ty data)
	{
		do_insert_element(data);
	}
	void remove(const _Ty data)
	{
		do_remove_element(data);
	}
	void clearAll() { do_clear_allElemets(); }
	size_t size() const
	{
		NodeType *nd = head;
		size_t sz = 0;
		while (nd->getNext() !=nullptr)
		{
			++sz;
			nd = nd->getNext();
		}
		return sz;
	}
	void debug_output_allElements(std::ostream &os)
	{
		NodeType *nd = head->getNext();
		while (nd != nullptr)
		{
			os << nd->Data() << " ";
			nd = nd->getNext();
		}
		os << std::endl;
	}
	//排序
	void sort()
	{
		do_sort_allElements();
	}
	//逆置
	void reverse_traverse()
	{
		do_reverse_allElement_Traverse();
	}
	//寻找中间的节点
	NodeType *findMid()
	{
		//原理 就是_head向前移动两个 temp向前移动一个 当_head不再是没有下一个了那么就可以返回此时的temp
		NodeType *_head = head->getNext();
		NodeType *temp = _head,*mid=nullptr;
		while (_head  && _head->getNext() && _head->getNext()->getNext() != nullptr)
		{
			_head = _head->getNext()->getNext();
			temp = temp->getNext();
			mid = temp;
		}
		return mid;
	}
	//是否为空
	bool isEmpty()
	{
		return !head || (head->getNext() == nullptr);
	}
};
//循环双链表
template<typename _Ty>
class DoubleCircleLinkList
{
	typedef DoubleNode<_Ty> NodeType;
private:
	NodeType *head;
	void do_insert(const _Ty &data)
	{
		//默认插入到尾部
		NodeType *ptr = new NodeType(data, head, head->getPrev());
		head->getPrev()->setNext(ptr);
		head->setPrev(ptr);

	}
	void do_remove(const _Ty &data)
	{
		NodeType *prev=head, *curr=head->getNext();
		while (curr && curr != head && curr->Data() != data)
		{
			prev = curr;
			curr=curr->getNext();
		}
		if (curr != head)
		{
			prev->setNext(curr->getNext());
			curr->getNext()->setPrev(prev);
			delete curr;
		}
	}
	void do_clear()
	{
		if (!isEmpty())
		{
			NodeType *temp, *node = head->getNext();
			while (node != head)
			{
				temp = node->getNext();
				delete node;
				node = temp;
			}
			head->setNext(head);
			head->setPrev(head);
		}
		
	}
public:
	DoubleCircleLinkList() :head(new NodeType())
	{
		head->setNext(head);
		head->setPrev(head);
	}
	~DoubleCircleLinkList() { do_clear(); delete head; }
	bool isEmpty()
	{
		return head->getPrev() == head;
	}
	void insert(const _Ty data)
	{
		do_insert(data);
	}
	void remove(const _Ty data) { do_remove(data); }
	size_t size() const
	{
		size_t sz = 0;
		NodeType *nd = head->getNext();
		while (nd != head)
		{
			++sz;
			nd = nd->getNext();
		}
		return sz;
	}
	void clearAll() { do_clear(); }
	void debug_output_all_begin(std::ostream &os)
	{
		NodeType *temp = head->getNext();
		while (temp != head)
		{
			os << temp->Data() << " ";
			temp = temp->getNext();
		}
		os << std::endl;
	}
	void debug_output_all_last(std::ostream &os)
	{
		NodeType *temp = head->getPrev();
		while (temp != head)
		{
			os << temp->Data() << " ";
			temp = temp->getPrev();
		}
		os << std::endl;
	}
	void sort()
	{
		//默认从小到大排序
		NodeType *ptr;
		int sz = size();
		_Ty temp;
		if (sz <= 1)
			return;
		for (int i = 0; i < sz; ++i)
		{
			ptr = head->getNext();
			for (int j = 0; j < sz - i-1; ++j)
			{
				if (ptr && ptr->getNext() && ptr->getNext()->Data() < ptr->Data())
				{
					temp = ptr->Data();
					ptr->Data() = ptr->getNext()->Data();
					ptr->getNext()->Data() = temp;
				}
				ptr = ptr->getNext();
			}
		}
	}
	const NodeType *getHead() const { return head; }
	/*迭代器设计*/
	struct iterator
	{
		NodeType *node;
		iterator() :node(nullptr) {}
		iterator(NodeType *nd) :node(nd) {}
		_Ty &operator*()
		{
			return node->Data();
		}
		NodeType *operator->()
		{
			return node;
		}
		iterator &operator++()
		{
			if (node)
			{
				node = node->getNext();
				
			}
			return *this;
		}
		iterator operator++(int)
		{
			iterator temp(*this);
			node = node->getNext();
			return temp;
		}
		iterator &operator--()
		{
			if (node)
			{
				node = node->getPrev();
			}
			return *this;
		}
		iterator operator--(int)
		{
			iterator temp(*this);
			node = node->getPrev();
			return temp;
		}
		bool operator!=(const iterator &rhs) { return rhs.node != this->node; }
		bool operator==(const iterator &rhs) { return rhs.node == this->node; }
		const NodeType *getPtr() { return node; }
	};
	iterator begin()
	{
		return head->getNext();
	}
	iterator end()
	{
		return head;//最后的一个元素（一遍）的下一个是表头 因为最后一个元素next就是表头了
	} 

};