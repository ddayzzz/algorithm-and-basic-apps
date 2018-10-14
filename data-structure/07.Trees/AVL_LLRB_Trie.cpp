#include "../BinarySearchTree.hpp"
#include "../Tree.hpp"
int main()
{
    // 普通二叉查找树
    BinarySearchTree<int> bt(18);
    auto j = bt.getRoot();
    //bt.insert(j, 18);
    bt.insert(j, 19);
    bt.insert(j, 22);
    bt.insert(j, 17);
    bt.insert(j, 11);
    bt.insert(j, 10);
    bt.insert(j, 15);
    bt.insert(j, 13);
    bt.remove(j, 11);

    printf("LLRB and AVL\n");
    RBTree<int> rb(1);
    AVLTree<int> avl(1);
    for (int i = 2; i <= 10; ++i)

    {
        rb.insert(i);
        avl.insert(i);
    }
    printf("AVL\n");
    avl.InOrderTraverse(avl.getRoot());
    printf("\nLLRB\n");
    rb.InOrderTraverse(rb.getRoot());
    printf("\n");
    // Trie 树
    // trie树的使用
    int a, b;
    a = (b = 4) = 5;
    TrieTree<> ch;
    ch.insert("abc");
    ch.insert("abcdf");
    ch.insert("abc");
    ch.insert("abcdef");
    ch.insert("abcde");
    ch.insert("bcd");
    ch.insert("bcb");
    string d("abcdef");
    ch.printAll();
    cout << "ab前缀：";
    ch.printPre("a");
}