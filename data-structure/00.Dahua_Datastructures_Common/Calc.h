#pragma once
#include "../stdafx.h"
#include "LinkStack.h"
//����һ����������ʵ�� ��С��������β�ַ�
char *infixToSuffix(char *arr, int size)
{
	//����׺ʽת��Ϊ�沨��ʽ
	LinkStack ops;
	ops = create_empty_LinkStack();
	char *res = (char*)malloc(size * sizeof(char) + 1); int index = 0;
	//���� ������������ȼ� ���������� ����Ԫ������ ջ��Ԫ�����ȼ����ڻ���ڸ������Ϊֹ ��x�����ȼ�����ջs1ջ����������ȼ�����xֱ��ѹ��ջs1�����ߣ���ջs1��ջ�������������ѹ��ջs2�У�ֱ��ջs1��ջ����������ȼ�����ڣ����������ڣ�x�����ȼ�����ջs2��ջ�������Ϊ'('����ʱ����xѹ��ջs1;
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

