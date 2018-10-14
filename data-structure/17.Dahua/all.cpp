// 大话数据结构1.cpp : 定义控制台应用程序的入口点。
//

#include "../stdafx.h"
#include "../00.Dahua_Datastructures_Common/StaticList.h"
#include "../00.Dahua_Datastructures_Common/DoubleList.h"
#include "../00.Dahua_Datastructures_Common/SharedStack.h"
#include "../00.Dahua_Datastructures_Common/LinkStack.h"
#include "../00.Dahua_Datastructures_Common/Calc.h"
#include "../00.Dahua_Datastructures_Common/LinkQueue.h"
#include "../00.Dahua_Datastructures_Common/String.h"
int main()
{
	/* 静态链表的使用
	CursorList l;
	l = initialize_cursorlist(10);
	insert_cursorlist(l, 1, 5);
	insert_cursorlist(l, 2, 9);
	insert_cursorlist(l, 3, 19);
	insert_cursorlist(l, 4, 29);
	StaticList *s = &l[2];
	insert_cursorlist(l, 5, 39);
	print_allelements(l);
	free(l);
	s->cursor;
	*/
	/*双端链表的使用
	DoubleList dl;
	dl = initialize_DoubleList();
	insert_DoubleList(dl, 1, 3);
	insert_DoubleList(dl, 2, 5);
	insert_DoubleList(dl, 3, 6);
	insert_DoubleList(dl, 4, 69);
	print_DoubleList_prior(dl);
	printf("-----------");
	delete_DoubleList(dl, 3);
	print_DoubleList_next(dl);
	auto df = dl->next->next;
	free_DoubleList(dl);
	//print_DoubleList_next(dl);
	*/
	/* 共享的栈使用
	SharedStack s;
	s=create_sharedStack(6);
	push_sharedStack(5, s, 1);
	push_sharedStack(6, s, 1);
	push_sharedStack(7, s, 1);
	push_sharedStack(8, s, 1);
	push_sharedStack(9, s, 2);
	push_sharedStack(10, s, 2);
	push_sharedStack(12, s, 2);
	print_allelemaentsinSharedStack(s);

	pop_sharedStack(s, 1);
	popandtop_sharedStack(s, 2);

	print_allelemaentsinSharedStack(s);
	free_sharedStack(s);
	*/
	/*链栈的使用
	LinkStack li;
	li = create_empty_LinkStack();
	push_LinkStack(5,li);
	push_LinkStack(6, li);
	push_LinkStack(66, li);
	push_LinkStack(666, li);
	topandpop_linkstack(li);
	auto i = li->next->next;
	push_LinkStack(66666, li);
	print_all_linkstack(li);
	free_all_linkstack(li);
	*/
	//char c[] = { '1','+','2','*','3','+','(','4','*','5','+','6',')','*','7','\0' };// { '9', '+', '(', '3', '-', '1', ')', '*', '3', '+', '1', '/', '2' };
	//int s = sizeof(c) / sizeof(c[0]);
	//char *gff=infixToSuffix(c, s-1);
	//printf("%s", gff);
	/* 中缀式 转后缀式
	char c; int cnt = 0;
	char p[256];
	do
	{
		c = getchar();
		if (c != ' ' && c !='\n')
		{
			p[cnt++] = c;
		}
	} while (cnt <256 && c != '\n');
	p[cnt] = '\0';
	char *f=infixToSuffix(p, cnt);
	printf("            postfix is \'%s\'", f);
	
	free(f);
	*/
	/*
	LinkQueue lq;
	lq = create_empty_linkqueue();
	EnQueue_linkqueue(lq, 1);
	EnQueue_linkqueue(lq, 2);
	EnQueue_linkqueue(lq, 3);
	//printf("%d\n",DeQueue_linkqueuq(lq));
	//printf("%d\n", DeQueue_linkqueuq(lq));
	//printf("%d\n", DeQueue_linkqueuq(lq));
	destroy_allLinkQueue(lq);
	*/
	String h;
	h = create_string('\0', 5);
	int g = size_string(h);
	for(int j=1;j<=5;++j)
		push_back_string(h, '0'+j);
	printf("%s", h->first);
	insert_string(h, '6', 2);
	String h2;
	h2 = create_string('\0', 10);
	for (int j = 1; j <= 9; ++j)
		push_back_string(h2, '0'+j);
	String hh = union_string(h, h2);
	String p = create_string();
	push_back_string(p, 's');
	String hhh = create_string('2', 6);
	push_back_string(hhh, 'A');
	push_back_string(hhh, 'A');
	push_back_string(hhh, 'A');
	push_back_string(hhh, 'B');
	push_back_string(hhh, 'D');
	push_back_string(hhh, 'A');
	int a = find_string_KMP(hhh,hh);
	free_string(h);
	getchar();
    return 0;
}

