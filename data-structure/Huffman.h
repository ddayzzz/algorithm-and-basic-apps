#pragma once
#include "stdafx.h"
#include <algorithm>
#include <map>
#include <vector>
#include <utility>
#include <unordered_map>
#include <queue>
 class HuffmanTreeNodeBase
{
public:
	//构造函数必须提供频数或频数之和
	HuffmanTreeNodeBase(int f):flag(f){}
	//获取flag值 对于叶子节点派生类这个保存的是频数 对于节点保存的是两个flag的频数纸盒之和
	int getFlag() const { return flag; }
	//设置flag
	void setFlag(int w) { flag = w; }

	virtual ~HuffmanTreeNodeBase(){}
private:
	int flag;//表示这个节点的值
};

class HuffmanLeafTree :public HuffmanTreeNodeBase
{
public:
	//必须提供叶子节点频数和代表的字符
	HuffmanLeafTree(int f,char c):HuffmanTreeNodeBase(f), ch(c){}
	//获取叶子节点代表的字符
	char getChar() { return ch; }
	//设置叶子节点代表的字符
	void setChar(char c) { ch = c; }
	~HuffmanLeafTree(){}
private:
	char ch;//这个表示叶子节点的被编码的符号
};
class HuffmanTreeNode : public HuffmanTreeNodeBase
{
	typedef HuffmanTreeNodeBase *Node;
public:
	//提供频数和频数之和 左儿子节点指针 右儿子节点指针
	HuffmanTreeNode(int flag, Node l, Node r) :HuffmanTreeNodeBase(flag), left(l), right(r) {}
	~HuffmanTreeNode() { 
		delete left; //析构函数
	delete right; }
	//获取左儿子节点指针
	Node getLeftchild() { return left; }
	//获取右儿子节点指针
	Node getRightchild() { return right; }
private:
	Node left;
	Node right;
};
class Huffman
{
	
public:
	typedef std::map<char, int> Charfrenquent;//这个用来保存被编码的字符的出现的频数
	typedef std::vector<int> Encoding;//这个用来保存一组哈夫曼编码
	typedef std::map<char, Encoding> CharMap;//这个用来保存对应字符的编码表

