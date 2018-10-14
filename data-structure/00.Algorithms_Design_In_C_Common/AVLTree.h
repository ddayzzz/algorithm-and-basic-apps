#pragma once
#include "../stdafx.h"
#include <cstdlib>

typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType_AVLTree;
struct AVLNode
{
	ElementType_AVLTree data;
	AVLTree left;
	AVLTree right;
	int height;
};
AVLTree make_empty_avltree()
{
	//生成一个空树
	AVLTree r = (AVLTree)malloc(sizeof(struct AVLNode));
	if (r)
	{
		r->left = NULL;
		r->right = NULL;
		r->height = 0;
		return r;
	}
	return NULL;
}
static int height_avltree(AVLTree t)
{
	if (t == NULL)
	{
		return -1;
	}
	else
	{
		return t->height;
	}
}
static int max_avltree(int a, int b)
{
	return a > b ? a : b;
}
Position find_avltree(ElementType_AVLTree x, AVLTree t);
//这个函数进行R旋转
static Position SingleRotate_withLeft_avltree(Position k2) //R型旋转
{
	Position k1; //k2是原父节点 k1是新的父节点（原父节点的右儿子） 而原父节点的右儿子8会成为新的父节点的左儿子（即原父节点）的右儿子
	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max_avltree(height_avltree(k2->left), height_avltree(k2->right)) + 1;
	k1->height = max_avltree(height_avltree(k1->left), k2->height) + 1;
	return k1; //新的子树根节点
}
//这个函数进行L旋转
static Position SingleRotate_withright_avltree(Position k1) //L旋转
{
	Position k2;//k1是原父节点 k2是新的父节点=原父节点的左子树 原理是让原中间节点（原父节点左子树）变成父节点 中间节点的右子树变成原父节点的左子树 原父节点变成中间节点的右子树
	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max_avltree(height_avltree(k1->left), height_avltree(k1->right)) + 1;
	k2->height = max_avltree(height_avltree(k2->right), height_avltree(k1));
	return k2;
}
//在左儿子的右子树上添加元素 进行LR旋转
static Position DoubleRotate_withLeft_avltree(Position k2)
{
	/*
	k2 是需要替换不平衡点 我们需要从k2的右子树开始替换 返回一个结果 存在k3中 然后对k2节点进行L旋转
	*/
	k2->left = SingleRotate_withright_avltree(k2->left);
	return SingleRotate_withLeft_avltree(k2);
}
//在右儿子的左儿子上添加元素 进行 先后RL旋转
static Position DoubleRotate_withright_avltree(Position k2)
{
	/*
	k2 是需要替换不平衡点 我们需要从k2的左子树开始替换 返回一个结果 存在k3中 然后对k2节点进行R旋转
	*/
	k2->right = SingleRotate_withLeft_avltree(k2->right);
	return SingleRotate_withright_avltree(k2);
}
void draw_pattern_avltree(int depth)
{
	int cnt = 0;
	while (cnt < depth)
	{
		printf(" ");
		++cnt;
	}
}
static void print_all_elements_avltree(Position tree, int depth = 0)
{
	if (tree == NULL)
	{
		draw_pattern_avltree(depth);
		printf("---\n");
		return;
	}
	Position p;
	if (!(tree->left) && !(tree->right))
	{
		//leaf
		draw_pattern_avltree(depth);
		printf("%d---叶子\n", tree->data);
	}
	else
	{
		draw_pattern_avltree(depth);
		printf("%d\n", tree->data);
		//node 
		print_all_elements_avltree(tree->left, depth + 1);
		print_all_elements_avltree(tree->right, depth + 1);
	}

}
Position find_min_avltree(AVLTree t)
{
	if (t != NULL)
	{
		if (t->left == NULL)
		{
			return t;
		}
		else
		{
			Position p = t;
			while (p->left != NULL)
			{
				p = p->left;
			}
			return p;
		}
	}
}
Position find_max_avltree(AVLTree t)
{
	if (t == NULL)
	{
		return NULL;
	}
	else
	{
		Position p = t;
		while (p->right)
		{
			p = p->right;
		}
		return p;
	}
}
AVLTree insert_avltree(ElementType_AVLTree e, AVLTree t)
{
	if (t==NULL)
	{
		t = (AVLTree)malloc(sizeof(struct AVLNode));
		t->data = e;
		t->left = t->right = NULL;//叶子节点
		t->height = 0;
	}
	else
	{
		if (e < t->data)
		{
			//插入的是左位置 所以不平衡应该是发生在左儿子上
			t->left = insert_avltree(e, t->left);
			//计算高度差
			if (height_avltree(t->left) - height_avltree(t->right) == 2)
			{
				if (e < t->left->data)//判断是左儿子的左右子树
					t = SingleRotate_withLeft_avltree(t);//RR 这个T就是要变成儿子节点的儿子（替换后的）这个新父亲就是原来的儿子
				else
					t = DoubleRotate_withLeft_avltree(t);//RL
			}
		}
		else
		{
			if (e > t->data)
			{
				t->right = insert_avltree(e, t->right);
				if (height_avltree(t->right) - height_avltree(t->left) == 2)
				{

					if (e > t->right->data)
						t = SingleRotate_withright_avltree(t);//LL
					else
						t = DoubleRotate_withright_avltree(t);//LR
				}
			}
		}
	}
	t->height = max_avltree(height_avltree(t->left), height_avltree(t->right))+1;
	return t;
}
AVLTree delete_avltree(ElementType_AVLTree e, AVLTree t)
{
	//寻找相等的子节点
	if (t != NULL)
	{
		if (e < t->data)
		{
			t->left=delete_avltree(e, t->left);
		}
		else
		{
			if (e > t->data)
			{
				t->right=delete_avltree(e, t->right);
			}
			else
			{
				//that is!
				if (t->left != NULL && t->right != NULL)
				{
					//总是选择右儿子的左子树的最小值点
					Position min = find_min_avltree(t->right);
					t->data = min->data;
					t->right=delete_avltree(t->data, t->right);
				}
				else
				{
					Position pos=t;
					if (t->left == NULL)//没有左儿子 就返回他的右儿子给父节点的左儿子
						t = t->right;
					else if (t->right == NULL)//没有右儿子 吧他的左儿字给父节点做右儿子
						t = t->left;
					free(pos);
				}
			}
		}
	}
	return t;
}
void free_avltree(AVLTree t)
{
	if (t != NULL)
	{
		if (t->left == NULL && t->right == NULL)
		{
			free(t);
			return;
		}
		free_avltree(t->left);
		free_avltree(t->right);
		free(t);
	}
}
