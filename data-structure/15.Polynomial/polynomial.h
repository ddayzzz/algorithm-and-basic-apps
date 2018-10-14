#pragma once
#include "../stdafx.h"
#include "../00.Algorithms_Design_In_C_Common/list.h"
int max1(int a, int b) { return a > b ? a : b; }
/*���ڱ������ʽ��ϵ���Ľṹ��
ʹ��ʱ��һ��Ҫ��initpolynomal����ʼ��
ʹ�����ʱ��ʹ��free_poly�ͷŷ������Դ
*/
struct polynomial
{
	Node nd;//�������ϵ��
	int maxdegree;//�涨����ʽ������
	int unknownvalue = 0;//δ֪����ֵ
	//���ڳ�ʼ������ʽ δ֪����ֵ��ϵ���������Ԫ�ص�ַ������
	void initpolynomal(int unknown, int *addofxishu, int num)
	{
		//��ʼ�����õĳ�Ա
		unknownvalue = unknown;
		maxdegree = num;
		//firstxishuadd = addofxishu;
		int c;
		nd.makeempty();//��ʼ��һ���µĽڵ�
		Node::Position pos = nd.head;
		for (c = 1; c <= num; ++c)
		{
			nd.insert(*addofxishu++, pos);//����ϵ��
			pos = pos->next;//����λ��
		}
		

	}
	//���ڳ�ʼ������ʽ������ʹ��ָ����ϵ��Ĭ��ֵ�����ڳ�ʼ���������Ķ���ʽ�� ������δ֪����ֵ��ϵ��Ĭ��ֵ
	void initpolynomal_zero(int num,int unknown,int xishu=1)
	{
		//��ʼ����Ա
		maxdegree = num;
		unknownvalue = unknown;
		int c;
		nd.makeempty();//�����µĽڵ�
		Node::Position pos = nd.head;
		for (c = 1; c <= num; ++c)
		{
			nd.insert(xishu, pos);
			pos = pos->next;
		}
	}
	//ʹ�ӷ���������Ҳ������ĳ��ȱ���һ�� ����С��ϵ������ʼ��Ϊ1 ����:�Ҳ�����
	void make_p1_p2_size_equal(polynomial *p2)
	{
		int i;
		int maxcount = max1(maxdegree, p2->maxdegree);
		if (maxdegree > p2->maxdegree)
		{
			Node *pos = p2->nd.last(&p2->nd);
			for (i = p2->maxdegree; i < maxcount; ++i)
			{
				p2->nd.insert(0, pos);
				pos = pos->next;
			}
		}
		else
		{
			if (maxdegree < p2->maxdegree)
			{
				Node *pos = nd.last(&p2->nd);
				for (i = maxdegree; i < maxcount; ++i)
				{
					nd.insert(0, pos);
					pos = pos->next;
				}
			}
		}
	}
	//���ж���ʽ�ӷ����� �Ҳ�������Ŀ��д��Ķ���ʽ��ַ��δ֪����ֵ�����������Ҳ�������ͬ��
	void plus_xishuofpoly( polynomial *p2,polynomial *dest, int unknown)
	{
		int i;
		int maxcount = max1(maxdegree, p2->maxdegree);
		make_p1_p2_size_equal(p2);
		dest->initpolynomal_zero(maxcount,unknown);
		Node::Position pos = dest->nd.head->next;

		Node::Position pos1 = nd.head->next;
		Node::Position pos2 = p2->nd.head->next;
		for (i = 0; i < maxcount; ++i)
		{
			pos->data= (pos1->data + pos2->data);
			pos1 = pos1->next;
			pos2 = pos2->next;
			pos = pos->next;
		}
		//dest->nd.print_all_elements();
	}
	// ���ж���ʽ�˷����� �Ҳ�������Ŀ��д��Ķ���ʽ��ַ��δ֪����ֵ�����������Ҳ�������ͬ��
	void multiply_xishuopoly(polynomial *p2, polynomial *dest,int unknown)
	{
		int i, k;
		int maxexp = maxdegree + p2->maxdegree;
		dest->initpolynomal_zero(maxexp - 1, unknown, 0);//�˷���Ķ���ʽ������������������ָ��֮�� -1
		Node::Position pp1 = nd.head->next;
		Node::Position pp2;
		for (i = 0; i < maxdegree; ++i)
		{
			pp2 = p2->nd.head->next;
			for (k = 0; k < p2->maxdegree; ++k)
			{
				*dest->nd.get_position_byindex(k + i) += pp1->data * pp2->data;
				pp2 = pp2->next;
			}
			pp1 = pp1->next;
		}
	}
	//��ʾ����ʽ�ĺ�δ֪���ı��ʽ �����ַ���δ֪������ʽ �����β�ַ����˸��ת������ ��ô�ͻ��ڽ�β�ַ�ǰ���һ���ո�����ɾ��
	void show_unary_mode(char endchar = '\n', char c = 'X')
	{
		/* ԭ����
		1.�������ʾδ֪��
		2.һ�����ʾ1�η�
		3.����ϵ��Ϊ0�������ʾ��
		4.����̫���ܻ�Ϊ0������֤��
		
		*/
		Node::Position pos = nd.head->next;
		int cnt = 0;
		char previous_symbol = '\0';//���������ķ���
		bool firstobj = true;//�Ƿ��ǵ�һ���� ���ڴ����Ƿ���ʾ��������
		int val;
		if (pos == NULL) { return; }//���������Ԫ��

		
		while (pos != NULL)
		{ 
			val = pos->data;
			if (val > 0)
			{
				if (firstobj == true)//��������� �����ǵ�һ������ ��ô�Ͳ���ʾ�������� ����������һ��������
				{
					previous_symbol = '\0';
					firstobj = false;//��һ�ξͱ�����ʾ����
				}
				else
				{
					previous_symbol = '+';//�ⲻ�ǵ�һ������ ��Ŷ����ʾ����
				}
			}
			else
			{
				if (val < 0)
				{
					previous_symbol = '-'; val = -val;//��ʾ���� ͬʱvalȡ����ֵ
					firstobj = false;//ͬʱҲ�رյ�һ���ʾ���ŵĲ���
				}
				else
				{
					if (val == 0)
					{
						if (pos->next == NULL)//�����һ��Ϊ0 ͬʱ�Ժ�û������ ��ô����ʾ0
						{
							printf("0");
							break;
						}
						else
						{
							//���Ϊ0 �Ҳ������һ����ôֱ������ ����ʾ
							++cnt;
							pos = pos->next;
							continue;
						}
					}
				}
			}
			//��ȷ����ʾ��val �Լ�����
			switch (cnt)
			{
			case 0:
				if(previous_symbol !='\0'){ printf("%c%d", previous_symbol, val); }else{ printf("%d", val); }//�����ķ���Ϊ\0��ô�Ͳ���ʾ��
				break;
			case 1:
				 if(previous_symbol !='\0')
				 { 
					 if (val != 1)
					 {
						 printf("%c%d%c", previous_symbol, val, c);
					 }
					 else {
						 printf("%c%c", previous_symbol, c);
					 }
				 }
				 else
				 { 
					 if (val != 1)
					 {
						 printf("%d%c", val, c);
					 }
					 else
					 {
						 printf("%c", c);
					 }
				 }
				break;
				
			default:
				if (cnt == maxdegree - 1)
				{
					//Ĭ�ϲ���ʾ\0�ַ�
					if (endchar == '\b')
					{
						//������˸� ��ô������һ���ո�����ɾ��  ������
						if (val == 1)//ϵ��Ϊ1����ʾ
						{
							if (previous_symbol != '\0')
							{
								printf("%c%c^%d %c", previous_symbol, c, cnt, endchar);
							}
							else
							{
								printf("%c^%d %c", c, cnt, endchar);
							}
						}
						else
						{
							if (previous_symbol != '\0')
							{
								printf("%c%d%c^%d %c", previous_symbol, val, c, cnt, endchar);
							}
							else
							{
								printf("%d%c^%d %c", val, c, cnt, endchar);
							}
						}
					}
					else
					{
						if (val == 1)
						{
							if (previous_symbol != '\0')
							{
								printf("%c%c^%d%c", previous_symbol, c, cnt, endchar);
							}
							else
							{
								printf("%c^%d%c", c, cnt, endchar);
							}
						}
						else
						{
							if (previous_symbol != '\0')
							{
								printf("%c%d%c^%d%c", previous_symbol, val, c, cnt, endchar);
							}
							else
							{
								printf("%d%c^%d%c", val, c, cnt, endchar);
							}
						}
					}
				}
				else
				{
					if (previous_symbol != '\0')
					{
						printf("%c%d%c^%d", previous_symbol, val, c, cnt);
					}
					else
					{
						printf("%d%c^%d", val, c, cnt);
					}
				}
				break;
			}
			++cnt;//��������
			pos = pos->next;//���µ�ַ
		}
	}
	//���ؼ���õ���ֵ��δ֪����ֵ�ɳ�ʼ��������
	int show_calced_value()
	{
		Node::Position pos = nd.head->next;
		int res = 0;
		int val;
		int cnt = 0;
		if (pos == NULL) { return 0; }
		while (pos != NULL)
		{
			val = pos->data;
			res = res + val*(power(unknownvalue, cnt));
			pos = pos->next;
			++cnt;
		}
		return res;
	}
	//�ͷ���Դ
	void free_poly()
	{
		nd.free_list();
		//free(nd.head);
	}
	//����e��X�η�
	int power(int e,int x)
	{
		if (x == 0) return 1;
		int val = e;
		int i;
		for (i = 1; i < x; ++i)
		{
			val *= e;
		}
		return val;
	}
};