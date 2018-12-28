#include "compare.h"

void compare_para(const char * filepath, const char * libfilepath)
{
	std::vector<Word> lib_words, file_words;
	std::vector<int> end_of_para, end_of_lib_para;
	auto &&total_files = read_word_seq(filepath, file_words, &end_of_para);
	auto &&total_lib = read_word_seq(libfilepath, lib_words, &end_of_lib_para);
	// 遍历每一个段落
	int left = 0;
	int right;
	int para_index = 1;
	for (int i = 0; i < end_of_para.size(); ++i)
	{
		right = end_of_para[i];
		if (left < right)
		{
			std::cout << "Para " << para_index++ << ':' << std::endl;
			// 存在一个段落
			// 构造新的单词序列
			std::vector<Word> file_words_seq(file_words.cbegin() + left, file_words.cbegin() + right);
			// 去掉相对位置的偏移
			for (auto &&word : file_words_seq)
			{
				word.count = word.count - left;
			}
			// compare , 看一看和哪一个lib的句子的 最相似
			int lib_left=0;
			int lib_right;
			int lib_para_index=1 ;
			int max_para_index = -1;
			float max_para_score = -1.0f;
			for (int z = 0; z < end_of_lib_para.size(); ++z)
			{
				lib_right = end_of_lib_para[z];
				if (lib_left < lib_right)
				{
					// 句子匹配
					std::vector<Word> lib_word_seq(lib_words.cbegin() + lib_left, lib_words.cbegin() + lib_right);
					// 去掉相对位置的偏移
					for (auto &&word : lib_word_seq)
					{
						word.count = word.count - lib_left;
					}
					// 
					float ts = compare(total_files, file_words_seq, total_lib, lib_word_seq);
					if (ts > max_para_score)
					{
						max_para_index = lib_para_index;
						max_para_score = ts;
					}
					++lib_para_index;
					lib_left = lib_right;
				}
				else
				{
					break;
				}
			}
			std::cout << "Max score : " << max_para_score << " Para " << max_para_index << " In Lib" << std::endl;
			//
			left = right;
		}
		else
		{
			break;
		}
	}
}

float compare(
	const std::string &total_files, 
	const std::vector<Word> &file_words, 
	const std::string &total_lib,
	const std::vector<Word> &lib_words)
{
	// 最长公共子序列 数组的元素是一个小单词
	//std::vector<Word> lib_words;
	//auto &&total_files = read_word_seq(filepath, file_words);
	//auto &&total_lib = read_word_seq(libfilepath, lib_words);
	// 最长公共子序列的
	int vsize = file_words.size() + 1;
	int hsize = lib_words.size() + 1;
	int **arr = new int*[vsize];
	From **frm = new From*[vsize];
	for (int i = 0; i < vsize; ++i)
	{
		arr[i] = new int[hsize];
		frm[i] = new From[hsize];
		arr[i][0] = 0;
	}
	// 第 0 行和列均以用 0 初始化
	for (int i = 0; i < hsize; ++i)
		arr[0][i] = 0;
	// 构建表
	for (int i = 1; i < vsize; ++i)
	{
		for (int j = 1; j < hsize; ++j)
		{
			bool same = compare_word(file_words[i - 1], lib_words[j - 1]);
			if (same)
			{
				arr[i][j] = arr[i - 1][j - 1] + 1;
				frm[i][j] = From::Same;
			}
			else
			{
				// 看看那个大？
				if (arr[i][j - 1] > arr[i - 1][j])
				{
					// 左大
					arr[i][j] = arr[i][j - 1];
					frm[i][j] = From::Left;
				}
				else
				{
					// 上大
					arr[i][j] = arr[i - 1][j];
					frm[i][j] = From::Top;
				}
			}
		}
	}
	int j = 9;
	// 递归求公共子序列
	std::vector<std::pair<Word, Word>> common_seq;
	output_the_same_seq(frm, vsize -1, hsize - 1, lib_words, file_words, common_seq);
	// 反转
	std::reverse(common_seq.begin(), common_seq.end());
	// 打印
	float s = print(total_lib, total_files, lib_words, file_words, common_seq);
	// 释放资源
	for (int i = 0; i < vsize; ++i)
	{
		delete[] arr[i];
		delete[] frm[i];
	}
	return s;
}

