// DataStructAndAlgorithmsReview.cpp : 定义控制台应用程序的入口点。
//

#include "../stdafx.h"

#include "../00.DataStructAndAlgorithmsReview_Common/List.hpp"
#include "../00.DataStructAndAlgorithmsReview_Common/CA14_string.h"
#include <map>
#include <string>


//文件内存映射
struct TNode
{
	char pText[256];//默认短信长度256个字符
	int dwCount;
	TNode *childNodes[256];
	TNode():dwCount(0)
	{
		for (int i = 0; i < 256; ++i)
		{
			childNodes[i] = nullptr;
		}
	}
	~TNode() {
		for (int i = 0; i < 256; ++i)
		{
			if (childNodes[i])
				delete childNodes[i];
		}
	}
};
void CreateChildNode(TNode *pNode, const char *pText, int nIndex)
{
	static int y = 0;
	if (pNode->childNodes[pText[nIndex]] == nullptr)
	{
		
		pNode->childNodes[pText[nIndex]] = new TNode();
		++y;
		printf("%d\n", y);
	}
	if (pText[nIndex + 1] == '\0')
	{
		pNode->childNodes[pText[nIndex]]->dwCount++;
		strcpy(pNode->childNodes[pText[nIndex]]->pText, pText);
	}
	else if (pText[nIndex] != '\0')
		CreateChildNode(pNode->childNodes[pText[nIndex]], pText, nIndex + 1);
}
void getResult(std::multimap<int, std::string> &msgRes, TNode *root)
{
	int i;
	for (i = 0; i < 256; ++i)
	{
		if (root->childNodes[i])
		{
			if (root->childNodes[i]->dwCount != 0)
			{
				msgRes.emplace(root->childNodes[i]->dwCount,root->childNodes[i]->pText);//如果路径上存在一个
			}
			getResult(msgRes, root->childNodes[i]);
		}
	}
}
void CreateRootNode(char **pTexts, int dwCount)
{
	TNode rn;
	for (int i = 0; i < dwCount; ++i)
		CreateChildNode(&rn, pTexts[i], 0);
	//创建完毕
	std::multimap<int,std::string> messagesandFreq;
	getResult(messagesandFreq, &rn);
	//这个允许重复的映射中 是以频率出现升序排列的！
}
int main()
{
	using namespace std;
	/* 单链表节点
	SingleLinkList<int> slist;
	for (int i =10; i > 0; --i)
	{
		slist.insert(i);
	}
	slist.debug_output_allElements(std::cout);
	slist.sort();
	int s = slist.size();
	slist.debug_output_allElements(std::cout);
	system("pause");
	slist.reverse_traverse();
	slist.debug_output_allElements(std::cout);
	system("pause");
	auto i = slist.findMid();
	if (i)
	{
		std::cout << "中间节点：" << i->Data() << "\n";

	}
	*/
	/*双链表
	DoubleCircleLinkList<int> dclist;
	for (int i = 20; i < 10; ++i)
		dclist.insert(10-i);
	std::cout << "大小:" << dclist.size() << "\n";
	dclist.debug_output_all_begin(std::cout);
	dclist.debug_output_all_last(std::cout);
	dclist.remove(111);
	dclist.remove(5);
	dclist.debug_output_all_begin(std::cout);
	dclist.debug_output_all_last(std::cout);
	std::cout << "大小:" << dclist.size() << "\n";
	dclist.sort();
	dclist.debug_output_all_begin(std::cout);
	dclist.debug_output_all_last(std::cout);
	std::cout << "大小:" << dclist.size() << "\n";
	*/
	/*约瑟夫环问题 循环链表解决
	DoubleCircleLinkList<int> hosephus;
	int number = 13;//总人数
	int report = 10;//报道的数
	for (int i = 0; i < number; ++i)
		hosephus.insert(i + 1);
	int start = 5;//从这个数字开始报
	auto beg = hosephus.begin();
	for (int i = 0; i < start-1; ++i)
	{
		//这个判断没办法了 因为++总是会递增到head 但是head又不是我想要的所以就需要两次++
		if (beg->getNext() == hosephus.getHead())
			++beg;
		++beg;
	}
	while (!hosephus.isEmpty())
	{
		int count = 1;
		while (count != report)
		{
			++count;
			if (beg->getNext() == hosephus.getHead())
				++beg;
			++beg;
		}
		std::cout << *beg << std::endl;
		int temp=*beg;
		if (beg->getNext() == hosephus.getHead())
			++beg;
		++beg;
		hosephus.remove(temp);
	}
	*/
	/*内存文件映射 感觉就是Trie树
	char *m1 = "Hello!";
	char *m2 = "Hello!";
	char *m3 = "Hi!";
	char *m4 = "Are you okay?";
	char *m5 = "Are you sure?";
	char *m6 = "Hi!";
	char *messages[] = { m1,m2,m3,m4,m5,m6 };
	CreateRootNode((char**)messages, 6);
	*/
	/* 字符转换
	char m[2][5] = { "abcd","vbb" };
	auto i = m[0];
	int ms = sizeof(m[1]);
	printf("%s\n", m[0]);
	printf("%s",m[1]); 
	*/
	/*求非连续最大子字符串出现的次数
	std::string s; std::vector<std::string> res;
	std::cout << "请输入字符串:";
	std::cin >> s;
	int u = getMaxSubStrCount(res,s);
	std::cout << "最大的非连续子字符串出现次数为：" << u << "他们分别是："<<std::endl;
	for (auto i = res.cbegin(); i != res.cend(); ++i)
	{
		std::cout << *i << std::endl;
	}
	*/
	/*出现最多的连续的子字符串
	std::string s; std::vector<std::string> res;
	std::cout << "请输入字符串:";
	std::cin >> s;
	int u = getLinkedMaxSubStr(s, res);
	std::cout << "最大的连续子字符串出现次数为：" << u << " 他们分别是："<<std::endl;
	for (auto i = res.cbegin(); i != res.cend(); ++i)
	{
		std::cout << *i << std::endl;
	}
	*/
	/*搜索组长的子串出现的位置
	std::string s; std::string res;
	std::cout << "请输入字符串:";
	std::cin >> s;
	int u = get_MaxCommonString(s, res);
	std::cout << "出现的子字符串最长的位置：" << u << " 字符串为："<<res<<std::endl;
	*/
/*搜索子字符串
std::string s1, s2;
std::cout << "主字符串：";
std::cin >> s1;
std::cout << "子字符串：";
std::cin >> s2;
std::cout << "出现的位置：" << my_strstr(s1, s2) << '\n';
*/
/*特殊的反转 p248
std::string s1;
getline(std::cin, s1);
SpecialFlip(s1);

std::cout << "翻转后：" << s1 << '\n';
*/
char p[] = "ABCDEFGHI";
StringMove_01(p, 3);
printf("%s", p);
	
    return 0;
}