	//构造函数
	Huffman(){}
	//这个用来整理map 频率最小的排在前面 现在已经不使用
	void sortMap(std::unordered_map<char, int> &ma)
	{
		std::vector<std::pair<char, int>> res;
		for (auto iter = ma.begin(); iter != ma.end(); ++iter)
			res.push_back(std::make_pair(iter->first, iter->second));
		std::sort(res.begin(), res.end(),
			[](const std::pair<char, int> &c1, std::pair<char, int> &c2) {return c1.second < c2.second; }
		);
		//重新排序
		ma.clear();
		for (auto i = res.cbegin(); i != res.cend(); ++i)
			ma[i->first] = i->second;
	}
	//这个函数用来计算字符出现的频率 第三个参数是输出的保存字符对应平频率的映射表
	void calcFrenquentofChars(const char *c,int size,Charfrenquent &cf)
	{
		if (c != nullptr && size > 0)
		{
			
			for (int i = 0; i < size; ++i)
			{
				cf[c[i]]++;
			}
			//sortMap(cf);
		}
	}
	//这个用来生成哈夫曼树 需要获取已知的频率映射表 生成的树依据最优二叉树的规则
	HuffmanTreeNodeBase *buildHuffmanTree(Charfrenquent &cf)
	{
		auto j = [](const HuffmanTreeNodeBase *c1, const HuffmanTreeNodeBase *c2) {return c1->getFlag() > c2->getFlag();/*如果返回的是true表示后面的频数比前面的小 那么就需要吧后面的和前面的交换顺序*/ };//这个用来设置优先队列最先出出对的佘顺序 依据的是频数 频数最小的先出来
		std::priority_queue < HuffmanTreeNodeBase*, std::vector<HuffmanTreeNodeBase*>, decltype(j)> trees(j);
		for (auto i = cf.begin(); i != cf.end(); ++i)
			trees.push(new HuffmanLeafTree(i->second, i->first));
		//优先队列
		while (trees.size() > 1)
		{
			//从优先队列出来是频数最小的字符
			HuffmanTreeNodeBase *le = trees.top();
			trees.pop();
			HuffmanTreeNodeBase *ri = trees.top();
			trees.pop();
			HuffmanTreeNode *nd=new HuffmanTreeNode(le->getFlag() + ri->getFlag(), le, ri);//新建的一个Node节点 由于是base的派生类 所以指针是可以插入的
			trees.push(nd);//把这个节点插入优先队列
		}
		return trees.top();
	}
	//这个用来生成哈夫曼编码 charmap输出的就是字符对应的编码 用vector保存 第三个参数用来验证是否只存在一个编码的情况
	void genrateCode(HuffmanTreeNodeBase *tree, CharMap &cm,Charfrenquent &fren)
	{
		Encoding enc;//这个是用于临时保存的vector
		if (fren.size() == 1)
		{
			enc.push_back(0);
		}
		else
		{
			if (fren.size() <= 0)
				return;
		}
		do_genrateCode(tree, enc, cm);
	}
	std::string deCoding(CharMap &cm, std::string &encodedstr)
	{
		std::string result;
		std::map<std::string, char> reverseMap;
		for (CharMap::const_iterator it = cm.cbegin(); it != cm.cend(); ++it)
		{
			std::string k;
			for (Encoding::const_iterator i = it->second.cbegin(); i != it->second.cend(); ++i)
				k.push_back(*i+'0');//将vector中的编码序列变成字符串的形式 注意int和char类型的互换
			reverseMap.insert(std::make_pair(k, it->first));//将键值对插入map
		}
		//反向映射表建立完成
		auto beg = encodedstr.cbegin();
		auto end = encodedstr.cend();
		auto range = ++encodedstr.cbegin();//这个表示范围的有开区间 我们将会从[Beg,range) 中构建查找的字符串 beg！=range 否则为空字符串
		int cnt = 0;//cnt计数用于吧beg递增到最近一次匹配位置的尾后
		while (beg != end)
		{
			char dest;
			bool changeres = match_str(reverseMap, beg, range, dest);//查找
			if (changeres == true)
			{
				result.push_back(dest);
				for (int i = 0; i <= cnt; ++i)
				{
					++beg;
				}
				if (range == end)//如果此时的匹配之后range的位置是尾后 那么表示这是最后一次成功的匹配 就结束while
					break;
				range = beg + 1;//range>beg
				cnt = 0;//cntc重新开始计数
			}
			else
			{
				++cnt;//如果匹配失败 那么一旦匹配成功那么bg会递增到beg+cnt+1的位置
				++range;//范围也要递增
			}
		}
		return result;
	}
	~Huffman() {}
private:
	void do_genrateCode(HuffmanTreeNodeBase *tree, Encoding &precode, CharMap &charmap)
	{
		if (tree == nullptr)
			return;
		
		HuffmanLeafTree *leaf = dynamic_cast<HuffmanLeafTree*>(tree);
		if (leaf)
		{
			//表示这个指针是叶子节点 那么就设置该字符的编码 编码保存在int的vector中
			charmap[leaf->getChar()] = precode;
		}
		else
		{
			HuffmanTreeNode *nd = dynamic_cast<HuffmanTreeNode*>(tree);
			if (nd)
			{
				//表示这是节点 所以还是必须把编码压入vector
				Encoding leftcode = precode;//这里定义一个新的vector他是用来防止不同的vector编码冲突的问题
				leftcode.push_back(0);//做儿子的话 路径上的权为0
				do_genrateCode(nd->getLeftchild(), leftcode, charmap);//从左儿子开始 递归
				Encoding rightcode = precode;//解释同上
				rightcode.push_back(1);
				do_genrateCode(nd->getRightchild(), rightcode, charmap);

			}
		}
	}
	//这个用来寻找哈夫曼序列对应的字符 第一个参数是映射表 [beg,end） 注意beg ！=end 表示要匹配的迭代器范围
	bool match_str(std::map<std::string, char> reverseMap,string::const_iterator beg_match, std::string::const_iterator end_match,char &res)
	{
		std::string s(beg_match, end_match);//构建一个临时的字符串
		auto r = reverseMap.find(s);//根据字符串查找对应的哈夫曼字符映射
		if (r == reverseMap.end())//如果没有找到的话 返回的是end迭代器
		{
			return false;
		}
		else
		{
			res = r->second;//找到了映射
			return true;
		}
	}
};