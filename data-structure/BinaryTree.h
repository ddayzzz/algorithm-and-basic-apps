#pragma once
#include <stack>
#include <queue>
template<typename T>
class BinaryTreeNode
{
	typedef T DataType;
	typedef BinaryTreeNode<DataType> NodeType;
	typedef NodeType *Node;
public:
	BinaryTreeNode():leftchild(nullptr),rightchild(nullptr){}
	BinaryTreeNode(DataType da,Node l=nullptr,Node r=nullptr):leftchild(l),rightchild(r),data(da){}
	//获取
	DataType &getData()
	{
		return data;
	}
	//设置左儿子
	void setLeftchild(Node l) { leftchild = l; }
	//设置右儿子
	void setRightchild(Node r) { rightchild = r; }
	//获取左儿子
	Node getLeftchild() { return leftchild; }
	//获取右儿子
	Node getRightchild() { return rightchild; }
	//析构函数 Node由管理类释放
	~BinaryTreeNode(){}
	//获取左儿子的状态 是否是线索（前驱）
	bool getLeftchildStatus()
	{
		return leftThread;
	}
	//获取右儿子的状态 是否是线索（后继）
	bool getRightchildStatus()
	{
		return rightThread;
	}
	//设置左儿子的状态 是否是线索（前驱）
	void setLeftchildStatus(bool status)
	{
		leftThread = status;
	}
	//设置右儿子的状态 是否是线索（后继）
	void setRightchildStatus(bool status)
	{
		rightThread = status;
	}
private:
	Node leftchild;
	Node rightchild;
	DataType data;
	//这是用来线索化的二叉树标志
	bool leftThread=false;
	bool rightThread=false;
};

