
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


template<typename T> class BinarySearchTreeNode
{
private:
	BinarySearchTreeNode *left;
	BinarySearchTreeNode *right;
	T data;
public:
	BinarySearchTreeNode(T da, BinarySearchTreeNode *l = nullptr, BinarySearchTreeNode *r = nullptr) :data(da), left(l), right(r) {}
	BinarySearchTreeNode():left(nullptr),right(nullptr){}
	~BinarySearchTreeNode() {}
	BinarySearchTreeNode *getRight() { return right; }
	BinarySearchTreeNode *getLeft() { return left; }
	void setData(T da) { data = da; }
	T &getData() { return data; }
	void setLeft(BinarySearchTreeNode *l) { left = l; }
	void setRight(BinarySearchTreeNode *r) { right = r; }
};
template<typename T> class BinarySearchTree
{
	typedef T DataType;
	typedef BinarySearchTreeNode<DataType> NodeType;
	typedef NodeType *Node;
private:
	Node root=nullptr;
	void do_clear(Node beg)
	{
		if (beg != nullptr)
		{
			do_clear(beg->getLeft());
			do_clear(beg->getRight());
			delete beg;
		}
	}
public:
	BinarySearchTree(DataType dat):root(new NodeType(dat)){}
	//获取节点
	Node getRoot() { return root; }
	//寻找最值
	Node findMin(Node beg)
	{
		if (beg != nullptr)
		{
			if (beg->getLeft() != nullptr)
			{
				return findMin(beg->getLeft());
			}
			else
			{
				return beg;
			}
		}
		else
		{
			return nullptr;
		}
	}
	Node findMax(Node  beg)
	{
		if (beg != nullptr)
		{
			if (beg->getRight() != nullptr)
			{
				return findMax(beg->getRight());
			}
			else
			{
				return beg;
			}
		}
		else
		{
			return nullptr;
		}
	}
	Node findData(Node beg, DataType dat)
	{
		if (beg != nullptr)
		{
			if (dat > beg->getData())
				return findData(beg->getRight());
			else if (dat < beg->getData())
				return findData(beg->getRight());
			return beg;
		}
		else
		{
			return nullptr;
		}
	}
	//插入
	 Node insert(Node beg, DataType dat)
	{
		if (beg == nullptr)
		{
			beg = new NodeType(dat);
		}
		if (dat < beg->getData())
			beg->setLeft(insert(beg->getLeft(),dat));
		else if (dat > beg->getData())
			beg->setRight(insert(beg->getRight(),dat));
		return beg;//返回被插入的节点地址给他的父亲或者是返回路径上的节点给他的父亲 这个非常关键
	}
	Node remove(Node beg, DataType dat)
	{
		if (beg != nullptr)
		{
			if (dat < beg->getData())
			{
				beg->setLeft(remove(beg->getLeft(), dat));
			}
			else
			{
				if (dat > beg->getData())
				{
					beg->setRight(remove(beg->getRight(), dat));
				}
				else
				{
					//find it;
					Node tmp;
					if (beg->getLeft() && beg->getRight())
					{
						//has two children
						tmp = findMin(beg->getRight());
						beg->setData(tmp->getData());
						beg->setRight(remove(beg->getRight(),beg->getData()));
					}
					else
					{
						tmp = beg;
						if (beg->getLeft() == nullptr)
							beg = beg->getRight();//如果这个顶点只有一个儿子 那么就返回他的另一个儿子做这个父亲对应的孩子
						else if (beg->getRight() == nullptr)
							beg = beg->getLeft();//如果都不存在的话返回的就是他的右儿子当然也是nullptr给父节点 所以父节点对应的儿子就是nullptr
						delete tmp;
					}
				}
			}
		}

		return beg;
	}
	void clear() { do_clear(root); root = nullptr; }
	 ~BinarySearchTree() { do_clear(root); root = nullptr; }
};
//AVL树 节点
template<typename T> class AVLTreeNode
{
	typedef AVLTreeNode<T> AVLNodeType;
	typedef AVLNodeType *AVLNode;
private:
	//平衡因子 对于AVL只有1 0 -1两种情况 右儿子高度 - 做儿子高度代表因子
	int height;//节点的高度
	AVLNode left = nullptr;
	AVLNode right = nullptr;
	T data;
public:
	AVLTreeNode(T dat, int hg = 0, AVLNode l = nullptr, AVLNode r = nullptr):data(dat),left(l),right(l),height(hg){}
	AVLNode getRight() { return right; }
	AVLNode getLeft() { return left; }
	void setData(T da) { data = da; }
	T &getData() { return data; }
	void setLeft(AVLNode l) { left = l; }
	void setRight(AVLNode r) { right = r; }

	int getHeight() { return height; }
	void setHeight(int hg) { height = hg; }
};
//AVL树定义
template<typename T> class AVLTree
{
private:
	
	typedef AVLTreeNode<T> AVLNodeType;
	typedef AVLNodeType *AVLNode;
	AVLNode root;
	int getHeight(AVLNode nd)
	{
		if (nd != nullptr)
		{
			//int lt = getHeightSum(nd->getLeft());
			//int rl = getHeightSum(nd->getRight());
			//return std::max<int>(lt, rl);
			return nd->getHeight();
		}
		else
		{
			return -1;//空树规定改为-1
		}
	}
	void do_clear(AVLNode beg)
	{
		if (beg != nullptr)
		{
			do_clear(beg->getLeft());
			do_clear(beg->getRight());
			delete beg;
		}
	}
	AVLNode singalRotate_R(AVLNode k1)
	{
		if (k1 != nullptr)
		{
			AVLNode pos;
			pos = k1->getLeft();
			k1->setLeft(pos->getRight());
			pos->setRight(k1);
			k1->setHeight(std::max<int>(
				getHeight(k1->getLeft()), getHeight(k1->getRight()) + 1
				));
			pos->setHeight(max<int>(
				k1->getHeight(), getHeight(pos->getLeft()) + 1
				));
			return pos;
		}
	}
	//从右往左
	AVLNode singalRotate_L(AVLNode k1)
	{
		if (k1 != nullptr)
		{
			//k1为不平衡的节点 pos即将成为父节点 pos为k1的右儿子 所以k1成为pos的左儿子 而原pos的左儿子成为k1的右儿子
			AVLNode pos;
			pos = k1->getRight();
			k1->setRight(pos->getLeft());
			pos->setLeft(k1);
			k1->setHeight(max<int>(
				getHeight(k1->getLeft()), getHeight(k1->getRight())
				) + 1);
			pos->setHeight(max<int>(getHeight(pos->getRight()),
				k1->getHeight()) + 1);
			return pos;
		}
	}
	//双旋转从L向R 
	AVLNode doubleRotate_LR(AVLNode k1)
	{
		k1->setLeft(singalRotate_L(k1->getLeft()));
		return singalRotate_R(k1);
	}
	AVLNode doubleRotate_RL(AVLNode k1)
	{
		k1->setRight(singalRotate_R(k1->getRight()));
		return singalRotate_L(k1);
	}
	AVLNode do_insert(AVLNode beg, T dat)
	{
		if (beg == nullptr)
		{
			beg = new AVLNodeType(dat);
		}
		else
		{

			if (dat < beg->getData())
			{
				beg->setLeft(do_insert(beg->getLeft(), dat));
				if (getHeight(beg->getRight()) - getHeight(beg->getLeft()) == -2)
				{
					if (dat < beg->getLeft()->getData())
						beg = singalRotate_R(beg);
					else
						beg = doubleRotate_LR(beg);
				}
			}
			else
			{
				if (dat > beg->getData())
				{
					beg->setRight(do_insert(beg->getRight(), dat));
					if (getHeight(beg->getRight()) - getHeight(beg->getLeft()) == 2)
					{
						if (dat > beg->getRight()->getData())//如果这个要插入的节点在一条线上那么向左转
							beg = singalRotate_L(beg);
						else
							beg = doubleRotate_RL(beg);//否则是一个之字形的那么需要先向右转 成一条直线
					}
				}
			}
		}
		beg->setHeight(max<int>(getHeight(beg->getLeft()), getHeight(beg->getRight())) + 1);
		return beg;
	}
	AVLNode do_remove(AVLNode beg, T dat)
	{
		if (beg != nullptr)
		{
			if (dat < beg->getData())
			{
				beg->setLeft(do_remove(beg->getLeft(), dat));
			}
			else
			{
				if (dat > beg->getData())
				{
					beg->setRight(do_remove(beg->getRight(), dat));
				}
				else
				{
					//find it;
					AVLNode tmp;
					if (beg->getLeft() && beg->getRight())
					{
						//has two children
						tmp = findMin(beg->getRight());
						beg->setData(tmp->getData());
						beg->setRight(do_remove(beg->getRight(), beg->getData()));
					}
					else
					{
						tmp = beg;
						if (beg->getLeft() == nullptr)
							beg = beg->getRight();//如果这个顶点只有一个儿子 那么就返回他的另一个儿子做这个父亲对应的孩子
						else if (beg->getRight() == nullptr)
							beg = beg->getLeft();//如果都不存在的话返回的就是他的右儿子当然也是nullptr给父节点 所以父节点对应的儿子就是nullptr
						delete tmp;
					}
				}
			}
		}

		return beg;
	}
public:
	AVLTree(T dat):root(new AVLNodeType(dat)){}
	//注意任何的操作都会重新更改root的值
	AVLNode getRoot() { return root; }
	//寻找最值
	AVLNode findMin(AVLNode beg)
	{
		if (beg != nullptr)
		{
			if (beg->getLeft() != nullptr)
			{
				return findMin(beg->getLeft());
			}
			else
			{
				return beg;
			}
		}
		else
		{
			return nullptr;
		}
	}
	AVLNode findMax(AVLNode  beg)
	{
		if (beg != nullptr)
		{
			if (beg->getRight() != nullptr)
			{
				return findMax(beg->getRight());
			}
			else
			{
				return beg;
			}
		}
		else
		{
			return nullptr;
		}
	}
	//返回拥有指定的值得地址
	AVLNode findData(AVLNode beg, T dat)
	{
		if (beg != nullptr)
		{
			if (dat > beg->getData())
				return findData(beg->getRight());
			else if (dat < beg->getData())
				return findData(beg->getRight());
			return beg;
		}
		else
		{
			return nullptr;
		}
	}

	
	//之所以不重载继承来的函数而是隐藏掉继承的接口是因为无法覆盖
	void insert(T dat)
	{
		root=do_insert(root, dat);//一定要更改root值 这个超级坑爹
	}
	void remove(T dat)
	{
		do_remove(root, dat);
	}
	void clear() { do_clear(root); root = nullptr; }
	 ~AVLTree() { do_clear(root); root = nullptr; }
	 void InOrderTraverse(AVLNode beg)
	 {
		 if (beg != nullptr)
		 {
			 InOrderTraverse(beg->getLeft());
			 cout << beg->getData() << " ";
			 InOrderTraverse(beg->getRight());
			 
		 }
	 }
};
//红黑树节点定义
//删除记住的结构红色点 向下移动的条件 1.左儿子 以及左儿子的左儿子 2.左儿子以及左儿子的右儿子
enum RBCOLOR { RED = 1, BLACK = 0 };
template<typename T> class RBTreeNode
{
	typedef RBTreeNode<T> RBNodeType;
	typedef RBNodeType *RBNode;
private:
	RBNode left = nullptr;
	RBNode right = nullptr;
	T data;
	RBCOLOR color;//颜
public:
	
	RBTreeNode(T dat,RBCOLOR colo=RED, RBNode l = nullptr, RBNode r = nullptr) :color(colo),data(dat), left(l), right(l) {}
	RBNode getRight() { return right; }
	RBNode getLeft() { return left; }
	void setData(T da) { data = da; }
	T &getData() { return data; }
	void setLeft(RBNode l) { left = l; }
	void setRight(RBNode r) { right = r; }
	void setColor(RBCOLOR clo) { color = clo; }
	RBCOLOR getColor() { return color; }
	void colorFlip()
	{
		if (color == RBCOLOR::BLACK)
			color = RBCOLOR::RED;
		else
			color = RBCOLOR::BLACK;
	}
	virtual ~RBTreeNode(){}
};
template<typename T> class RBTree
{
	typedef RBTreeNode<T> RBNodeType;
	typedef RBNodeType *RBNode;
private:
	RBNode root;
	void colorFlip(RBNode node)
	{
		if (node)
		{
			node->colorFlip();
			if (node->getLeft() != nullptr)
				node->getLeft()->colorFlip();
			if (node->getRight() != nullptr)
				node->getRight()->colorFlip();
		}
	}
	bool isRed(RBNode node)
	{
		if (node)
		{
			return node->getColor() == RBCOLOR::RED;
		}
		return false;
	}
	RBNode singalRotate_L(RBNode key)
	{
		if (key != nullptr)
		{
			RBNode rb;
			rb = key->getRight();
			key->setRight(rb->getLeft());
			rb->setLeft(key);
			rb->setColor(rb->getLeft()->getColor());//改为原父节点的颜色
			rb->getLeft()->setColor(RBCOLOR::RED);

			return rb;
		}
		return nullptr;
	}
	RBNode singalRotate_R(RBNode key)
	{
		if (key != nullptr)
		{
			RBNode rb;
			rb = key->getLeft();
			key->setLeft(rb->getRight());
			rb->setRight(key);
			rb->setColor(rb->getRight()->getColor());//改为原父节点颜色
			rb->getRight()->setColor(RBCOLOR::RED);//原父节点一定是红色
			return rb;
		}
		return nullptr;
	}
	RBNode do_insert(RBNode node, T x)
	{
		if (node == nullptr)
		{
			node = new RBNodeType(x);
		}
		else
		{
			if (isRed(node->getLeft()) && isRed(node->getRight())) //这是类似于234树的4-node 所以要拆开 通过颜色反转
				colorFlip(node);/*红黑树不允许连续两个红边 如果是这样的话 就需要颜色反转 也就是节点的的左儿子和孙左子变成黑色 父亲是红色的边*/

			if (x < node->getData()) {
				node->setLeft(do_insert(node->getLeft(), x));

			}
			else if (x > node->getData()) {
				node->setRight(do_insert(node->getRight(), x));
			}
			//we find the same value in the rbtree
			if (isRed(node->getRight()))
				node = singalRotate_L(node);/*右儿子是红色 现在的父亲节点是红色对的 如果右儿子是红色的话 就不符合定义了 解决办法是右儿子、父节点L旋转 此时新的父节点的颜色是原父节点的颜色（因为原父节点是红的他的左右儿子是黑的，但是由于插入了新节点，这种关系被破坏）原父节点改为红色 也就是这个子节点的颜色*/
			if (isRed(node->getLeft()) && isRed(node->getLeft()->getLeft()))
				node = singalRotate_R(node);/*左儿子 左孙子 父节点是红色的 需要向右转 中间节点成为父亲颜色为原父节点的颜色红色 新的父节点也是红色 也就是说颜色都没变 所以需要在下面的判断中颜色反转
											*/
			if (isRed(node->getLeft()) && isRed(node->getRight()))/*红黑树 不能同时存在两个红色的儿子和红色的父节点 如果是这样的话 就需要颜色反转 也就是节点的的左儿子和孙左子变成黑色 父亲是红色的边*/
				colorFlip(node);
		}
		return node;
	}
	void do_clear(RBNode node)
	{
		if (node)
		{
			do_clear(node->getLeft());
			do_clear(node->getRight());
			delete node;
		}
	}
	RBNode moveRedRight(RBNode node)
	{
		//这个函数从上到下 处理节点进行左旋转的时候出现的红红的问题
		colorFlip(node);//首先反色 此处理后的节点的左儿子 右儿子为红色
		if (node && node->getLeft() && isRed(node->getLeft()->getLeft()))//但是如果节点的左儿子的也是一个红色的节点 那么我反色之后就会出现现红红的问题
		{
			node = singalRotate_R(node);//解决的策略就是右旋转注意处理后的父节点与儿子门还是红色的 所以需要向上反色
			colorFlip(node);
		}
		return node;
	}
	RBNode moveRedLeft(RBNode node)
	{
		//这个是解决寻找最小值的辅助函数
		colorFlip(node);//颜色向下反转
		if (node && isRed(node->getRight()->getLeft())) //如果父节点的右儿子的左儿子是红色的 那么父节点的右儿子就出现红红问题
		{
			node->setRight(singalRotate_R(node->getRight()));//那么我需要右儿子右转申直 然后再次左转 但是父节点的儿子们还是红色的 所以需要向左转
			node = singalRotate_L(node);
			colorFlip(node);//向上反色处理
		}
		return node;
	}
	RBNode fixUp(RBNode h)
	{
		//这个是向上的节点修复对的函数
		if (h)
		{
			if (isRed(h->getRight()))
				h = singalRotate_L(h);//修复向右的树 我们默认的是LLRB红黑树
			if (isRed(h->getLeft()) && isRed(h->getLeft()->getLeft()))
				h = singalRotate_R(h);//左儿子和左孙子是红色的 所以右旋 下面的条件会实现反色
			if (isRed(h->getLeft()) && isRed(h->getRight()))
				colorFlip(h);//反色 因为父节点 左儿子 做左孙子可能都是红色 所以反色的话就是可以避免红红问题 建立4-node
			return h;
		}
		return nullptr;
	}
	RBNode do_deleteMax(RBNode node)
	{
		if (isRed(node->getLeft()))
			node = singalRotate_R(node);//如果节点的左儿子是红色的 那么需要赚到右边去 我认为  ？？？删除右侧的一个左儿子 那个左儿子必定是黑色的 如果是你删除他那么就不会满足红黑树的节点到他的叶子节点的黑色儿子数量相等
		if (node->getRight() == nullptr)
		{
			//到达最大的节点 那么删除他 返回一个null给待更新的父节点的右儿子
			delete node;
			return nullptr;
		}
		if (!isRed(node->getRight()) && !isRed(node->getRight()->getLeft())) //如果右儿子 右儿子的左儿子全是黑色（这是一个3-node）如果不旋转的话 那么删除他的右儿子的就会减少一个黑的高度P56
			node = moveRedRight(node);//移动函数
		node->setRight(do_deleteMax(node->getRight())); //还没有到达最大节点 继续循环
		return fixUp(node);//DOWN-UP修复 主要是修复偏右的节点 4-node
	}
	RBNode do_deleteMin(RBNode node)
	{
		if (node->getLeft() == nullptr)
		{
			delete node;//删除他
			return nullptr;
		}
		if (!isRed(node->getLeft()) && !isRed(node->getLeft()->getLeft()))
			node = moveRedLeft(node); //左儿子 左孙子全是黑色的 也就是一个需要借一个节点
		node->setLeft(do_deleteMin(node->getLeft()));//向左删除
		return fixUp(node);//修复节点
	}
	RBNode do_delete(RBNode node, T dat)
	{
		//删除任意的节点的函数
		if (dat < node->getData())
		{
			//如果要删除的值 < 当前节点的值
			if (!isRed(node->getLeft()) && !isRed(node->getLeft()->getLeft()))
				node = moveRedLeft(node);//需要借一个节点 左孩子 左孙子全是黑色的 删除一个必然导致不会满足红黑树的黑孩子数相同
			node->setLeft(do_delete(node->getLeft(), dat));//修改完成后递归从左儿子处删除

		}
		else
		{
			//此时是等于或者是大余的
			if (isRed(node->getLeft()))//左儿子是红色的 需要向右旋转
				node = singalRotate_R(node); //node 一定是红色的
			if (dat == node->getData() && node->getRight() == nullptr)//但这个指的是叶子
			{
				delete node;//找到了 删除
				return nullptr;
			}
			if (!isRed(node->getRight()) && !isRed(node->getRight()->getLeft()))
				node = moveRedRight(node); //这是寻找最大值的一个情况 需要向下移动红色边  此时的node一定是红色的节点
			if (dat == node->getData())
			{
				//如果相等 但是节点不是叶子
				node->setData(findMin(node->getRight())->getData()); //替换为右子树的最小值
				node->setRight(do_deleteMin(node->getRight()));//从右子树开始删除最小值
			}
			else
			{
				node->setRight(do_delete(node->getRight(), dat));//只有大于的情况了
			}
		}
		return fixUp(node);
	}
public:
	RBTree(T dat) :root(new RBNodeType(dat, RBCOLOR::BLACK)) {}
	void insert(T dat)
	{
		root = do_insert(root, dat);
		if (root)
			root->setColor(RBCOLOR::BLACK);
	}
	void clear()
	{
		do_clear(root);
		root = nullptr;
	}
	~RBTree()
	{
		clear();
	}
	void InOrderTraverse(RBNode nd)
	{
		if (nd != nullptr)
		{
			InOrderTraverse(nd->getLeft());
			cout << nd->getData() << " ";
			InOrderTraverse(nd->getRight());
		}
	}
	RBNode getRoot() { return root; }
	void removeMax()
	{

		if (root)
		{
			root = do_deleteMax(root);
			root->setColor(RBCOLOR::BLACK);
		}

	}
	void removeMin()
	{

		if (root)
		{
			root = do_deleteMin(root);
			root->setColor(RBCOLOR::BLACK);
		}

	}
	void remove(T dat)
	{

		if (root)
		{
			root = do_delete(root, dat);
			root->setColor(RBCOLOR::BLACK);
		}

	}
	RBNode findMin(RBNode beg)
	{
		if (beg != nullptr)
		{
			if (beg->getLeft() != nullptr)
			{
				return findMin(beg->getLeft());
			}
			else
			{
				return beg;
			}
		}
		else
		{
			return nullptr;
		}
	}
	RBNode findMax(RBNode  beg)
	{
		if (beg != nullptr)
		{
			if (beg->getRight() != nullptr)
			{
				return findMax(beg->getRight());
			}
			else
			{
				return beg;
			}
		}
		else
		{
			return nullptr;
		}
	}
	//返回拥有指定的值得地址
	RBNode findData(RBNode beg, T dat)
	{
		if (beg != nullptr)
		{
			if (dat > beg->getData())
				return findData(beg->getRight(),dat);
			else if (dat < beg->getData())
				return findData(beg->getLeft(),dat);
			return beg;
		}
		else
		{
			return nullptr;
		}
	}
};
//单链表的字典树 我觉得还是使用红黑树来实现吧
class Entry
{
private:
	string word;
	string chs;
public:
	Entry(string eng,string ch):word(eng),chs(ch){}
	Entry():word(string("")),chs(string("")){}
	string getEnglish() const { return word; }
	string getChinese() const { return chs; }
	friend bool operator<(const Entry &l, const Entry &r);//这些都是为了插入元素的需要
	friend bool operator>(const Entry &l, const Entry &r);
	friend bool operator==(const Entry &l, const Entry &r);
	
};
bool operator<(const Entry &l, const Entry &r)
{
	return l.getEnglish() < r.getEnglish();
}
bool operator>(const Entry &l, const Entry &r)
{
	return l.getEnglish() > r.getEnglish();
}
bool operator==(const Entry &l, const Entry &r)
{
	return l.getEnglish() == r.getEnglish();
}
class Dictionary
{
private:
	typedef RBTree<Entry> WordsType;
	WordsType words;
	void do_init_haschinese(const char *fn,bool haschs)
	{
		if (haschs == true)
		{
			std::ifstream ifs(fn);
			string ss;
			while (getline(ifs, ss))
			{
				std::stringstream sstr(ss);
				string e;
				sstr >> e;
				string tran;
				if (e.size() > 1 && !ss.empty() && ss.size() != e.size())
				{
					tran = ss.substr(e.size() + 1);
					Entry r(e, tran);
					words.insert(r);
				}
				else
				{
				}

			}
		}
		else
		{
			std::ifstream ifs(fn);
			string ss;
			while (getline(ifs, ss))
			{
				std::stringstream sstr(ss);
				string e;
				sstr >> e;
				if (e.size() >= 1)
				{
					//tran = ss.substr(e.size() + 1);
					Entry r(e, "");
					words.insert(r);
				}
				else
				{
				}

			}
		}
	}
public:
	Dictionary():words(Entry()/*构造一颗默认的树*/) {}
	Dictionary(const char *fn,bool haschinese=true):words(Entry())
	{
		do_init_haschinese(fn, haschinese);
	}
	void init(const char *fn,bool haschinese=true)
	{
		do_init_haschinese(fn, haschinese);
	}
	void insert(string eng, string chs)
	{
		words.insert(Entry(eng, chs));
	}
	void insert(const char* eng, const char *chs)
	{
		string en(eng);
		string ch(chs);
		insert(en, ch);
	}
	string findChinese(const char *eng)
	{
		auto ent = Entry(string(eng), string(""));//寻找的依据就是英文 我可以不管当前的中文
		auto j = words.findData(words.getRoot(), ent);
		if (j)
		{
			return j->getData().getChinese();
		}
		return string("");
	}
	Entry *findEntry(const char *eng)
	{
		auto ent = Entry(string(eng), string(""));//寻找的依据就是英文 我可以不管当前的中文
		auto j = words.findData(words.getRoot(), ent);
		if (j)
		{
			return &j->getData();
		}
		return nullptr;
	}
	Entry *findEntry(string eng)
	{
		auto ent = Entry(eng, string(""));//寻找的依据就是英文 我可以不管当前的中文
		auto j = words.findData(words.getRoot(), ent);
		if (j)
		{
			return &j->getData();
		}
		return nullptr;
	}
	string findChinese(string eng)
	{
		auto ent = Entry(eng, string(""));
		auto j = words.findData(words.getRoot(), ent);
		if (j)
		{
			return j->getData().getChinese();
		}
		return string("");
	}
	void insertToFile(string en, string ch, const char *fn)
	{
		std::ofstream ofs(fn, std::ofstream::app);
		ofs <<endl<< en << " " << ch;//附加到结尾
		ofs.close();//关闭文件流
	}
};

