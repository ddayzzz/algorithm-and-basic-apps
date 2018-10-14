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
	typedef T elementtype;//Ԫ������
	typedef struct Node<T> *PtrtoList;//ָ���������͵����ͱ���
	typedef PtrtoList Position;//��������λ�õ�ָ������ͱ���
	//���캯��(�йظ��ƵĻ������Ժ�ʵ��)
	List() :header(new Node<elementtype>(0)) {}
	List(const List&) = delete;
	List(List&&) = delete;
	//��ֵ�����
	List &operator=(const List&) = delete;
	List &operator=(List&&) = delete;
	//��������
	~List() { delete_after_all(header); delete header; }
	//�ӿ� ���ݷ���
	elementtype &getdata(unsigned i) //���ص�ǰ����ڵ������������
	{
		Position p = index(i);
		if (p != nullptr)
		{
			return p->pdata;
		}
		else
		{
			throw std::runtime_error("�ڵ���Ч! ");
		}
	}
	elementtype &getdata(Position p) //���ص�ǰ����ڵ������������
	{
		if (p != nullptr)
		{
			return p->pdata;
		}
		else
		{
			throw std::runtime_error("�ڵ���Ч! ");
		}
	}
	template<typename X> void push_back(X e)
	{ 
		Position ek = getlast();
		if (ek != nullptr)
		{
			add_element_after(e, ek);
		}
	
	}//�����ݼ��뵽����ĩβ
	template<typename X> Position insert_after(X e, Position pos) { return add_element_after(e, pos); }//��e��ӵ�pos�ĺ��� ������Ӻ��Ԫ�ؽڵ��ַ
	Position erase_after(Position pos) { return delete_after(pos); }//ɾ��pos֮���һ��Ԫ�� ����ɾ��Ԫ��֮��Ľڵ��ַ
	//Position erase_range(Position pos, Position end) { return delete_range(pos, end); }//ɾ��[pos,end)������Ԫ�� ����end
	void clear() { delete_after_all(header); }//ɾ������Ԫ�� ���ǲ�ɾ����ͷ
	//�ӿ� ��Ϣ
	Position head() { return header; }//���ر�ͷ�ڵ��ַ
	Position begin() { return header->next; }//�����������Ԫ�صĵ�ַ
	Position back() { return getlast(); }//�������һ��Ԫ�صĵ��ӵ�ַ
	unsigned int size() { return getsize(); }//���ص�ǰ����Ĵ�С ��������ͷ
	Position find(elementtype t) { return find_matched(t); }//���ص�һ������ָ��Ԫ�صĽڵ��ַ
	bool empty() { return header->next == nullptr; }
	//�ӿ� �����
	elementtype &operator[](unsigned int i) 
	{
		return getdata(i);
	}//ͨ��������������
private:
	Position header = nullptr;//��ͷԪ��
	//���Ԫ��
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
				//β��Ԫ�ز���ɾ��
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
	//���ҵ�һ��ƥ���Ԫ��
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
				throw std::runtime_error("������ɾ����ͷԪ��. ");
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
	typedef CONTAINER eletype;//��ʾ����Ԫ������
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
			throw std::runtime_error("����! ����һ�������ڵ�λ��");
		}
	}
private:
	Node<eletype> *pos;
};