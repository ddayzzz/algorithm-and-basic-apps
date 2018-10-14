#include "../ThreadBinaryTree.h"

int main()
{
    	
	///???
	ThreadBinaryTreeSearchList<int> tbtsl(20);
	tbtsl.insert(tbtsl.getRoot(), 30);
	tbtsl.insert(tbtsl.getRoot(), 10);
	tbtsl.insert(tbtsl.getRoot(), 5);
	tbtsl.insert(tbtsl.getRoot(), 15);
	tbtsl.insert(tbtsl.getRoot(), 16);
	tbtsl.insert(tbtsl.getRoot(), 17);
	tbtsl.insert(tbtsl.getRoot(), 18);
	tbtsl.insert(tbtsl.getRoot(), 33);
	tbtsl.erase(tbtsl.getRoot(), 15);
	tbtsl.Threading_InOrder();
	tbtsl.InOrder_Traverse_usingThread();
	//*/
}