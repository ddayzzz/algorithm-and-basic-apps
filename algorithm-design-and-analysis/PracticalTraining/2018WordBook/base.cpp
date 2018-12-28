#include "base.h"

void Vocabulary::do_insert_word(const std::string & word)
{
	auto &&fnd = std::find_if(_word_count.begin(), _word_count.end(), [&word](const Word &obj) {return word == obj.word; });
	if (fnd == _word_count.end())
	{
		// 新的单词
		Word wd{ word, 1 };
		_word_count.emplace_back(wd);
	}
	else
	{
		// 已经存在的代词
		fnd->count += 1;
	}
}

Vocabulary::Vocabulary(const std::string & filepath)
{
	std::ifstream stream(filepath);
	std::string word;
	char ch;
	while (!stream.eof())
	{
		// 没有EOF
		stream >> std::noskipws >> ch;
		// 1. 当前的字符是空 对齐 换行 - ' 认为单词的结束
		if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '-' || ch == '\'')
		{
			if (!word.empty())
			{
				do_insert_word(word);
				word = std::string();
			}
			
		}
		// 2. A-Z a-z
		else if (isalpha(ch))
		{
			if (isupper(ch))
				ch += 32;
			word.push_back(ch);
		}
	}
	if (!word.empty())
	{
		do_insert_word(word);
		word = std::string();
	}
}

void Vocabulary::print(int column)
{
	// column =0, column = 1 分别按照 单词和词频排序
	if (column == 0)
	{
		std::cout << "Sort by Alphabet:" << std::endl;
		MergeSort<Word>(_word_count, [](const Word &lhs, const Word &rhs)->bool{return lhs.word <= rhs.word; });
		for (auto &&word : _word_count)
		{
			std::cout << std::setw(20) << word.word << "\t" << std::setw(3) << word.count << std::endl;
		}
	}
	else
	{
		std::cout << "Sort by Count:" << std::endl;
		// 统计词频
		MergeSort<Word>(_word_count, [](const Word &lhs, const Word &rhs)->bool {return lhs.count > rhs.count; });
		for (auto &&word : _word_count)
		{
			std::cout << std::setw(20) << word.word << "\t" << std::setw(3) << word.count << std::endl;
		}
	}
}


