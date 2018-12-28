#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include <functional>
#include <algorithm>
struct Word
{
	std::string word;
	int count;
};
// 单词表
class Vocabulary
{
private:
	// 单词到词频容器
	std::vector<Word> _word_count;
	// 添加某些新单词
	void do_insert_word(const std::string &word);
public:
	// 构造函数
	Vocabulary(const std::string &filepath);
	// 排序并打印
	void print(int column);
};

/* 排序函数
//归并排序
归并算法的合并算法 第一个参数原数组 low为开始的地址 mid*/
template<typename T>
void do_mergeSort_hebing(std::vector<T>& arr, int low, int mid, int high, std::function<bool(const T&, const T&)> &comp)
{
	int i = low;//第一段的序列的下标
	int j = mid + 1;//第二段的序列下标
	int k = 0;//可临时存放合并序列的下标
	T *newarr = new T[high - low + 1];
	//扫描第一段个第二段序列 直到有一个扫描结束
	while (i <= mid && j <= high)
	{
		if (comp(arr[i], arr[j]))
		{
			newarr[k] = arr[i];
			++i;//有最小值的的数组的小标递增
			++k;//临时序列的下标递增
		}
		else
		{
			newarr[k] = arr[j];//填入新的值
			++j;//同理
			++k;//反正k无论如何也要变化
		}
	}
	//注意可能还有没完成的 这里的步骤就是把所有没有写入到新的表中的元素写入
	while (i <= mid)
	{
		newarr[k] = arr[i];
		++i;
		++k;
	}
	while (j <= high)
	{
		newarr[k] = arr[j];
		++j;
		++k;
	}
	for (k = 0, i = low; i <= high; ++i, ++k)
		arr[i] = newarr[k];//更新对应的元素数组里的值
	delete[] newarr;
}

//归并排序的分解算法
template<typename T>
void do_mergeSort_divid(std::vector<T>& arr, int gap, int length, std::function<bool(const T&, const T&)> &comp)
{

	int i = 0;
	for (i = 0; i + 2 * gap - 1/* i+2*gap -1表示的是第一组需要合并的 如果只有一对需要合并 那么这个循环执行一次*/ < length; i = i + 2 * gap/*下一个替换的一对的起始位置*/)
		do_mergeSort_hebing(arr, i, i + gap - 1, i + 2 * gap - 1, comp);
	//余下了两个子表 因为长度的大小是不可能满足的
	if (i + gap - 1 < length)
		do_mergeSort_hebing(arr, i, i + gap - 1, length - 1, comp);
}

//这个接口的函数
template<typename T>
void MergeSort(std::vector<T>& arr, std::function<bool(const T&, const T&)> comp)
{
	int sz = arr.size();
	for (int gap = 1; gap < sz; gap = gap * 2)
	{
		do_mergeSort_divid(arr, gap, sz, comp);//每一次gap递增
	}
}