std::string read_word_seq(const char * path, std::vector<Word>& seq, std::vector<int> *end_of_para)
{
	std::ostringstream s;
	std::ifstream stream(path);
	std::string word;
	char ch;
	int word_count = 1;
	while (!stream.eof())
	{
		// 没有EOF
		stream >> std::noskipws >> ch;
		// 1. 当前的字符是空 对齐 换行 - ' 认为单词的结束
		if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '-' || ch == '\'')
		{
			if (!word.empty())
			{
				seq.emplace_back(Word{ word, word_count++ });
				word = std::string();
				
			}
		}
		// 2. A-Z a-z
		else if (isalpha(ch))
		{
			word.push_back(ch);
		}
		else if(ch == '.' || ch == '?' || ch == '!')
		{
			if(end_of_para)
				end_of_para->push_back(word_count);
		}
		s << ch;
	}
	if (!word.empty())
	{
		seq.emplace_back(Word{ word, word_count });
	}
	return s.str();
}

bool compare_word(const Word & lhs, const Word & rhs)
{
	int lsize = lhs.word.size(), rsize = rhs.word.size();
	if (lsize != rsize)
		return false;
	for (int i = 0; i < lsize; ++i)
	{
		if (lhs.word[i] != rhs.word[i])
		{
			// 可能有大写的情况
			char lc = isupper(lhs.word[i]) ? lhs.word[i] + 32 : lhs.word[i];
			char rc = isupper(rhs.word[i]) ? rhs.word[i] + 32 : rhs.word[i];
			if (lc != rc)
				return false;
		}
	}
	return true;
}

void output_the_same_seq(From ** arr, int v, int h, 
	const std::vector<Word> &libs, 
	const std::vector<Word> &files, 
	std::vector<std::pair<Word, Word>> &common_seq)
{
	if (v == 0 || h == 0)
		return;
	// 递归，判断来源
	auto &&frm = arr[v][h];
	if (frm == From::Same)
	{
		common_seq.emplace_back(std::make_pair(files[v - 1], libs[h - 1]));
		output_the_same_seq(arr, v - 1, h - 1, libs, files, common_seq);
	}
	else if (frm == From::Left)
		output_the_same_seq(arr, v, h - 1, libs, files, common_seq);
	else if (frm == From::Top)
		output_the_same_seq(arr, v - 1, h, libs, files, common_seq);
}

