
#include "../Hash.hpp"
// #include "../WordCheck.hpp"
int main()
{
    //HashTable<EnglishWord, decltype(EnglishWord_Hash)> dict(EnglishWord_Hash, 53);

auto lab = [](int &num)->int {return num % 10; };
HashTable<int, int(int&)> hash(lab, 13);
hash.insert(41);
hash.insert(31);
hash.insert(21);
hash.insert(22);
hash.print();
hash.insert(41);
auto j = hash.find(51);
auto i = hash.find(41);
}