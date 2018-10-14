
//#include "BinaryTree.h"
#include "stdafx.h"
template<typename T>//线索二叉搜索树的节点的定义
class ThreadBinaryTreeNode //其实可以使用继承关系
{
	typedef T DataType;
	typedef ThreadBinaryTreeNode<DataType> NodeType;
	typedef NodeType *Node;
public:
	ThreadBinaryTreeNode() :leftchild(nullptr), rightchild(nullptr) {}
	ThreadBinaryTreeNode(DataType da, Node l = nullptr, Node r = nullptr) :leftchild(l), rightchild(r), Data(da),leftTag(false),rightTag(false) {}
	//获取
	DataType Data;
	//设置左儿子
	void setLeftchild(Node l) { leftchild = l; }
	//设置右儿子
	void setRightchild(Node r) { rightchild = r; }
	//获取左儿子
	Node getLeftchild() { return leftchild; }
	//获取右儿子
	Node getRightchild() { return rightchild; }
	//析构函数 Node由管理类释放
	~ThreadBinaryTreeNode() {}
	//设置儿子的标志 false为指向左儿子 true为指向线索 
	void setLeftTag(bool b) { leftTag=b; }
	void setRightTag(bool b) { rightTag = b; }
	//返回左右儿子的状态
	bool getLeftTag() { return leftTag; }
	bool getRightTag() { return rightTag; }
private:
	Node leftchild;
	Node rightchild;
	bool leftTag;
	bool rightTag;
	
};
//线索化的二叉搜索树
template<typename T> class ThreadBinaryTreeSearchList
{
	typedef T DataType;
	typedef ThreadBinaryTreeNode<T> NodeType;
	typedef NodeType *Node;
public:
	~ThreadBinaryTreeSearchList()
	{
		root=do_clear(root);
	}
	ThreadBinaryTreeSearchList(DataType da):root(new NodeType(da)){}
	//操作
	Node getRoot() { return root; }
	Node findMin(Node rt)
	{
		if (rt)
		{
			if (rt->getLeftchild())
				findMin(rt->getLeftchild());
			else return rt;
		}
	}
	Node insert(Node rt,DataType da)
	{
		if (rt == nullptr)
		{
			rt = new NodeType(da);
		}
		else
		{
			if (rt->Data < da)
			{
				rt->setRightchild(insert(rt->getRightchild(), da));
			}
			else
			{
				if (rt->Data > da)
				{
					rt->setLeftchild(insert(rt->getLeftchild(), da));
				}
				//相同的不考虑
			}
		}
		return rt;
	}
	Node erase(Node rt,DataType da)
	{
		if (rt)
		{
			if (da < rt->Data)
			{
				rt->setLeftchild(erase(rt->getLeftchild(), da));
			}
			else
			{
				if (da > rt->Data)
				{
					rt->setRightchild(erase(rt->getRightchild(), da));
				}
				else
				{
					//找到了这个顶点
					if (rt->getLeftchild() && rt->getRightchild())
					{
						//两个孩子
						Node min = findMin(rt->getRightchild());
						rt->Data = min->Data;
						rt->setRightchild(erase(rt->getRightchild(), min->Data));
					}
					//存在一个或多个儿子 如果是左儿子:删除本节点 返回左儿子
					//有儿子的话 返回右儿子
					Node ret = nullptr;
					if (rt->getLeftchild())
						rt = rt->getLeftchild();
					else if (rt->getRightchild())
						rt = rt->getRightchild();
					delete ret;
				}
			}
		}
		return rt;
	}
	void clear(Node rt) { rt = do_clear(rt); }
	/*线索化遍历结构*/
	void Threading_InOrder()
	{
		Node pre = nullptr;
		do_threading_InOrder(pre, root);//线索化二叉树
	}
	Node Threading_InOrder_FindFirst(Node f)
	{
		if (f)
		{
			while (f->getLeftTag() == false)
				f = f->getLeftchild();//中序遍历搜索最左的儿子
			return f;
		}
		return nullptr;
	}
	Node Threading_InOrder_Next(Node f)
	{
		if (f)
		{
			//如果下一个不是线索 那么需要返回他的左子树的最左的儿子 否则根据线索树的定义 有儿子保存后继 所以返回后继节点
			if (f->getRightTag() == false) return Threading_InOrder_FindFirst(f->getRightchild());
			else return f->getRightchild();
		}
		return nullptr;
	}
	void InOrder_Traverse_usingThread()
	{
		Node first;
		for (first = Threading_InOrder_FindFirst(root); first; first = Threading_InOrder_Next(first))
		{
			std::cout << first->Data << std::endl;
		}
		

	}
private:
	Node root;
	Node do_clear(Node beg)
	{
		if (beg)
		{
			if(!beg->getLeftTag())
				beg->setLeftchild(do_clear(beg->getLeftchild()));
			if(!beg->getRightTag())
				beg->setRightchild(do_clear(beg->getRightchild()));
			delete beg;
			beg = nullptr;
		}
		return beg;
	}
	//线索化
	//前驱线索化 注意pre一定要先初始化为nullptr5
	void do_threading_InOrder(Node &pre, Node beg)
	{
		if (beg)
		{
			do_threading_InOrder(pre, beg->getLeftchild());//先对左儿子进行线索化
			//线索化
			if (beg->getLeftchild() == nullptr)//如果不存在左儿子 那么线索化 让他指向前驱 但是最左的左儿子是没有前驱的
			{
				beg->setLeftchild(pre);//pre表示的是中序遍历的时候的前驱（也就是父节点） 确定前驱
				beg->setLeftTag(true);
			}
			if (pre && pre->getRightchild()==nullptr)//当到达最后一个左儿子时，pre被访问到但是此时的pre是nullptr所以pre最后还是被更新为最左儿子 然后进行中序遍历
			{
				pre->setRightTag(true);//确定后继
				pre->setRightchild(beg);
			}
			pre = beg;//更新前驱 因为右子树的中序遍历的前驱是已经访问过的
			do_threading_InOrder(pre,beg->getRightchild());
		}
	}
	
};