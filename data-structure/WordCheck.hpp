
#include "Hash.hpp"
#include "BinarySearchTree.hpp"
#include <vector>
#include <fstream>
#include <map>
#include <set>
class WordsCheck
{
private:
	Dictionary di;//为何不能const char*初始化
	string filen;
	vector<string> fileline;
	map<string, set<Entry>> wrongwords;
public:
	WordsCheck(string file) :filen(file) {
		cout << "Dictionary is loading...\n";
		di.init("wordlist.txt", false);
		std::ifstream ifs(file);
		if (!ifs)
		{
			cerr << "Cannot open file! Loading file abort!\n";
			return;
		}
		string sline;
		while (getline(ifs, sline))
		{
			fileline.push_back(sline);
		}
	}
	WordsCheck() {
		cout << "Dictionary is loading...\n";
		di.init("wordlist.txt", false);
	}
	void toLower(string &s)
	{
		//除了A I其他的转为小写单词 因为是A a都是不定冠词 I是主格 是存在匹配项的
		if (s.size() == 1)
		{
			if (s[0] != 'A' && s[0] != 'I')
			{
				if (s[0] >= 'A' && s[0] < 'Z')
				{
					s[0] = s[0] + ('a' - 'A');
				}
			}
		}
		else
		{
			for (int i = 0; i < s.size(); ++i)
			{
				if (s[i] >= 'A' && s[i] < 'Z')
				{
					s[i] = s[i] + ('a' - 'A');
				}
			}
		}
	}
	bool isWord(string s)
	{
		if (s.size() < 1)
		{
			return false;//考虑：不考虑单个字符 这种单词一般是主格 之类的 也不太可能被其他的字符替换
		}
		if ((s.size() == 1 && isalpha(s[0])) || s.size() >= 2)

			return true;
		else
			return false;
	}
	void WordCorrect(string &w)
	{
		toLower(w);
		if (w.size() >= 1)
		{
			if (!isalpha(w.back()))
			{
				w.pop_back();//去掉尾巴后的标点
			}
		}
	}
	//原作者使用hash表存储字典的单词 我还是用RB吧 到时候试一试哈希的
	//这个是判断任意删除一个字母是否可以匹配
	void SpellingCheck1(string word, set<Entry> &suggest)
	{
		//这个是判断任意删除一个字母是否可以匹配 只有一个字符不考虑
		if (word.size() == 1)
			return;
		auto isfind = di.findEntry(word);
		if (!isfind)
		{
			for (int j = 0; j < word.size(); ++j)
			{
				string neword;//每次的循环更新新的单词
				for (int i = 0; i < word.size(); ++i)
				{

					if (i == j)
						continue;//忽略单词
					neword.push_back(word[i]);//插入后面的单词
				}
				auto fin = di.findEntry(neword);
				if (fin)
					suggest.insert(*fin);//添加单词
			}
		}
	}
	//任意字母被替换的情况
	void SpellingCheck2(string word, set<Entry> &suggest)
	{
		if (word.size() == 1)
			return;
		string alpha = "abcdefghijklmnopqrstuvwxyz";
		Entry *fins = nullptr;
		for (int i = 0; i < word.size(); ++i)
		{
			string n = word;
			for (int j = 0; j < 26; ++j)
			{
				n[i] = alpha[j];
				fins = di.findEntry(n);
				if (fins)
				{
					suggest.insert(*fins);
				}
			}
		}

	}
	//置换相邻字母
	void SpellingCheck3(string word, set<Entry> &suggest)
	{
		if (word.size() == 1)
			return;
		int changeindex = 0;
		Entry *fins = nullptr;
		string n;
		for (int k = 1; k <= word.size() - 1; ++k)
		{
			n = word;
			char tmpc = n[changeindex + 1];
			n[changeindex + 1] = n[changeindex];
			n[changeindex] = tmpc;
			fins = di.findEntry(n);
			if (fins)
				suggest.insert(*fins);
			++changeindex;
		}
	}
	//任意位置插入
	void SpellingCheck4(string word, set<Entry> &suggest)
	{
		string alpha = "abcdefghijklmnopqrstuvwxyz";
		Entry *fins = nullptr;
		for (int i = 0; i <= word.size(); ++i)
		{
			string n = word;
			n.insert(i, 1, 'i');
			for (int j = 0; j < 26; ++j)
			{
				n[i] = alpha[j];
				fins = di.findEntry(n);
				if (fins)
					suggest.insert(*fins);
			}
		}
	}
	//检查主格的大写
	void SpellingCheck5(string word, set<Entry> &suggest)
	{
		if (word.size() == 1)
		{
			if (word[0] == 'i')
				suggest.insert(Entry("I", ""));
		}
	}