float print(const std::string & lib, const std::string & files, const std::vector<Word> &lib_words, const std::vector<Word> &file_words, const std::vector<std::pair<Word, Word>> &words)
{
	if (words.size() <= 0)
	{
		return 0.0f; // 没有匹配,逗我呢
	}
	// std::cout << files << std::endl;
	// 输出标记
	float score = 0.0f;
	int total = 0;
	int j = 0;
	int je = words.size() - 1;
	// j 是起始的开始的单词
	// 获取相同的位置
	const Word &file_low = words[j].first;
	const Word &file_upper = words[je].first;
	const Word &lib_low = words[j].second;
	const Word &lib_upper = words[je].second;
	//
	int lib_file_offset = (file_upper.count - file_low.count) - (lib_upper.count - lib_low.count);
	int offset_backup = lib_file_offset;
	// 计算总共的词数
	total = file_words.size(); // 计算 file 单词个数
	// 特殊情况 lib_file_offset = 0
	if (lib_file_offset == 0)
	{
		int m = std::min(file_upper.count - file_low.count, lib_upper.count - lib_low.count);
		// 直接比较, 不存在插入空的情况
		for (int ii = 0; ii <= m; ++ii)
		{
			int file_index = file_words[file_low.count - 1 + ii].count - 1;
			int lib_index = lib_words[lib_low.count - 1 + ii].count - 1;
			if (compare_word(file_words[file_index], lib_words[lib_index]))
				score += 1.0f;
			else
				score -= 1.0f;
		}
	}
	std::cout << std::setw(10) << "Paper:";
	// 输出 Paper 部分
	// 是否需要补齐
	int k = file_low.count - 1;
	if (lib_file_offset < 0)
	{
		// p 表示的是较段部分的从 words 的偏移位置
		int p;
		int q;
		// file 比 lib 短, 找到比 file 相同的最后一个单词的位置，输出相差的空字符。随后填充，在此之后不再填充
		for (p = 0, q = 0; p < lib_upper.count - lib_low.count + 1 && q < file_upper.count - file_low.count + 1 && lib_file_offset != 0; ++p)
		{
			// 如果长度还存在话。否则设置最后一个的位置
			int file_index = file_words[file_low.count - 1 + q].count - 1;
			int lib_index = lib_words[lib_low.count - 1 + p].count - 1;
			if (!compare_word(file_words[file_index], lib_words[lib_index]))
			{
				// p和q处的单词不相等。原因有两个：
				/*
				1. 不相等的单词不是 q 的下一个单词，也就是两个连续匹配的单词的中间，需要按照原文显示
				2. 如果不是夹在中间，则使用 - 代替
				*/
				// <= file + abs(lib_file_offset) 判断是否与 lib 的位置相等
				int j;
				bool fnd = false;
				for (j = -lib_file_offset; j > 0; --j)
				{
					int forward_lib = lib_words[lib_low.count - 1 + p + j].count - 1;
					if (compare_word(file_words[file_index], lib_words[forward_lib]))
					{
						// 这个是需要添加 - 的
						lib_file_offset = lib_file_offset + j;
						for (int t = 0; t < j; ++t)
						{
							std::cout << std::setw(15) << '-';
							score += 0.5;// 插入了空格
						}
						fnd = true;
						break;
					}
				}
				// 夹在中间的
				if (!fnd)
				{
					std::cout << std::setw(15) << file_words[file_index].word;
					++q;
					score -= 1.0f;
				}
			}
			else
			{
				// 比对相同
				score += 1.0f;
				std::cout << std::setw(15) << file_words[file_index].word;
				++q;
			}
		}
		if (lib_file_offset == 0)
			k = file_words[file_low.count - 1 + q].count - 1;
		else
			k = file_words[file_low.count - 1 + q - 1].count - 1;
	}


	for (; k <= file_upper.count - 1; ++k)
	{
		std::cout << std::setw(15) << file_words[k].word;
		if (offset_backup < 0)
			score += 1.0f;
	}

	std::cout << std::endl;
	std::cout << std::setw(10) << "Lib:";
	// 输出 Lib 部分
	// 是否需要补齐
	k = lib_low.count - 1;
	if (lib_file_offset > 0)
	{
		// p 表示的是较段部分的从 words 的偏移位置
		int p;
		int q;
		// file 比 lib 短, 找到比 file 相同的最后一个单词的位置，输出相差的空字符。随后填充，在此之后不再填充
		for (p = 0, q = 0; p < lib_upper.count - lib_low.count + 1 && q < file_upper.count - file_low.count + 1 && lib_file_offset != 0; ++q)
		{
			// 如果长度还存在话。否则设置最后一个的位置
			int file_index = file_words[file_low.count - 1 + q].count - 1;
			int lib_index = lib_words[lib_low.count - 1 + p].count - 1;
			if (!compare_word(file_words[file_index], lib_words[lib_index]))
			{
				// p和q处的单词不相等。原因有两个：
				/*
				1. 不相等的单词不是 q 的下一个单词，也就是两个连续匹配的单词的中间，需要按照原文显示
				2. 如果不是夹在中间，则使用 - 代替
				*/
				// <= file + abs(lib_file_offset) 判断是否与 lib 的位置相等
				int j;
				bool fnd = false;
				for (j = lib_file_offset; j > 0; --j)
				{
					int forward_file = file_words[file_low.count - 1 + q + j].count - 1;
					if (compare_word(file_words[forward_file], lib_words[lib_index]))
					{
						// 这个是需要添加 - 的
						lib_file_offset = lib_file_offset - j;
						for (int t = 0; t < j; ++t)
						{
							std::cout << std::setw(15) << '-';
							score += 0.5f;// 插入了空格
						}
						fnd = true;
						break;
					}
				}
				// 夹在中间的
				if (!fnd)
				{
					score -= 1.0f;
					std::cout << std::setw(15) << lib_words[lib_index].word;
					++p;
				}
			}
			else
			{
				std::cout << std::setw(15) << lib_words[lib_index].word;
				++p;
				score += 1.0f;
			}
		}
		if(lib_file_offset == 0)
			k = lib_words[lib_low.count - 1 + p].count - 1;
		else
			k = lib_words[lib_low.count - 1 + p - 1].count - 1;
	}

	for (; k <= lib_upper.count - 1; ++k)
	{
		std::cout << std::setw(15) << lib_words[k].word;
		if (offset_backup > 0)
			score += 1.0f;
	}
	std::cout << std::endl;

	// 输出比较的结果
	return score / total;
}
