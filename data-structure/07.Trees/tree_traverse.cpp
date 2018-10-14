
#include "../stdafx.h"
#include "../BinaryTree.h"
int main(int argc, char const *argv[])
{
    BinaryTreeList<int> li(32);
    li.insert_left(li.getRoot(), 5);
    li.insert_left(li.getRoot(), 6);
    li.insert_left(li.getRoot()->getLeftchild(), 7);
    li.insert_right(li.getRoot()->getLeftchild(), 10);
    li.insert_right(li.getRoot(), 55);
    li.insert_right(li.getRoot(), 66);
    li.insert_left(li.getRoot()->getRightchild(), 22);
    //前序遍历
    cout << "Preorder traverse : ";
    li.PreOrder(li.getRoot());
    cout << endl
         << "Preorder traverse using stack : ";
    li.PreOrder_Stack(li.getRoot());
    cout << "Inorder traverse : ";
    li.InOrderTraverse(li.getRoot());
    cout << endl
         << "Inorder traverse using stack : ";
    li.InOrderTraverse_Stack(li.getRoot());
    cout << "Post traverse : ";
    li.PostOrderTraverse(li.getRoot());
    cout << endl
         << "Postorder taverse using stack :";
    li.PostOrderTraverse_Stack(li.getRoot());
    cout << "LevelOrder Traverse : ";
    li.LevelOrderTraverse(li.getRoot());
    //线索化
    cout << "Threading:"<<endl;
    cout << endl;
    //li.PreOrderThread(li.getRoot());
    //li.Display_PreOrderThread(li.getRoot());
    li.PostOrderThread(li.getRoot());
    li.Display_PostOrderThread(li.getRoot());

    //li.InOrderThread(li.getRoot());
    //li.Display_InOrderThread(li.getRoot());
    //li.Display_PreOrderThread(li.getRoot());

    /* 普通的树
TreeList<int> li(66);
li.insertChild(li.getRoot(), 5);
li.insertChild(li.getRoot(), 6);
li.insertChild(li.getRoot(), 7);
li.insertChild(li.getRoot()->getLeftchild(), 99);
auto l = li.getRoot()->getLeftchild();
li.clear();
*/
    return 0;
}