	void check()
	{
		for (int i = 0; i < fileline.size(); ++i)
		{
			string word;
			std::stringstream ss(fileline[i]);
			while (ss >> word)
			{
				if (isWord(word))//是不是单词
				{
					WordCorrect(word);
					auto fin = di.findEntry(word);
					if (!fin)//不存在结果
					{
						auto exist = wrongwords[word];//是否已经存在
						if (exist.size() > 0)//是否存在已经得出结论的错误单词
						{
							cout << "Line " << i + 1 << " : \"" << word << "\" : \n            suggestions:\n";
							for (auto it = wrongwords[word].cbegin(); it != wrongwords[word].cend(); ++it)
								cout << "               " << it->getEnglish() << endl;
						}
						else
						{
							set<Entry> suggest;
							//获得搜索建议
							SpellingCheck1(word, suggest);
							SpellingCheck2(word, suggest);
							SpellingCheck3(word, suggest);
							SpellingCheck4(word, suggest);
							SpellingCheck5(word, suggest);
							cout << "Line " << i + 1 << " : \"" << word << "\" : \n            suggestions:\n";
							wrongwords[word] = suggest;
							for (auto it = suggest.cbegin(); it != suggest.cend(); ++it)
								cout << "               " << it->getEnglish() << endl;
						}
					}

				}
				word.clear();

			}
		}
	}
	void demo_mode()
	{
		cout << "Dictionary load finished!\nPlease input the filename of the text you want to check spelling which can be found in the program path!(Example: text.txt )\nIf you want to exit this program, please input \'q\' and enter to exit.";
		string fn;
		char c;
		do {
			cout << "\nFile: ";
			while ((c = getchar()) != '\n' && c != 'q')
				fn.push_back(c);
			if (c == 'q')
				break;
			fileline.clear();
			std::ifstream ifs(fn);
			if (!ifs)
			{
				cerr << "Cannot open file! Loading file abort!\n";
				fn.clear();
				continue;
			}
			string sline;
			while (getline(ifs, sline))
			{
				fileline.push_back(sline);
			}
			check();
			fn.clear();
		} while (1);
	}
};
struct EnglishWord :public HashSetKeyBase//英语单词类继承自key基类
{
	string english;
	EnglishWord(string s) :english(s) {}
	EnglishWord() :english(string()) {}
};
bool operator==(const EnglishWord &l, const EnglishWord &r)
{
	return l.english == r.english;
}
bool operator!=(const EnglishWord &l, const EnglishWord &r)
{
	return l.english != r.english;
}
bool operator<(const EnglishWord &l, const EnglishWord &r)
{
	return l.english < r.english;
}
bool operator>(const EnglishWord &l, const EnglishWord &r)
{
	return l.english == r.english;
}
ostream &operator<<(ostream &os, const EnglishWord &w)
{
	os << w.english;
	return os;
}
unsigned long EnglishWord_Hash(const EnglishWord &ke)
{
	return ENTRYSTORED_Hash(ke.english);
}
bool eq(const EnglishWord &l, const EnglishWord &r) {
	return l == r;
}


