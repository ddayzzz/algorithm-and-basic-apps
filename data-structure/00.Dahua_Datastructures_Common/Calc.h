#pragma once
#include "../stdafx.h"
#include "LinkStack.h"
//这是一个计算器的实现 大小不包括结尾字符
char *infixToSuffix(char *arr, int size)
{
	//将中缀式转换为逆波兰式
	LinkStack ops;
	ops = create_empty_LinkStack();
	char *res = (char*)malloc(size * sizeof(char) + 1); int index = 0;
	//规律 括号有最高优先级 遇到操作符 弹出元素条件 栈顶元素优先级低于或等于该运算符为止 若x的优先级大于栈s1栈顶运算符优先级，则将x直接压入栈s1。否者，将栈s1的栈顶运算符弹出，压入栈s2中，直到栈s1的栈顶运算符优先级别低于（不包括等于）x的优先级，或栈s2的栈顶运算符为'('，此时再则将x压入栈s1;
	int i;
	for (i = 0; i < size;)
	{
		if (arr[i] != ' ')
		{
			switch (arr[i])
			{
			case '(':
				push_LinkStack('(', ops); ++i; break;
			case ')':
				if (ops->next != NULL)
				{
					while (ops->next->data !='(')
					{
						res[index++]=topandpop_linkstack(ops);
					}
					topandpop_linkstack(ops);
				}
				++i;
				break;
			case '+':
				if (ops->next)
				{
					while (ops->next !=NULL && ops->next->data !='(')
					{
						res[index++] = topandpop_linkstack(ops);
					}
					push_LinkStack('+', ops);
				}
				else { push_LinkStack('+', ops); }
				++i;
				break;
			case '-':
				if (ops->next)
				{
					while (ops->next != NULL && ops->next->data != '(')
					{
						res[index++] = topandpop_linkstack(ops);
					}
					push_LinkStack('-', ops);
				}
				else { push_LinkStack('-', ops); }
				++i;
				break;
			case '*':
				if (ops->next)
				{
					while (ops->next != NULL && ops->next->data != '(')
					{
						if (ops->next->data == '+' || ops->next->data == '-') { break; }
						else{ res[index++] = topandpop_linkstack(ops); }
					}
					push_LinkStack('*', ops);
				}
				else { push_LinkStack('*', ops); }
				++i;
				break;
			case '/':
				if (ops->next)
				{
					while (ops->next != NULL && ops->next->data != '(')
					{
						if (ops->next->data == '+' || ops->next->data == '-') { break; }
						else{ res[index++] = topandpop_linkstack(ops); }
					}
					push_LinkStack('/', ops);
				}
				else { push_LinkStack('/', ops); }
				++i;
				break;
			default:
				res[index++] = arr[i];
				++i;
				break;
			}
		}
	}
	while (ops->next)
	{
		res[index++] = topandpop_linkstack(ops);
	}
	res[index] = '\0';
	//free(res);
	return res;
}

