#include "compare.h"

void compare_para(const char * filepath, const char * libfilepath)
{
	std::vector<Word> lib_words, file_words;
	std::vector<int> end_of_para, end_of_lib_para;
	auto &&total_files = read_word_seq(filepath, file_words, &end_of_para);
	auto &&total_lib = read_word_seq(libfilepath, lib_words, &end_of_lib_para);
	// ����ÿһ������
	int left = 0;
	int right;
	int para_index = 1;
	for (int i = 0; i < end_of_para.size(); ++i)
	{
		right = end_of_para[i];
		if (left < right)
		{
			std::cout << "Para " << para_index++ << ':' << std::endl;
			// ����һ������
			// �����µĵ�������
			std::vector<Word> file_words_seq(file_words.cbegin() + left, file_words.cbegin() + right);
			// ȥ�����λ�õ�ƫ��
			for (auto &&word : file_words_seq)
			{
				word.count = word.count - left;
			}
			// compare , ��һ������һ��lib�ľ��ӵ� ������
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
					// ����ƥ��
					std::vector<Word> lib_word_seq(lib_words.cbegin() + lib_left, lib_words.cbegin() + lib_right);
					// ȥ�����λ�õ�ƫ��
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
	// ����������� �����Ԫ����һ��С����
	//std::vector<Word> lib_words;
	//auto &&total_files = read_word_seq(filepath, file_words);
	//auto &&total_lib = read_word_seq(libfilepath, lib_words);
	// ����������е�
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
	// �� 0 �к��о����� 0 ��ʼ��
	for (int i = 0; i < hsize; ++i)
		arr[0][i] = 0;
	// ������
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
				// �����Ǹ���
				if (arr[i][j - 1] > arr[i - 1][j])
				{
					// ���
					arr[i][j] = arr[i][j - 1];
					frm[i][j] = From::Left;
				}
				else
				{
					// �ϴ�
					arr[i][j] = arr[i - 1][j];
					frm[i][j] = From::Top;
				}
			}
		}
	}
	int j = 9;
	// �ݹ��󹫹�������
	std::vector<std::pair<Word, Word>> common_seq;
	output_the_same_seq(frm, vsize -1, hsize - 1, lib_words, file_words, common_seq);
	// ��ת
	std::reverse(common_seq.begin(), common_seq.end());
	// ��ӡ
	float s = print(total_lib, total_files, lib_words, file_words, common_seq);
	// �ͷ���Դ
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
		// û��EOF
		stream >> std::noskipws >> ch;
		// 1. ��ǰ���ַ��ǿ� ���� ���� - ' ��Ϊ���ʵĽ���
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
			// �����д�д�����
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
	// �ݹ飬�ж���Դ
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
		return 0.0f; // û��ƥ��,������
	}
	// std::cout << files << std::endl;
	// ������
	float score = 0.0f;
	int total = 0;
	int j = 0;
	int je = words.size() - 1;
	// j ����ʼ�Ŀ�ʼ�ĵ���
	// ��ȡ��ͬ��λ��
	const Word &file_low = words[j].first;
	const Word &file_upper = words[je].first;
	const Word &lib_low = words[j].second;
	const Word &lib_upper = words[je].second;
	//
	int lib_file_offset = (file_upper.count - file_low.count) - (lib_upper.count - lib_low.count);
	int offset_backup = lib_file_offset;
	// �����ܹ��Ĵ���
	total = file_words.size(); // ���� file ���ʸ���
	// ������� lib_file_offset = 0
	if (lib_file_offset == 0)
	{
		int m = std::min(file_upper.count - file_low.count, lib_upper.count - lib_low.count);
		// ֱ�ӱȽ�, �����ڲ���յ����
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
	// ��� Paper ����
	// �Ƿ���Ҫ����
	int k = file_low.count - 1;
	if (lib_file_offset < 0)
	{
		// p ��ʾ���ǽ϶β��ֵĴ� words ��ƫ��λ��
		int p;
		int q;
		// file �� lib ��, �ҵ��� file ��ͬ�����һ�����ʵ�λ�ã�������Ŀ��ַ��������䣬�ڴ�֮�������
		for (p = 0, q = 0; p < lib_upper.count - lib_low.count + 1 && q < file_upper.count - file_low.count + 1 && lib_file_offset != 0; ++p)
		{
			// ������Ȼ����ڻ��������������һ����λ��
			int file_index = file_words[file_low.count - 1 + q].count - 1;
			int lib_index = lib_words[lib_low.count - 1 + p].count - 1;
			if (!compare_word(file_words[file_index], lib_words[lib_index]))
			{
				// p��q���ĵ��ʲ���ȡ�ԭ����������
				/*
				1. ����ȵĵ��ʲ��� q ����һ�����ʣ�Ҳ������������ƥ��ĵ��ʵ��м䣬��Ҫ����ԭ����ʾ
				2. ������Ǽ����м䣬��ʹ�� - ����
				*/
				// <= file + abs(lib_file_offset) �ж��Ƿ��� lib ��λ�����
				int j;
				bool fnd = false;
				for (j = -lib_file_offset; j > 0; --j)
				{
					int forward_lib = lib_words[lib_low.count - 1 + p + j].count - 1;
					if (compare_word(file_words[file_index], lib_words[forward_lib]))
					{
						// �������Ҫ��� - ��
						lib_file_offset = lib_file_offset + j;
						for (int t = 0; t < j; ++t)
						{
							std::cout << std::setw(15) << '-';
							score += 0.5;// �����˿ո�
						}
						fnd = true;
						break;
					}
				}
				// �����м��
				if (!fnd)
				{
					std::cout << std::setw(15) << file_words[file_index].word;
					++q;
					score -= 1.0f;
				}
			}
			else
			{
				// �ȶ���ͬ
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
	// ��� Lib ����
	// �Ƿ���Ҫ����
	k = lib_low.count - 1;
	if (lib_file_offset > 0)
	{
		// p ��ʾ���ǽ϶β��ֵĴ� words ��ƫ��λ��
		int p;
		int q;
		// file �� lib ��, �ҵ��� file ��ͬ�����һ�����ʵ�λ�ã�������Ŀ��ַ��������䣬�ڴ�֮�������
		for (p = 0, q = 0; p < lib_upper.count - lib_low.count + 1 && q < file_upper.count - file_low.count + 1 && lib_file_offset != 0; ++q)
		{
			// ������Ȼ����ڻ��������������һ����λ��
			int file_index = file_words[file_low.count - 1 + q].count - 1;
			int lib_index = lib_words[lib_low.count - 1 + p].count - 1;
			if (!compare_word(file_words[file_index], lib_words[lib_index]))
			{
				// p��q���ĵ��ʲ���ȡ�ԭ����������
				/*
				1. ����ȵĵ��ʲ��� q ����һ�����ʣ�Ҳ������������ƥ��ĵ��ʵ��м䣬��Ҫ����ԭ����ʾ
				2. ������Ǽ����м䣬��ʹ�� - ����
				*/
				// <= file + abs(lib_file_offset) �ж��Ƿ��� lib ��λ�����
				int j;
				bool fnd = false;
				for (j = lib_file_offset; j > 0; --j)
				{
					int forward_file = file_words[file_low.count - 1 + q + j].count - 1;
					if (compare_word(file_words[forward_file], lib_words[lib_index]))
					{
						// �������Ҫ��� - ��
						lib_file_offset = lib_file_offset - j;
						for (int t = 0; t < j; ++t)
						{
							std::cout << std::setw(15) << '-';
							score += 0.5f;// �����˿ո�
						}
						fnd = true;
						break;
					}
				}
				// �����м��
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

	// ����ȽϵĽ��
	return score / total;
}
