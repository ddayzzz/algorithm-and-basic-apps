#include <string>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
//int u = 55;
//以下是针对STRING的HASH函数
const unsigned long FNV1A_32_PRIME = 16777619;
const unsigned long FNV1A_32_OFFSET_BASIS = 2166136261;
unsigned long BKDRHash(const string &s,const int hashsize,unsigned long seed=31)
{
	unsigned long val = 0;
	int i;
	for (i = 0; i < s.size(); ++i)
		val = val*seed + s[i];
	return val % hashsize;
}
unsigned long RSHash(const string &s, int hashsize)
{
	unsigned long a = 31415; unsigned long b = 27183;
	unsigned long val = 0;
	int i;
	for (i = 0; i < s.size(); ++i)
	{
		val = (val * a + s[i]) % hashsize;
		a = a*b % (hashsize - 1);
	}
	return val;
}
unsigned long FNV1A_32_Hash(const string &s)
{
	unsigned long val = FNV1A_32_OFFSET_BASIS;
	int i = 0;
	for (; i < s.size(); ++i)
	{
		val = val ^ s[i];
		val = val * FNV1A_32_PRIME;
	}
	return val;
}
unsigned long FNV1A_32_Hash_Optimize(const string &s)
{
	unsigned long val = FNV1A_32_OFFSET_BASIS;
	int i = 0;
	for (; i < s.size(); ++i)
	{
		val = val  ^ s[i];
		val += (val << 1 /*=val*2 */) + (val << 4/* =val*16 */)
			+ (val << 7) + (val << 8) + (val << 24);
	}
	return val;
}
static const int num_primes = 25;
static const unsigned long primes_list[] = {
	53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
	196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843,
	50331653, 100663319, 201326611, 402653189, 805306457
};//这个是存储素数的列表
//英语单词词条的HASH计算 这个放是BKDR
unsigned long ENTRYSTORED_Hash(const string &s)
{
	unsigned int res = 0;
	for (int i = 0; i < s.size(); ++i)
		res = res * 1000 + s[i];
	return res;
}
//拉链法解决冲突
//这个模板类用于容纳节点
template<typename T>
struct HashListNode
{
	HashListNode *next = nullptr;//下一个节点
	T data;//节点的值
	HashListNode(T dat) :data(dat), next(nullptr) {}
	HashListNode() :next(nullptr) {}
};
template<typename T> class HashNode
{
private:
	
	int size;//这个表示表的大小 
	HashListNode<T> *element;//这个存放表的节点
public:
	HashNode(int sz) :size(sz) {
		element = new HashListNode<T>[sz];
	}
	HashNode():size(0),element(nullptr){}
	void setSize(int sz)
	{
		size = sz;
		element = new HashListNode<T>[sz];//保存的数组
	}
	void insert(int pos,T dat)
	{
		if (element[pos].next == nullptr)
		{
			element[pos].next = new HashListNode<T>(dat);
		}
		else
		{
			//如果相同的话应该在相同的位置插入的尾部插入节点
			HashListNode<T> *nd = element[pos].next;
			while (nd->next != nullptr && nd->data !=dat)
				nd = nd->next;
			if(nd->data !=dat)
				nd->next = new HashListNode<T>(dat);
		}
	}
	void remove(int pos, T dat)
	{
		if (element[pos]->next)
		{
			HashListNode<T> *nl = element[pos];
			HashListNode<T> *tmp;
			while (nl->next && nl->next->data != dat)
			{
				nl = nl->next;
			}
			if (nl->next == nullptr)
			{
				//表示已经末尾但是还是不相等
				return;
			}
			tmp = nl->next;//删除
			nl->next = nl->next->next;
			delete tmp;
		}
		
	}
	void clear()
	{
		HashListNode<T> *node,*tmp;
		for (int i = 0; i < size; ++i)
		{
			node = element[i].next;
			while (node != nullptr)
			{
				tmp = node;
				node = node->next;//设置下一个位置
				delete tmp;//释放节点
			}
			element[i].next = node;
		}
		delete[] element;//释放元素
		element = nullptr;
	}
	HashListNode<T> *find(int pos,T dat)
	{
		HashListNode<T> *node = element[pos].next;
		while (node != nullptr && node->data !=dat)
		{
			node = node->next;
		}
		return node;
	}
	~HashNode() { clear(); }
	void print()
	{
		cout << "哈希表存储结构如下：" << endl;
		HashListNode<T> *node;
		for (int i = 0; i < size; ++i)
		{
			cout << "第" << i + 1 << "个：";
			if (element[i].next)
			{
				node = element[i].next;
				while (node)
				{
					cout << node->data << " ";
					node = node->next;
				}
				cout << endl;
			}
			else
			{
				cout << "无元素\n";
			}
		}
	}
};
template<typename T,typename HASHFCN> class HashTable
{
private:
	HashNode<T> hashnodes;
	function<HASHFCN> hashfcn;//不能传递函数对象给模板类 因为类型不是完整的 所以传递一个可调用对象目的是兼容lambada
	int size;
public:
	HashTable(HASHFCN hash, int sz) :hashfcn(hash), size(sz) { hashnodes.setSize(sz); }
	//获取合理的位置
	int getPostion(T &dat)
	{
		unsigned long  pos = hashfcn(dat);
		if (pos < 0 || pos >= size)
		{
			pos = pos % size;
		}
		return pos;
	}
	//插入
	void insert(T dat)
	{
		int pos = getPostion(dat);
		hashnodes.insert(pos, dat);
	}
	void print()
	{
		hashnodes.print();
	}
	//寻找等价的节点 成功返回地址 失败的话返回nullptr
	HashListNode<T> *find(T dat)
	{
		int pos = getPostion(dat);
		HashListNode<T> *nd = hashnodes.find(pos, dat);
		return nd;
	}
	~HashTable()
	{

	}
};
//Hash表 这个是用了线性探查法处理冲突
class HashSetKeyBase//这个是基类 用于HashSet 这个返回这个关键字是否被使用了
{
public:
	virtual ~HashSetKeyBase() {}//必须的
	bool getUsed() const { return isused; }
	void setUsed(bool used) { isused=used; }
	HashSetKeyBase():isused(false){}

private:
	bool isused = false;
};