class WordCheck_HashStored
{
private:
	//HashTable<EnglishWord, decltype(EnglishWord_Hash)> *di=nullptr;//这个是使用双重散列发的hash表 这个速度慢
	HashSet < EnglishWord, decltype(EnglishWord_Hash), decltype(eq) > *di = nullptr;//注意 在类内初始的是声明 构造的话需要在当前类的构造函数中进行
	std::map<string, set<string>> suggest;
	vector<std::string> fileline;
public:
	~WordCheck_HashStored() { delete di; }
	/*
	WordCheck_HashStored(string fn):di(new HashTable<EnglishWord, decltype(EnglishWord_Hash)>(EnglishWord_Hash, 53))
	{
		std::ifstream ifs(fn);
		string wd;
		cout << "Dictionary is loading...";
		if (ifs)
		{
			while (getline(ifs, wd))
			{
				//insert
				di->insert(wd);
			}
		}
		else
		{
			cout << "\nFail to load dictionary. Program terminate.\n";
			exit(1);
		}
	}
	*/
	WordCheck_HashStored(string fn) :di(new HashSet < EnglishWord, decltype(EnglishWord_Hash), decltype(eq)>(EnglishWord_Hash))
	{
		std::ifstream ifs(fn);
		string wd;
		cout << "Dictionary is loading...";
		if (ifs)
		{
			while (getline(ifs, wd))
			{
				//insert
				di->insert(wd);
			}
		}
		else
		{
			cout << "\nFail to load dictionary. Program terminate.\n";
			exit(1);
		}
	}
	void toLower(string &s)
	{
		//除了A I其他的转为小写单词 因为是A a都是不定冠词 I是主格 是存在匹配项的
		if (s.size() == 1)
		{
			if (s[0] != 'A' && s[0] != 'I')
			{
				if (s[0] >= 'A' && s[0] < 'Z')
				{
					s[0] = s[0] + ('a' - 'A');
				}
			}
		}
		else
		{
			for (int i = 0; i < s.size(); ++i)
			{
				if (s[i] >= 'A' && s[i] < 'Z')
				{
					s[i] = s[i] + ('a' - 'A');
				}
			}
		}
	}
	bool isWord(string s)
	{
		if (s.size() < 1)
		{
			return false;//考虑：不考虑单个字符 这种单词一般是主格 之类的 也不太可能被其他的字符替换
		}
		if ((s.size() == 1 && isalpha(s[0])) || s.size() >= 2)

			return true;
		else
			return false;
	}
	void WordCorrect(string &w)
	{
		toLower(w);
		if (w.size() >= 1)
		{
			if (!isalpha(w.back()))
			{
				w.pop_back();//去掉尾巴后的标点
			}
		}
	}
	//哈希的
	//这个是判断任意删除一个字母是否可以匹配
	void SpellingCheck1(string word, set<string> &suggest)
	{
		//这个是判断任意删除一个字母是否可以匹配 只有一个字符不考虑
		if (word.size() == 1)
			return;
		auto isfind = di->find(word);
		if (!isfind)
		{
			for (int j = 0; j < word.size(); ++j)
			{
				string neword;//每次的循环更新新的单词
				for (int i = 0; i < word.size(); ++i)
				{

					if (i == j)
						continue;//忽略单词
					neword.push_back(word[i]);//插入后面的单词
				}
				auto fin = di->find(neword);
				if (fin)
					//suggest.insert(fin->data.english);//添加单词
					suggest.insert(fin->english);
			}
		}
	}
	//任意字母被替换的情况
	void SpellingCheck2(string word, set<string> &suggest)
	{
		if (word.size() == 1)
			return;
		string alpha = "abcdefghijklmnopqrstuvwxyz";
		for (int i = 0; i < word.size(); ++i)
		{
			string n = word;
			for (int j = 0; j < 26; ++j)
			{
				n[i] = alpha[j];
				auto fins = di->find(n);
				if (fins)
				{
					//suggest.insert(fins->data.english);
					suggest.insert(fins->english);
				}
			}
		}

	}
	//置换相邻字母
	void SpellingCheck3(string word, set<string> &suggest)
	{
		if (word.size() == 1)
			return;
		int changeindex = 0;
		//HashListNode<EnglishWord> *fins = nullptr;
		string n;
		for (int k = 1; k <= word.size() - 1; ++k)
		{
			n = word;
			char tmpc = n[changeindex + 1];
			n[changeindex + 1] = n[changeindex];
			n[changeindex] = tmpc;
			auto fins = di->find(n);
			if (fins)
				suggest.insert(fins->english);
			++changeindex;
		}
	}
	//任意位置插入
	void SpellingCheck4(string word, set<string> &suggest)
	{
		string alpha = "abcdefghijklmnopqrstuvwxyz";
		//HashListNode<EnglishWord> *fins = nullptr;
		for (int i = 0; i <= word.size(); ++i)
		{
			string n = word;
			n.insert(i, 1, 'i');
			for (int j = 0; j < 26; ++j)
			{
				n[i] = alpha[j];
				auto fins = di->find(n);
				if (fins)
					suggest.insert(fins->english);
			}
		}
	}
	//检查主格的大写
	void SpellingCheck5(string word, set<string> &suggest)
	{
		if (word.size() == 1)
		{
			if (word[0] == 'i')
				suggest.insert(string("I"));
		}
	}

	void check()
	{
		for (int i = 0; i < fileline.size(); ++i)
		{
			string word;
			std::stringstream ss(fileline[i]);
			while (ss >> word)
			{
				if (isWord(word))//是不是单词
				{
					WordCorrect(word);
					auto fin = di->find(word);
					if (!fin)//不存在结果
					{
						auto exist = suggest[word];//是否已经存在
						if (exist.size() > 0)//是否存在已经得出结论的错误单词
						{
							cout << "Line " << i + 1 << " : \"" << word << "\" : \n            suggestions:\n";
							for (auto it = suggest[word].cbegin(); it != suggest[word].cend(); ++it)
								cout << "               " << *it << endl;
						}
						else
						{
							set<string> sugg;
							//获得搜索建议
							SpellingCheck1(word, sugg);
							SpellingCheck2(word, sugg);
							SpellingCheck3(word, sugg);
							SpellingCheck4(word, sugg);
							SpellingCheck5(word, sugg);
							cout << "Line " << i + 1 << " : \"" << word << "\" : \n            suggestions:\n";
							suggest[word] = sugg;
							for (auto it = sugg.cbegin(); it != sugg.cend(); ++it)
								cout << "               " << *it << endl;
						}
					}

				}
				word.clear();

			}
		}
	}
	void demo_mode()
	{
		cout << "Dictionary load finished!\nPlease input the filename of the text you want to check spelling which can be found in the program path!(Example: text.txt )\nIf you want to exit this program, please input \'q\' and enter to exit.";
		string fn;
		char c;
		do {
			cout << "\nFile: ";
			while ((c = getchar()) != '\n' && c != 'q')
				fn.push_back(c);
			if (c == 'q')
				break;
			fileline.clear();
			std::ifstream ifs(fn);
			if (!ifs)
			{
				cerr << "Cannot open file! Loading file abort!\n";
				fn.clear();
				continue;
			}
			string sline;
			while (getline(ifs, sline))
			{
				fileline.push_back(sline);
			}
			check();
			fn.clear();
		} while (1);
	}
};