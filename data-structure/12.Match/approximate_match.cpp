#include <string>
#include "match.h"
int main(int argc, char const *argv[])
{
    // 未完成. <算法之美>
    std::string s = "bcdabcdef";
    std::string p = "abcdefbcd";
    std::cout << find_using_BMH(s.c_str(), p.c_str(), s.size(), p.size());
    huisu_mohu_alogrithms(s.c_str(), p.c_str(), s.size(), p.size());

    return 0;
}
