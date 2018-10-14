#include "../BinarySearchTree.hpp"

int main()
{
    // 字典的使用
    Dictionary di("llrb_wordlist.txt");
    string sl;

    string f;
    string res;
    while (1)
    {
        cout << "输入你想查的单词(输入q退出)：";
        cin >> sl;
        if (sl == string("q") || sl == string("Q"))
            break;
        res = di.findChinese(sl);
        if (res.empty())
        {
            cout << "没有结果。是否为他添加到字典中？(Y/N)";
            cin >> f;
            if (f == string("Y") || f == string("y"))
            {

                string chs;
                cout << "请输入这个单词的中文意思：";
                getchar(); //删除掉多余的回车
                char t;
                while ((t = getchar()) != '\n')
                    chs.push_back(t); //主要是为了可以不输入空格
                di.insert(sl, chs);
                di.insertToFile(sl, chs, "llrb_wordlist.txt");
                cout << "插入成功！" << endl;
            }
        }
        else
        {
            cout << "中文意思为：" << res << endl;
        }
    }
}