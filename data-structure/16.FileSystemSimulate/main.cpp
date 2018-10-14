#include "funnytree_filesystemh.h"

int main()
{
    ///* 模拟树状文件系统
	fileobj root, d1, d2,d3, f1, f2, f3;
	root = create_fileordir(0, 'R', 2, 1);
	d2 = create_fileordir(0, '2', 2);
	d1 = create_fileordir(0, '1', 2);
	d3 = create_fileordir(0, '3', 2, 0);
	f2 = create_fileordir(1, 'B', 6);
	f1 = create_fileordir(1, 'A', 6);
	f3 = create_fileordir(1, 'c', 6);
	attachToFather(d3, root);
	attachToFather(d1, root);
	attachToFather(d2, root);
	attachToFather(f1, d2);
	attachToFather(f2, d2);
	attachToFather(f3, d3);
	ListDirectory(root);
	//deletefileobj(d3, root);
	ListDirectory(root);
	printf("-----------------------\n");
	ListDirectory_nameandsize(root);
	freeroot(root);
}