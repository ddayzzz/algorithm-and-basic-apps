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
	//获取左儿子
	Node getLeftchild()
	{
		return leftchild;
	}
	//获取右兄弟节点（头结点）
	Node getRightSlibing()
	{
		return rightslibing;
	}
	//设置做儿子节点
	void setLeftchild(Node n)
	{
		leftchild = n;
	}
	//设置右兄弟
	void setRightslibing(Node n)
	{
		rightslibing = n;
	}
	//析构函数由list管理
	~TreeNode() {}
	//是否是叶子节点
	bool isLeaf()
	{
		return leftchild == nullptr;
	}
	//获取下一个兄弟
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
	//操作
	//添加儿子 这会把新插入的儿子弄到左儿子位置或者是右儿子链中的最末端
	void insertChild(Node root, DataType da)
	{
		Node nd = new NodeType(da);
		if (nd)
		{
			Node p = root->getLeftchild();
			if (p == nullptr)
			{
				//没有左儿子
				root->setLeftchild(nd);
			}
			else
			{
				//需要遍历到最右端
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
	//得到第一个儿子
	Node getFirstchild(Node nd) { return nd->getLeftchild(); }
	//得到第一个右儿子
	Node getNextslibing(Node nd) { return nd->getRightSlibing(); }
	//删除节点
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
	//递归方式的前序遍历 根节点 左儿子 右儿子
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
	//递归方式的后序遍历 
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
//trie树
template<typename T = char> class TrieTreeNode
{
public:
	short wordcnt;
	string word;//表示这个单词的重复的个数 如果是0表示的就是没有内容
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
			//之所以平行的for是因为这个单词出现的地方可能也是一个非叶子节点
			for (int i = 0; i < 26; ++i)
			{
				if (nd->treeNode[i])
				{
					do_printAll(nd->treeNode[i]);//接着搜索
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
			if (location)//找到了这个单词
			{
				location->word.clear();//清空保存的单词 相当一次假的删除 考虑了在此添加的情况
				return true;
			}
			else
			{
				return false;
			}
		}
	}
public:
	//根节点是没有保存的数据的
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
				if (node->treeNode[char_code] == nullptr)//防止多余的分配内存的问题
					node->treeNode[char_code] = new NodeType;
				node = node->treeNode[char_code];//从这个节点开始
				chs++;
			}
			if (node)
			{
				node->word = n;//到达末尾了 表示已经可以插入单词的标记
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
		if ((location != nullptr && location->word !=n)/*是一个前缀 且这个前缀不构成单词*/ || location==nullptr/*单词的字母木有对应的地址*/)
		{
			//寻找的单词是某个前缀 但是查找是失败的
			return false;
		}
		//包含路径上是一个完整的单词 也可能是从根节点到非叶子节点组成的单词
		return true;
	}
	
	bool remove(const char *chs)
	{
		string n(chs);
		return do_deleteWord(root, n);
	}
	bool printPre(char *chs)
	{
		//打印前缀
		Node location = root;
		int code;
		while (location && *chs != '\0')
		{
			code = charToCharCode(*chs);
			if (code >= 0 && code <= 25)
			{
				location = location->treeNode[code];//移动
				++chs;
			}
			else
			{
				return false;
			}
		}
		if (location)
		{
			do_printAll(location);//输出以前缀开始的所有单词
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
//使用数组的树
