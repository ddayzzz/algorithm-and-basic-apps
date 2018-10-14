#pragma once
#include "Node.hpp"
//������
/*
�޸���2017��2��24��
*/
//������
template<typename _Ty>
class SingleLinkList
{
	typedef Node<_Ty> NodeType;
private:
	NodeType *head;
	void do_insert_element(const _Ty &data)
	{
		//���µ�Ԫ�ز��뵽����
		NodeType *node = head;//Ҫȷ��node ��Ϊnullptr
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
		if (node)//���Ϊnull��ʾû���ҵ�Ԫ�� ��������Ҫ�ж�һ��
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
		//����ð�������һ���㷨
		NodeType *node = head;
		_Ty tempdata;//��ʱ������
		if (node == nullptr || node->getNext() == nullptr)
			return;//�����ͷΪ�ջ�����û��һ���ڵ� �Ǿͽ���
		int sz = size();//���ô�С
		for (int i = 0; i < sz; ++i)
		{
			node = head->getNext();//ÿһ�����µ�ѭ����Ҫ�ӵ�һ��Ԫ�ؿ�ʼ
			for (int j = 0; j < sz - i-1; ++j)
			{
				if (node && node->getNext()/*����ǽڵ���ж�*/ && (node->Data() > node->getNext()->Data()))
				{
					//��������Ԫ��С��ǰ����ô����˳��
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
		curr = prev->getNext();//��ȡ�ڶ����ڵ��ָ��
		prev->setNext(nullptr);//��һ���ڵ��������һ����
		while (curr != nullptr)
		{
			temp = curr->getNext();//������һ��
			curr->setNext(prev);//ǰ������˺��
			prev = curr;
			curr = temp;
		}
		head->setNext(prev);//��ͷָ���µĵ�һ���ڵ�

	}
public:
	SingleLinkList():head(new NodeType()){}
	SingleLinkList(const SingleLinkList&) = delete;
	SingleLinkList(SingleLinkList&&) = delete;
	SingleLinkList &operator=(const SingleLinkList&) = delete;
	SingleLinkList &operator=(SingleLinkList&&) = delete;
	~SingleLinkList() { do_clear_allElemets(); delete head; }
	//�ӿ�
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
	//����
	void sort()
	{
		do_sort_allElements();
	}
	//����
	void reverse_traverse()
	{
		do_reverse_allElement_Traverse();
	}
	//Ѱ���м�Ľڵ�
	NodeType *findMid()
	{
		//ԭ�� ����_head��ǰ�ƶ����� temp��ǰ�ƶ�һ�� ��_head������û����һ������ô�Ϳ��Է��ش�ʱ��temp
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
	//�Ƿ�Ϊ��
	bool isEmpty()
	{
		return !head || (head->getNext() == nullptr);
	}
};
//ѭ��˫����
template<typename _Ty>
class DoubleCircleLinkList
{
	typedef DoubleNode<_Ty> NodeType;
private:
	NodeType *head;
	void do_insert(const _Ty &data)
	{
		//Ĭ�ϲ��뵽β��
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
		//Ĭ�ϴ�С��������
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
	/*���������*/
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
		return head;//����һ��Ԫ�أ�һ�飩����һ���Ǳ�ͷ ��Ϊ���һ��Ԫ��next���Ǳ�ͷ��
	} 

};