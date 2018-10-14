#pragma once
#include "stdafx.h"
#include <string>
template<typename T> class TreeNode
{
	typedef T DataType;
	typedef TreeNode<DataType> NodeType;
	typedef NodeType *Node;
public:
	TreeNode(DataType da) :leftchild(nullptr), rightslibing(nullptr), data(da) {}
	//��ȡ�����
	Node getLeftchild()
	{
		return leftchild;
	}
	//��ȡ���ֵܽڵ㣨ͷ��㣩
	Node getRightSlibing()
	{
		return rightslibing;
	}
	//���������ӽڵ�
	void setLeftchild(Node n)
	{
		leftchild = n;
	}
	//�������ֵ�
	void setRightslibing(Node n)
	{
		rightslibing = n;
	}
	//����������list����
	~TreeNode() {}
	//�Ƿ���Ҷ�ӽڵ�
	bool isLeaf()
	{
		return leftchild == nullptr;
	}
	//��ȡ��һ���ֵ�
	Node getNextSlibing()
	{
		if (rightslibing==nullptr)
		{
			return nullptr;
		}
		else
		{
			return rightslibing->rightslibing;
		}
	}
	DataType data;
private:
	Node leftchild;
	Node rightslibing;
	
};
template<typename T> class TreeList
{
	typedef T DataType;
	typedef TreeNode<DataType> NodeType;
	typedef NodeType *Node;
public:
	TreeList(DataType da):root(new NodeType(da)){}
	//����
	//��Ӷ��� �����²���Ķ���Ū�������λ�û������Ҷ������е���ĩ��
	void insertChild(Node root, DataType da)
	{
		Node nd = new NodeType(da);
		if (nd)
		{
			Node p = root->getLeftchild();
			if (p == nullptr)
			{
				//û�������
				root->setLeftchild(nd);
			}
			else
			{
				//��Ҫ���������Ҷ�
				while (p !=nullptr && p->getRightSlibing() != nullptr)
				{
					p = p->getRightSlibing();
				}
				if (p != nullptr)
				{
					p->setRightslibing(nd);
				}
			}
		}
	}
	//�õ���һ������
	Node getFirstchild(Node nd) { return nd->getLeftchild(); }
	//�õ���һ���Ҷ���
	Node getNextslibing(Node nd) { return nd->getRightSlibing(); }
	//ɾ���ڵ�
	void erase(Node nd,Node dest){}
	Node getRoot()
	{
		return root;
	}
	void clear()
	{
		root=destroy(root);
	}
	~TreeList() { root=destroy(root); }
	//�ݹ鷽ʽ��ǰ����� ���ڵ� ����� �Ҷ���
	void do_traverse_PreOrder_recursion(Node beginroot,int depth=1)
	{
		if (beginroot)
		{
			for (int i = 0; i < depth; ++i)
			{
				printf("-");
			}
			std::cout << beginroot->data << std::endl;
			for (Node left = beginroot->getLeftchild(); left; left = left->getRightSlibing())
				do_traverse_PreOrder_recursion(left, depth + 1);
		}
	}
	//�ݹ鷽ʽ�ĺ������ 
	void do_traverse_PostOrder_recursion(Node beginroot,int depth=1)
	{
		if (beginroot)
		{
			for (Node pnode = beginroot->getLeftchild(); pnode; pnode = pnode->getRightSlibing())
				do_traverse_PostOrder_recursion(pnode,depth + 1);
			std::cout << beginroot->data << std::endl;
		}
	}
private:
	Node root;
	Node destroy(Node nd)
	{
		if (nd != nullptr)
		{
			nd->setLeftchild(destroy(nd->getLeftchild()));
			nd->setRightslibing(destroy(nd->getRightSlibing()));
			delete nd;
			return nullptr;
		}
		else
		{
			return nullptr;
		}
	}
};
//trie��
template<typename T = char> class TrieTreeNode
{
public:
	short wordcnt;
	string word;//��ʾ������ʵ��ظ��ĸ��� �����0��ʾ�ľ���û������
	TrieTreeNode *treeNode[26];
	TrieTreeNode() {
		for (int i = 0; i < 26; ++i)
			treeNode[i] = nullptr;
	}
};
template<typename T = char> class TrieTree
{
	typedef TrieTreeNode<T> NodeType;
	typedef NodeType *Node;
private:
	Node root;
	Node do_clearAll(Node beg)
	{
		if (beg != nullptr)
		{
			int i = 0;
			for (; i < 26; ++i)
			{
				if (beg->treeNode[i])
					beg->treeNode[i] = do_clearAll(beg->treeNode[i]);
			}
			delete beg;
			return nullptr;
		}
		return beg;
	}
	int charToCharCode(char chs)
	{
		int charCode = -1;
		if (chs >= 'a' && chs <= 'z')
			charCode = chs - 'a';
		else if (chs >= 'A' && chs <= 'Z')
			charCode = chs - 'A';
		return charCode;
	}
	void do_printAll(Node nd)
	{
		if (nd)
		{
			if (nd->word.empty() == false)
			{
				cout << nd->word << endl;
			}
			//֮����ƽ�е�for����Ϊ������ʳ��ֵĵط�����Ҳ��һ����Ҷ�ӽڵ�
			for (int i = 0; i < 26; ++i)
			{
				if (nd->treeNode[i])
				{
					do_printAll(nd->treeNode[i]);//��������
				}
			}
		}
	}
	bool do_deleteWord(Node nd,string s)
	{
		if (nd)
		{
			Node location = nd;
			int k = 0;
			while (location && k <s.size())
			{
				int code = charToCharCode(s[k]);
				if (code >=0 && code < 26)
				{
					location = location->treeNode[code];
					++k;
				}
				else
				{
					return false;
				}
			}
			if (location)//�ҵ����������
			{
				location->word.clear();//��ձ���ĵ��� �൱һ�μٵ�ɾ�� �������ڴ���ӵ����
				return true;
			}
			else
			{
				return false;
			}
		}
	}
public:
	//���ڵ���û�б�������ݵ�
	TrieTree():root(new NodeType){}
	~TrieTree() { root=do_clearAll(root); }
	bool insert(const char *chs)
	{
		string n;
		int char_code;
		Node node = root;
		bool res = true;
		if (chs)
		{
			while (node !=nullptr && *chs !='\0')
			{
				char_code = charToCharCode(*chs);
				if (char_code < 0)
				{
					return false;
				}
				n.push_back(*chs);
				if (node->treeNode[char_code] == nullptr)//��ֹ����ķ����ڴ������
					node->treeNode[char_code] = new NodeType;
				node = node->treeNode[char_code];//������ڵ㿪ʼ
				chs++;
			}
			if (node)
			{
				node->word = n;//����ĩβ�� ��ʾ�Ѿ����Բ��뵥�ʵı��
			}
			return res;
		}
		return false;
	}
	bool search(const char *chs)
	{
		int char_code;
		string n;
		Node location = root;
		int charCode;
		if (location == nullptr)
			return false;
		while (location != nullptr && *chs != '\0')
		{
			char_code = charToCharCode(*chs);
			if (char_code < 0)
			{
				return false;
			}
			n.push_back(*chs);
			location = location->treeNode[charCode];
			++chs;
		}
		if ((location != nullptr && location->word !=n)/*��һ��ǰ׺ �����ǰ׺�����ɵ���*/ || location==nullptr/*���ʵ���ĸľ�ж�Ӧ�ĵ�ַ*/)
		{
			//Ѱ�ҵĵ�����ĳ��ǰ׺ ���ǲ�����ʧ�ܵ�
			return false;
		}
		//����·������һ�������ĵ��� Ҳ�����ǴӸ��ڵ㵽��Ҷ�ӽڵ���ɵĵ���
		return true;
	}
	
	bool remove(const char *chs)
	{
		string n(chs);
		return do_deleteWord(root, n);
	}
	bool printPre(char *chs)
	{
		//��ӡǰ׺
		Node location = root;
		int code;
		while (location && *chs != '\0')
		{
			code = charToCharCode(*chs);
			if (code >= 0 && code <= 25)
			{
				location = location->treeNode[code];//�ƶ�
				++chs;
			}
			else
			{
				return false;
			}
		}
		if (location)
		{
			do_printAll(location);//�����ǰ׺��ʼ�����е���
		}
		return false;
	}
	void printAll()
	{
		do_printAll(root);
	}
	void deleteAll()
	{
		root = do_clearAll(root);
	}
};
//ʹ���������
