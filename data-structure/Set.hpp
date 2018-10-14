#pragma once
#include "stdafx.h"
const size_t DefaultSzie = 100;
class VectorSet
{
private:
	int *flags=nullptr;
	size_t size=0;
	bool vaildIndex(int index) const 
	{
		if (index >= 0 && index < size)
		{
			return true;
		}
		return false;
	}
public:
	VectorSet(size_t sz = DefaultSzie) :size(sz), flags(new int[sz]) { makeEmpty(); }
	~VectorSet() { delete flags; }
	size_t getSize() const { return size; }
	bool isMember(const int i) const 
	{
		if (vaildIndex(i) && flags !=nullptr)
		{
			return flags[i] != 0;
		}
	}
	bool operator==(const VectorSet &vec)
	{
		if (vec.getSize() == size)
		{
			for (int i = 0; i < size; ++i)
			{
				if (vec.getFlag(i) !=flags[i])
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}
	bool isEmpty() const 
	{
		for (int i = 0; i < size; ++i)
		{
			if (flags[i])
				return false;
		}
		return true;
	}
	int getFlag(int index) const
	{
		if (flags != nullptr && vaildIndex(index))
		{
			return flags[index];
		}
		return 0;
	}
	VectorSet &operator=(const VectorSet &vec)
	{
		if (vec.getSize() == size)
		{
			for (int i = 0; i < size; ++i)
			{
				flags[i] = vec.getFlag(i);
			}
		}
		return *this;
	}
	VectorSet &operator+(const VectorSet &vec)
	{
		if (vec.getSize() == size)
		{
			//新创建的数组的大小取决于最大的集合势
			for (int i = 0; i < vec.getSize(); ++i)
			{
				flags[i] = flags[i] || vec.getFlag(i);
			}
		}
		return *this;
	}
	VectorSet &operator*(const VectorSet &vec)
	{
		if (vec.getSize() == size)
		{
			for (int i = 0; i < size; ++i)
			{


				flags[i] = vec.getFlag(i) && flags[i];

			}
		}
		return *this;
	}
	VectorSet &operator-(const VectorSet &vec)
	{
		if (size ==vec.getSize())
		{
			for (int i = 0; i < size; ++i)
			{
				flags[i] = flags[i] && (!vec.getFlag(i));
			}
		}
		return *this;
	}
	VectorSet &add(int v)
	{
		if (flags != nullptr && vaildIndex(v))
		{
			if (flags[v] == 0)
			{
				flags[v] = 1;
			}
		}
		return *this;
	}
	VectorSet &deleteData(int v)
	{
		if (flags != nullptr && vaildIndex(v))
		{
			if (flags[v] == 1)
			{
				flags[v] = 0;
			}
		}
		return *this;
	}
	void makeEmpty()
	{
		if (flags != nullptr)
		{
			for (int i = 0; i < size; ++i)
				flags[i] = 0;
		}
	}
	friend std::ostream &operator<<(std::ostream &os,const VectorSet &vec);
};
std::ostream &operator<<(std::ostream &os, const VectorSet &vec)
{
	if (vec.size > 0 && !vec.isEmpty())
	{
		os << "{ ";
		int i = 0;
		do {
			if (vec.flags[i])
			{
				os << i << " ";
			}
				
			++i;
		} while (i < vec.size);
		os << "}";
	}
	else
	{
		os << "{ NOTHING }";
	}
	os << endl;
	return os;
}
template<typename T> class ListSet;
template<typename T> class ListSetNode
{
	friend class ListSet<T>;
	friend std::ostream &operator<<(std::ostream &os, const ListSet<T> &li);
private:
	ListSetNode<T> *next;
	T data;
	ListSetNode(T dat):data(dat),next(nullptr){}
};
template<typename T> class ListSet
{
private:
	typedef ListSetNode<T> NodeType;
	typedef NodeType *Node;
	Node root;
public:
	ListSet():root(nullptr){}
	~ListSet() { clear(); }
	bool isEmpty() const 
	{
		return root == nullptr;
	}
	ListSet(const ListSet &set):root(nullptr)
	{
		Node nd = set.root;
		while (nd != nullptr)
		{
			add(nd->data);
			nd = nd->next;
		}
		
	}
	ListSet &add(T dat)
	{
		if (isEmpty())
		{
			root = new NodeType(dat);
		}
		else
		{
			Node prior = root;
			Node current = root->next;
			Node tmp = new NodeType(dat);
			//首先判断首元素 有可能是首元素比带插入的元素大
			if (dat < root->data)
			{
				tmp->next = prior;//即将成为首元素
				root = tmp;//改为首元素
				return *this;//返回
			}
			while (current && current->data < dat)
			{
				prior = current;
				current = current->next;
			}
			if (current == nullptr)
			{
				//插入到尾后 但是要排除首元素的问题
				prior->next = tmp;
			}
			else
			{
				if (current->data == dat || prior->data==dat)
				{
					return *this;//相等或者是 前驱元素相等
				}
				else
				{
					if (current->data > dat)
					{
						prior->next = tmp;
						tmp->next = current;
					}
				}
			}
		}
		return *this;
	}
	ListSet &deleteData(T dat)
	{
		if (!isEmpty())
		{
			Node prior = root;
			Node curr = root->next;
			if (prior->data == dat)
			{
				root = curr;
				delete prior;
				return *this;
			}
			while (curr && curr->data != dat)
			{
				prior = curr;
				curr = curr->next;
			}
			if (curr != nullptr)
			{
				prior->next = curr->next;
				delete curr;
			}
		}
		return *this;
	}
	void clear()
	{
		if (!isEmpty())
		{
			Node tmp = root;
			while (root)
			{
				tmp = root;
				root = root->next;
				delete tmp;
			}
		}
	}
	bool operator==(const ListSet &set)
	{
		if (isEmpty() && set.isEmpty())
		{
			return true;
		}
		int cnt1 = 0;
		int cnt2 = 0;
		Node curr_1 = root;
		Node curr_2 = set.root;
		while (curr_1 && curr_2)
		{
			if (curr_1->data != curr_2->data)
			{
				return false;
			}
			else
			{
				curr_1 = curr_1->next;
				curr_2 = curr_2->next;
			}
		}
		return (curr_1 == nullptr && curr_2 == nullptr);
	}
	ListSet &operator=(const ListSet &set)
	{
		clear();//清除
		Node nd = set.root;
		while (nd != nullptr)
		{
			add(nd->data);//赋值
			nd = nd->next;
		}
		return *this;
	}
	ListSet &operator*(const ListSet &set)
	{
		if (!set.isEmpty() && !isEmpty())
		{
			ListSet<T> *lis = new ListSet<T>(*this);
			lis->operator-(set);
			this->operator-(*lis);
			delete lis;//求交集 A+B=A-(A-B)
		}
		return *this;
	}
	ListSet &operator+(const ListSet &set)
	{
		if (!set.isEmpty())
		{
			Node nd = set.root;
			while (nd)
			{
				add(nd->data);//添加元素 相同的元素自动跳过
				nd = nd->next;
			}
		}
		return *this;
	}
	ListSet &operator-(const ListSet &set)
	{
		if (!isEmpty())
		{
			Node nd = set.root;
			while (nd)
			{
				deleteData(nd->data); //删除set与本集合共有的元素 即为补集
				nd = nd->next;
			}
		}
		return *this;
	}
	friend std::ostream &operator<<(std::ostream &os, const ListSet &li)
	{
		if (li.isEmpty())
		{
			os << "{ NOTHING }\n";
		}
		else
		{
			os << "{ ";
			Node node = li.root;
			while (node)
			{
				os << node->data << " ";
				node = node->next;
			}
			os << "}"<<endl;
		}
		return os;
	}
	
};