template<typename key_type, 
	typename hash_func, 
	typename key_equal_func> //=bool(const typename key_type&,const typename key_type&)
class HashSet
{
protected:
	
	function<hash_func> hashfcn;
	function<key_equal_func> eqfcn;
	vector<key_type> *stored;
	int keyscount;//关键字
	int prime;//素数列表的索引 如果存在的关键字的个数不适合再插入的话 就需要重新分配大小了 所以需要在resize递增他
	int table_size() const { return primes_list[prime]; }
	float load_factor() { return (float)(keyscount) / table_size(); }//评估是否能够再插入
public:
	//HashSet():keyscount(0),prime(0),stored(new vector<key_type>(primes_list[0])){}//默认构造一下
	//可以不传递相等操作 如果不传递的话就key_type需要有相等运算符
	HashSet(hash_func hf, key_equal_func ke=nullptr) :hashfcn(hf), eqfcn(ke), keyscount(0), prime(0), stored(new vector<key_type>(primes_list[0])) {}
	virtual ~HashSet() { 
		delete stored; }
	virtual int getKeysCount() { return keyscount; }
	virtual key_type* find(const key_type &k)
	{
		int p = hashfcn(k) % table_size();//依据关键字获得位置
		while ((*stored)[p].getUsed())
		{
			if ((eqfcn !=nullptr && eqfcn((*stored)[p], k)) || (eqfcn ==nullptr && (*stored)[p]==k)) //关键字相等的话
				return &(*stored)[p];
			p++;
			if (p == table_size()) p = 0;
		}
		return nullptr;
	}
	virtual void insert(const key_type &k)
	{
		if (load_factor() > .7) resize();//评估当前的大小是否适合继续插入 否则调整大小
		int pos = hashfcn(k) % table_size();//获取合理的位置
		while ((*stored)[pos].getUsed() == true)
		{
			pos++;
			if (pos == table_size())
				pos = 0;//从0开始
		}
		if (pos >= 0 && pos < table_size())
		{
			(*stored)[pos] = k;
			(*stored)[pos].setUsed(true);
			++keyscount;
		}

	}
	virtual void remove(const key_type &k)
	{
		key_type *fis = find(k);
		if (fis)
		{
			fis->setUsed(false);
			--keyscount;
		}
	}
	int resize()
	{
		if (prime == num_primes - 1)
		{
			cerr << "Storage for program is full. Program terminate!";
			exit(2);//已经是最后一个大小 适合插入了 不能再递增了
		}
		int prev = primes_list[prime++];
		int newsz = primes_list[prime];//新的大小
		vector<key_type> *newvec = new vector<key_type>(newsz);
		for (int i = 0; i < prev; ++i)
		{
			if ((*stored)[i].getUsed() == true)//表示确实有元素
			{
				key_type key = (*stored)[i];
				int pos = hashfcn(key) % newsz;//key在新的大小的位置
				while (pos < newsz && (*newvec)[pos].getUsed())
					++pos;
				if (pos == newsz)
					pos = 0;
				while ((*newvec)[pos].getUsed())
					++pos;//从0开始再搜索
				(*newvec)[pos] = key;
				(*newvec)[pos].setUsed(true);
			}
		}
		delete stored;//释放运来的指针
		stored = newvec;
		return newsz;
	}
};