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
// ���ʱ�
class Vocabulary
{
private:
	// ���ʵ���Ƶ����
	std::vector<Word> _word_count;
	// ���ĳЩ�µ���
	void do_insert_word(const std::string &word);
public:
	// ���캯��
	Vocabulary(const std::string &filepath);
	// ���򲢴�ӡ
	void print(int column);
};

/* ������
//�鲢����
�鲢�㷨�ĺϲ��㷨 ��һ������ԭ���� lowΪ��ʼ�ĵ�ַ mid*/
template<typename T>
void do_mergeSort_hebing(std::vector<T>& arr, int low, int mid, int high, std::function<bool(const T&, const T&)> &comp)
{
	int i = low;//��һ�ε����е��±�
	int j = mid + 1;//�ڶ��ε������±�
	int k = 0;//����ʱ��źϲ����е��±�
	T *newarr = new T[high - low + 1];
	//ɨ���һ�θ��ڶ������� ֱ����һ��ɨ�����
	while (i <= mid && j <= high)
	{
		if (comp(arr[i], arr[j]))
		{
			newarr[k] = arr[i];
			++i;//����Сֵ�ĵ������С�����
			++k;//��ʱ���е��±����
		}
		else
		{
			newarr[k] = arr[j];//�����µ�ֵ
			++j;//ͬ��
			++k;//����k�������ҲҪ�仯
		}
	}
	//ע����ܻ���û��ɵ� ����Ĳ�����ǰ�����û��д�뵽�µı��е�Ԫ��д��
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
		arr[i] = newarr[k];//���¶�Ӧ��Ԫ���������ֵ
	delete[] newarr;
}

//�鲢����ķֽ��㷨
template<typename T>
void do_mergeSort_divid(std::vector<T>& arr, int gap, int length, std::function<bool(const T&, const T&)> &comp)
{

	int i = 0;
	for (i = 0; i + 2 * gap - 1/* i+2*gap -1��ʾ���ǵ�һ����Ҫ�ϲ��� ���ֻ��һ����Ҫ�ϲ� ��ô���ѭ��ִ��һ��*/ < length; i = i + 2 * gap/*��һ���滻��һ�Ե���ʼλ��*/)
		do_mergeSort_hebing(arr, i, i + gap - 1, i + 2 * gap - 1, comp);
	//�����������ӱ� ��Ϊ���ȵĴ�С�ǲ����������
	if (i + gap - 1 < length)
		do_mergeSort_hebing(arr, i, i + gap - 1, length - 1, comp);
}

//����ӿڵĺ���
template<typename T>
void MergeSort(std::vector<T>& arr, std::function<bool(const T&, const T&)> comp)
{
	int sz = arr.size();
	for (int gap = 1; gap < sz; gap = gap * 2)
	{
		do_mergeSort_divid(arr, gap, sz, comp);//ÿһ��gap����
	}
}