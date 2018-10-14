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
	//���캯�������ṩƵ����Ƶ��֮��
	HuffmanTreeNodeBase(int f):flag(f){}
	//��ȡflagֵ ����Ҷ�ӽڵ�����������������Ƶ�� ���ڽڵ㱣���������flag��Ƶ��ֽ��֮��
	int getFlag() const { return flag; }
	//����flag
	void setFlag(int w) { flag = w; }

	virtual ~HuffmanTreeNodeBase(){}
private:
	int flag;//��ʾ����ڵ��ֵ
};

class HuffmanLeafTree :public HuffmanTreeNodeBase
{
public:
	//�����ṩҶ�ӽڵ�Ƶ���ʹ�����ַ�
	HuffmanLeafTree(int f,char c):HuffmanTreeNodeBase(f), ch(c){}
	//��ȡҶ�ӽڵ������ַ�
	char getChar() { return ch; }
	//����Ҷ�ӽڵ������ַ�
	void setChar(char c) { ch = c; }
	~HuffmanLeafTree(){}
private:
	char ch;//�����ʾҶ�ӽڵ�ı�����ķ���
};
class HuffmanTreeNode : public HuffmanTreeNodeBase
{
	typedef HuffmanTreeNodeBase *Node;
public:
	//�ṩƵ����Ƶ��֮�� ����ӽڵ�ָ�� �Ҷ��ӽڵ�ָ��
	HuffmanTreeNode(int flag, Node l, Node r) :HuffmanTreeNodeBase(flag), left(l), right(r) {}
	~HuffmanTreeNode() { 
		delete left; //��������
	delete right; }
	//��ȡ����ӽڵ�ָ��
	Node getLeftchild() { return left; }
	//��ȡ�Ҷ��ӽڵ�ָ��
	Node getRightchild() { return right; }
private:
	Node left;
	Node right;
};
class Huffman
{
	
public:
	typedef std::map<char, int> Charfrenquent;//����������汻������ַ��ĳ��ֵ�Ƶ��
	typedef std::vector<int> Encoding;//�����������һ�����������
	typedef std::map<char, Encoding> CharMap;//������������Ӧ�ַ��ı����

	//���캯��
	Huffman(){}
	//�����������map Ƶ����С������ǰ�� �����Ѿ���ʹ��
	void sortMap(std::unordered_map<char, int> &ma)
	{
		std::vector<std::pair<char, int>> res;
		for (auto iter = ma.begin(); iter != ma.end(); ++iter)
			res.push_back(std::make_pair(iter->first, iter->second));
		std::sort(res.begin(), res.end(),
			[](const std::pair<char, int> &c1, std::pair<char, int> &c2) {return c1.second < c2.second; }
		);
		//��������
		ma.clear();
		for (auto i = res.cbegin(); i != res.cend(); ++i)
			ma[i->first] = i->second;
	}
	//����������������ַ����ֵ�Ƶ�� ����������������ı����ַ���ӦƽƵ�ʵ�ӳ���
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
	//����������ɹ������� ��Ҫ��ȡ��֪��Ƶ��ӳ��� ���ɵ����������Ŷ������Ĺ���
	HuffmanTreeNodeBase *buildHuffmanTree(Charfrenquent &cf)
	{
		auto j = [](const HuffmanTreeNodeBase *c1, const HuffmanTreeNodeBase *c2) {return c1->getFlag() > c2->getFlag();/*������ص���true��ʾ�����Ƶ����ǰ���С ��ô����Ҫ�ɺ���ĺ�ǰ��Ľ���˳��*/ };//��������������ȶ������ȳ����Ե���˳�� ���ݵ���Ƶ�� Ƶ����С���ȳ���
		std::priority_queue < HuffmanTreeNodeBase*, std::vector<HuffmanTreeNodeBase*>, decltype(j)> trees(j);
		for (auto i = cf.begin(); i != cf.end(); ++i)
			trees.push(new HuffmanLeafTree(i->second, i->first));
		//���ȶ���
		while (trees.size() > 1)
		{
			//�����ȶ��г�����Ƶ����С���ַ�
			HuffmanTreeNodeBase *le = trees.top();
			trees.pop();
			HuffmanTreeNodeBase *ri = trees.top();
			trees.pop();
			HuffmanTreeNode *nd=new HuffmanTreeNode(le->getFlag() + ri->getFlag(), le, ri);//�½���һ��Node�ڵ� ������base�������� ����ָ���ǿ��Բ����
			trees.push(nd);//������ڵ�������ȶ���
		}
		return trees.top();
	}
	//����������ɹ��������� charmap����ľ����ַ���Ӧ�ı��� ��vector���� ����������������֤�Ƿ�ֻ����һ����������
	void genrateCode(HuffmanTreeNodeBase *tree, CharMap &cm,Charfrenquent &fren)
	{
		Encoding enc;//�����������ʱ�����vector
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
				k.push_back(*i+'0');//��vector�еı������б���ַ�������ʽ ע��int��char���͵Ļ���
			reverseMap.insert(std::make_pair(k, it->first));//����ֵ�Բ���map
		}
		//����ӳ��������
		auto beg = encodedstr.cbegin();
		auto end = encodedstr.cend();
		auto range = ++encodedstr.cbegin();//�����ʾ��Χ���п����� ���ǽ����[Beg,range) �й������ҵ��ַ��� beg��=range ����Ϊ���ַ���
		int cnt = 0;//cnt�������ڰ�beg���������һ��ƥ��λ�õ�β��
		while (beg != end)
		{
			char dest;
			bool changeres = match_str(reverseMap, beg, range, dest);//����
			if (changeres == true)
			{
				result.push_back(dest);
				for (int i = 0; i <= cnt; ++i)
				{
					++beg;
				}
				if (range == end)//�����ʱ��ƥ��֮��range��λ����β�� ��ô��ʾ�������һ�γɹ���ƥ�� �ͽ���while
					break;
				range = beg + 1;//range>beg
				cnt = 0;//cntc���¿�ʼ����
			}
			else
			{
				++cnt;//���ƥ��ʧ�� ��ôһ��ƥ��ɹ���ôbg�������beg+cnt+1��λ��
				++range;//��ΧҲҪ����
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
			//��ʾ���ָ����Ҷ�ӽڵ� ��ô�����ø��ַ��ı��� ���뱣����int��vector��
			charmap[leaf->getChar()] = precode;
		}
		else
		{
			HuffmanTreeNode *nd = dynamic_cast<HuffmanTreeNode*>(tree);
			if (nd)
			{
				//��ʾ���ǽڵ� ���Ի��Ǳ���ѱ���ѹ��vector
				Encoding leftcode = precode;//���ﶨ��һ���µ�vector����������ֹ��ͬ��vector�����ͻ������
				leftcode.push_back(0);//�����ӵĻ� ·���ϵ�ȨΪ0
				do_genrateCode(nd->getLeftchild(), leftcode, charmap);//������ӿ�ʼ �ݹ�
				Encoding rightcode = precode;//����ͬ��
				rightcode.push_back(1);
				do_genrateCode(nd->getRightchild(), rightcode, charmap);

			}
		}
	}
	//�������Ѱ�ҹ��������ж�Ӧ���ַ� ��һ��������ӳ��� [beg,end�� ע��beg ��=end ��ʾҪƥ��ĵ�������Χ
	bool match_str(std::map<std::string, char> reverseMap,string::const_iterator beg_match, std::string::const_iterator end_match,char &res)
	{
		std::string s(beg_match, end_match);//����һ����ʱ���ַ���
		auto r = reverseMap.find(s);//�����ַ������Ҷ�Ӧ�Ĺ������ַ�ӳ��
		if (r == reverseMap.end())//���û���ҵ��Ļ� ���ص���end������
		{
			return false;
		}
		else
		{
			res = r->second;//�ҵ���ӳ��
			return true;
		}
	}
};