template<typename T> class BinaryTreeList
{
public:
	//类型别名
	typedef T DataType;
	typedef BinaryTreeNode<DataType> NodeType;
	typedef NodeType *Node;
	//构造函数
	BinaryTreeList(DataType init) :root(new NodeType) { root->getData() = init; }
	
	//各种操作
	//访问
	//获取根节点
	Node &getRoot() { return root; }
	DataType &Retrieve(Node node) { return node->getData(); }
	//更改
	//插入右子节点
	void insert_right(Node parent,DataType da)
	{
		Node nd = new NodeType(da);
		nd->setRightchild(parent->getRightchild());
		parent->setRightchild(nd);
	}
	//插入左子节点
	void insert_left(Node parent,DataType da)
	{
		Node nd = new NodeType(da);
		nd->setLeftchild(parent->getLeftchild());
		parent->setLeftchild(nd);
	}
	//删除节点
	//注意要判断删除的是叶子还是非叶子	
	void erase_left(Node node)
	{
		destroy(node->getLeftchild());
		node->setLeftchild(nullptr);
	}
	void erase_right(Node node) { destroy(node->getRightchild()); node->setRightchild(nullptr); }
	//释放所有节点
	void clear()
	{
		destroy(root);
		root = nullptr;
	}
	~BinaryTreeList() { clear(); }
	//遍历
	//前序遍历
	void PreOrder(Node p)
	{
		if (p != nullptr)
		{
			cout << p->getData() << " ";
			PreOrder(p->getLeftchild());
			PreOrder(p->getRightchild());
		}
	}
	void PreOrder_Stack(Node p)
	{
		std::stack<NodeType*> sta;
		Node root = p;
		while (sta.empty() == false || root != nullptr)//只要栈不为空 那么就要
		{
			while (root)
			{
				sta.push(root);
				cout << root->getData() << " ";
				root = root->getLeftchild();
			}
			root = sta.top();//此时的top是深度最大的左叶子
			sta.pop();//把那个将要访问的pop
			root = root->getRightchild();//将要访问的叶子节点的父节点的值 左儿子已经处理过了 所以这个root要被更新为父节点的右儿子然后在对右儿子进行处理
		}
		cout << endl;
	}
	//中序遍历
	void InOrderTraverse(Node root)
	{
		if (root != nullptr)
		{
			InOrderTraverse(root->getLeftchild());
			cout << root->getData() << " ";
			InOrderTraverse(root->getRightchild());
		}
	}
	void InOrderTraverse_Stack(Node root)
	{
		stack<Node> nodes;
		Node p = root;
		while (!nodes.empty() || p != nullptr)
		{
			while (p)
			{
				nodes.push(p);
				p = p->getLeftchild();
			}
			if (nodes.empty() == false)
			{
				p = nodes.top();
				cout << p->getData() << " ";
				nodes.pop();
				p = p->getRightchild();
			}
		}
		cout << endl;
	}
	//后续遍历
	void PostOrderTraverse(Node p)
	{
		if (p != nullptr)
		{
			PostOrderTraverse(p->getLeftchild());
			PostOrderTraverse(p->getRightchild());
			std::cout << p->getData() << " ";
		}
	}
	void PostOrderTraverse_Stack(Node root)
	{
		stack<Node> sta;
		Node p = root;
		Node prev = nullptr;
		while (!sta.empty() || p != nullptr)
		{
			while (p)
			{
				sta.push(p);
				p = p->getLeftchild();
			}
			p = sta.top();
			//分析当前的栈顶元素 此时是没有左儿子的
			if (p->getRightchild() ==nullptr /*叶子节点直接访问*/|| p->getRightchild() ==prev/*如果左儿子为null 而且右儿子先前被访问过（说明要访问该节点（LR的父亲））*/)
			{
				cout << p->getData() << " ";
				prev = p;
				sta.pop();//将这个节点从栈中pop
				p = nullptr;//将p设置为nullptr是为了不要又开始搜索左儿子 应该访问栈顶了
			}
			else
			{
				//sta.pop();
				p = p->getRightchild();//不满足条件 那么应该继续搜索右儿子
			}
		}
		cout << endl;
	}
	//层次遍历
	void LevelOrderTraverse(Node root)
	{
		queue<Node> que;
		Node p = root;
		if (p != nullptr)
		{
			que.push(p);//首元素入队
			while (!que.empty()) //只要队列不为空的话 
			{
				p = que.front();//获取对头元素 
				cout << p->getData() << " ";
				que.pop();//出对 将对头元素转移到与之同级的右节点上 然后该节点的左右子树分别入队
				if (p->getLeftchild())
					que.push(p->getLeftchild());
				if (p->getRightchild())
					que.push(p->getRightchild());

			}
		}
		cout << endl;
	}
	//线索化操作
	//建立前序搜索关联
	void InOrderThread(Node root)
	{
		Node pre = nullptr;//这个指针总是保存之前访问的位置
		InOrderThread_Process(root, pre);
	}
	//中序线索遍历
	void Display_InOrderThread(Node root)
	{
		for (Node p = InOrder_FindFirst(root); p != nullptr; p = InOrder_NextNode(p))
			cout << p->getData() << " ";
		cout << endl;
	}
	// 前序搜索建立
	//建立前序搜索关联
	void PreOrderThread(Node root)
	{
		Node pre = nullptr;//这个指针总是保存之前访问的位置
		PreOrderThread_Process(root, pre);
	}
	//前序线索树显示
	void Display_PreOrderThread(Node root)
	{
		Node d = root;
		while (d != nullptr)
		{
			cout << d->getData() << " ";
			d = PreOrder_NextNode(d);
		}
		cout << endl;
	}
	//后续线索化
	void PostOrderThread(Node root)
	{
		Node pre = nullptr;
		PostOrderThread_Process(root, pre);
	}
	//显示线索化
	void Display_PostOrderThread(Node root)
	{
		Node p = PostOrderThread_FindFirstNode(root);
		while (p != nullptr)
		{
			cout << p->getData() << " ";
			p = PostOrderThread_NextNode(p);
		}
		cout << endl;
	}
	//清除指定根节点以及他的子树的线索信息
	void clearAllThreads(Node r)
	{
		if (r != nullptr)
		{
			clearAllThreads(r->getLeftchild());
			clearAllThreads(r->getRightchild());
			if (r->getLeftchildStatus() == true)
			{
				r->setLeftchildStatus(false);
				r->setLeftchild(nullptr);
			}
			if (r->getLeftchildStatus() == true)
			{
				r->setRightchild(nullptr);
				r->setRightchildStatus(false);
			}
		}

	}
private:
	Node root;//保存根节点
	void destroy(Node r)
	{
		if (r != nullptr)
		{
			if (r->getLeftchildStatus() == false)//如果不是修改后的指针域才会释放他们 避免二次释放
			{
				destroy(r->getLeftchild());
			}
			if (r->getRightchildStatus() == false)
			{
				destroy(r->getRightchild());
			}
			delete r;
		}
	}
	//中序线索化 私有函数
	void InOrderThread_Process(Node root, Node &pre)
	{
		if (root != nullptr)
		{
			InOrderThread_Process(root->getLeftchild(), pre);//遍历左子树
			if (root->getLeftchild() == nullptr)
			{
				//没有左孩子
				root->setLeftchildStatus(true);
				root->setLeftchild(pre);//将左孩子的指正改为前驱 指向树的前驱节点（也就是pre）
			}
			if (pre!=nullptr /*这个要判断*/ &&pre->getRightchild() == nullptr)
			{
				//前一个节点没有右孩子
				pre->setRightchildStatus(true);
				pre->setRightchild(root);
			}
			pre = root;//这个pre是一个引用 所以能够保证指向的是root!=nullptr的前一个节点
			InOrderThread_Process(root->getRightchild(), pre);//如果没有右儿子 那么会自动结束当前的递归 从而可以把root定位到原root的父节点 pre已经更新到root
		}
	}
	
	//寻找中序遍历的起点 最左的左儿子
	Node InOrder_FindFirst(Node o)
	{
		
		if (o != nullptr)
		{
			Node first = o;
			while (first->getLeftchildStatus() == false)
				first = first->getLeftchild();
			return first;
		}
		else
		{
			return nullptr;
		}
	}
	//寻找中序遍历后续的节点 可能是右儿子(因为是中序遍历)或者是指定的后继
	Node InOrder_NextNode(Node p) {
		if (p == nullptr)
		{
			return nullptr;
		}
		else
		{
			if (p->getRightchildStatus() == false) return InOrder_FindFirst(p->getRightchild());//右子树的第一个结点（右子树的最左的儿子）
			else return p->getRightchild();//或后继
		}
	}

	//寻找前序线索遍历的下一个节点
	Node PreOrder_NextNode(Node p) {
		if (p == nullptr)
		{
			return nullptr;
		}
		else
		{
			if (p->getLeftchildStatus() == false)//如果左儿子不是空的话 返回的下一个节点就是左儿子
			{
				return p->getLeftchild();
			}
			else
			{
				return p->getRightchild();//如果左儿子为空的话（此时节点指的是前驱）那么就返回他的右儿子
			}
		}
	}
	//前序线索便利构造
	void PreOrderThread_Process(Node root, Node &pre)
	{
		if (root != nullptr)
		{
			if (root->getLeftchild() == nullptr)
			{
				//没有左儿子 那这个左儿子域就用来保存前驱节点的指针
				root->setLeftchildStatus(true);
				root->setLeftchild(pre);
			}
			if (pre && pre->getRightchild() == nullptr)//前一个结点没有指针的位置 那么就让他指向下一个节点
			{
				pre->setRightchildStatus(true);
				pre->setRightchild(root);
			}
			pre = root;
			if (root->getLeftchildStatus() == false)//如果还有左儿子 那么也需要对左儿子建立线索
			{
				PreOrderThread_Process(root->getLeftchild(), pre);
			}
			if (root->getRightchildStatus() == false)//如果还有左右儿子 那么也需要对右儿子建立线索
			{
				PreOrderThread_Process(root->getRightchild(), pre);
			}
		}
	}
	
	//后续线索遍历
	void PostOrderThread_Process(Node root, Node &pre)
	{
		if (root != nullptr)
		{
			if (root->getLeftchildStatus() == false)
				PostOrderThread_Process(root->getLeftchild(), pre);
			if (root->getRightchildStatus() == false)
				PostOrderThread_Process(root->getRightchild(), pre);
			if (root->getLeftchild() == nullptr)
			{
				root->setLeftchild(pre);
				root->setLeftchildStatus(true);
			}
			if (pre !=nullptr && pre->getRightchildStatus() == false)
			{
				pre->setRightchild(root);
				pre->setRightchildStatus(true);
			}
			pre = root;
		}
	}
	Node PostOrderThread_FindFirstNode(Node nd)
	{
		if (nd != nullptr)
		{
			//用来寻找最深层的节点
			while (nd->getLeftchild())
				nd = nd->getLeftchild();
			return nd;
		}
		else
		{
			return nullptr;
		}
	}
	//后续线索的下一个节点
	Node PostOrderThread_NextNode(Node root)
	{
		if (root != nullptr)
		{
			if (root->getRightchildStatus() == false)
			{
				//存在右儿子
				if (root->getLeftchildStatus() == false)//如果存在左儿子的话 也就是到达了第一个有两个儿子的节点 那么我们认为他是不需要遍历的节点
				{
					return nullptr;
				}
				else
				{
					return PostOrderThread_FindFirstNode(root->getLeftchild());//存在右儿子 左儿子是前驱 那么我们就搜索他的子树 从最低的左儿子开始遍历
				}
			}
			else
			{
				return root->getRightchild();//右儿子是后继 直接返回右儿子
			}
		}
		else
		{
			return nullptr;
		}
	}
};