#pragma once
#include <fstream>
#include <sstream>
#include <algorithm>
#include "base.h"
enum class From
{
	Same,
	Left,
	Top
};
void compare_para(const char *filepath, const char *libfilepath);

float compare(const std::string &total_files,
	const std::vector<Word> &file_words,
	const std::string &total_lib,
	const std::vector<Word> &lib_words);
// std::vector<int> &end_of_para 保存单词的之后存在一个断点.
std::string read_word_seq(const char *path, std::vector<Word> &seq, std::vector<int> *end_of_para);

bool compare_word(const Word &lhs, const Word &rhs);

void output_the_same_seq(From **arr, int v, int h, const std::vector<Word> &libs, const std::vector<Word> &files, std::vector<std::pair<Word, Word>> &common_seq);

float print(const std::string & lib, const std::string & files, const std::vector<Word> &lib_words, const std::vector<Word> &file_words, const std::vector<std::pair<Word, Word>> &words);
