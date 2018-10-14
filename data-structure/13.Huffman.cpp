#include "stdafx.h"
#include "Huffman.h"
#include <string>
int main()
{
    // 哈夫曼编码的使用
    const char *c;
    int sz;
    cout << "请输入要编码的序列：";
    std::string s;
    cin >> s;
    c = s.c_str();
    sz = s.size();
    Huffman hmf;                     //哈夫曼对象
    Huffman::Charfrenquent hmf_freq; //字符出现的频数
    hmf.calcFrenquentofChars(c, sz, hmf_freq);
    HuffmanTreeNodeBase *tree = hmf.buildHuffmanTree(hmf_freq); //得到地哈夫曼树
    Huffman::CharMap hmf_map;                                   //哈夫曼映射表
    hmf.genrateCode(tree, hmf_map, hmf_freq);
    delete tree;
    int orgsz = 0;
    int zipsz = 0;

    //计算应该的长度
    int cnt = 0;
    int weight = 1;
    int t = hmf_map.size();
    while (1)
    {
        if (t == 1)
        {
            cnt = 1;
            break;
        }
        if (t - weight <= 0)
        {
            break;
        }
        else
        {
            weight *= 2;
            ++cnt;
        }
    }
    //cnt就应该要编码的二进制的位数
    orgsz = sz * cnt;
    cout << endl
         << "获得的哈夫曼编码映射为：" << endl;
    for (auto i = hmf_map.cbegin(); i != hmf_map.cend(); ++i)
    {
        cout << "[" << i->first << "]=";
        for (int j = 0; j < (i->second).size(); ++j)
        {
            cout << i->second[j];
        }
        cout << endl;
    }
    std::string hfm_encodedstr; //这个表示哈夫曼编码后的二进制
    cout << "得到的哈夫曼字符编码为：";
    for (int i = 0; i < sz; ++i)
    {
        for (int j = 0; j < hmf_map[c[i]].size(); ++j)
        {
            cout << hmf_map[c[i]][j];
            hfm_encodedstr.push_back(hmf_map[c[i]][j] + '0');
            ++zipsz; //压缩后大小计算
        }
        cout << " ";
    }
    cout << endl
         << "原始编码长度：" << orgsz << "，编码后长度：" << zipsz << " 压缩率为：" << (static_cast<float>(zipsz) / orgsz) << endl;
    cout << "解码后：" << hmf.deCoding(hmf_map, hfm_encodedstr) << endl; //重新解码
}