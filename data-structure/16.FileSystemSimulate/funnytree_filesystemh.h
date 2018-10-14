#pragma once
#include "../stdafx.h"
struct FileorDir
{
	char name;
	int size;
	int isfile;//是否是文件
	int isroot;//是否是文件夹
	FileorDir *sons_chain;//子文件/文件夹链
	FileorDir *brothers;//同一级别的文件夹/文件链
	//当isroot!=0时 表示是一个root
};
typedef struct FileorDir *fileobj;//文件夹 文件对象
//创建文件 或文件夹对象 是否是文件,文件名,文件大小,是否是根目录
fileobj create_fileordir(int isfile,char n,int size,int isroot =0)
{
	fileobj fo = (fileobj)malloc(sizeof(FileorDir));
	fo->name = n;
	fo->size = size;
	fo->isfile = isfile;
	fo->sons_chain = NULL;
	fo->brothers = NULL;
	fo->isroot=isroot;
	return fo;
}
//是否为root
int isroot(fileobj f)
{
	if(f == NULL)
	{
		return 0;
	}
	else
	{
		return f->isroot;
	}
}
//是否是文件
int isfile(fileobj f)
{
	if (f == NULL)
	{
		return 0;
	}
	else
	{
		return  f->isfile != 0;
	}
}
//是否是文件夹
int isdir(fileobj f)
{
	if (f == NULL)
	{
		return 0;
	}
	else
	{
		return  f->isfile == 0;
	}
}
//这个函数用于获取文件-文件(夹)-...-文件(夹)链的末端之前的元素 你可以根据需要选择遍历的方向 可以根据遍历方向选择插入的位置
//该函数的参数 文件/文件夹对象指针, 操作符 [F]从父系文件夹方向 [S]从子文件/文件夹方向 [B]从文件/文件夹对象的兄弟们方向 , 深度[-n]表示想root前进n个深度 [n] n>0 则相反
fileobj searchchain(fileobj f,char opssyb,int depth)
{
	return NULL;
}
//打印文件夹 文件的信息 偏移的位置取决于深度
void printName(fileobj f,int depth)
{
	if (f != NULL)
	{
		if (depth > 1) { printf("|"); }
		while (depth > 0)
		{
			if(depth==1){ printf("|-"); }else{ printf(" "); }
			depth--;
		}
		printf("%c\n",f->name);
	}
}
//列出文件名字的私有函数
void Listdir(fileobj f,int depth) {
	if (f != NULL)
	{
		if (depth == 0) { printf("%c\n", f->name); }else{ printName(f, depth); }
		if (isdir(f))
		{
			//printf("\n");
			fileobj sons = f->sons_chain;
			while (sons != NULL)
			{
				if (isfile(sons))
				{
					printName(sons, depth + 1);
				}
				else
				{
					//printf("\n");
					Listdir(sons, depth + 1);
				}
				sons = sons->brothers;
			}
			
			
		}
		else
		{
			//printName(f, depth);
		}
	}
}
//列出文件夹信息
void ListDirectory(fileobj f)
{
	Listdir(f, 0);
}
//将文件/文件夹附加到父系目录
void attachToFather(fileobj s, fileobj f)
{
	if (!isroot(s) && !isfile(f))
	{
		fileobj fo = f->sons_chain;
		if (fo == NULL)
		{
			f->sons_chain = s;
			return;
		}
		while (fo->brothers != NULL)
		{
			fo = fo->brothers;
		}
		fo->brothers = s;
	}
}
//获取文件对象在父目录下的前驱
fileobj find_prev(fileobj o, fileobj father)
{
	if (o != NULL && isdir(father))
	{
		fileobj fo = father->sons_chain;
		if (fo == o) { return father; }
		while (fo !=NULL && fo->brothers != o)
		{
			fo = fo->brothers;
		}
		return fo;
	}
	else

	{
		return NULL;
	}
}
//销毁整个根目录
void freeroot(fileobj o)
{
	if (o != NULL)
	{
		if (isfile(o))
		{
			//是文件 那么删除文件
			//printf("delete %c\n", o->name);
			free(o);
		}
		else
		{
			//文件夹 那么他的可以通过递归删除所有子文件  并同时销毁目录
			fileobj fo = o->sons_chain;
			fileobj next_temp;
			while (fo != NULL)
			{
				next_temp = fo->brothers;
				
				freeroot(fo);
				fo = next_temp;
			}
			
		}
	}
}
//删除文件/文件夹项目 文件对象, 他的父目录
void deletefileobj(fileobj o,fileobj hisfather)
{
	if (o != NULL)
	{
		//寻找前一个
		fileobj prev = find_prev(o, hisfather);
		if (prev == hisfather)
		{
			//表示删除的是第一子目录o=father->son 那么有需要修改父目录的子链
			if (isfile(o))
			{
				fileobj next = prev->sons_chain->brothers;
				prev->sons_chain = next;
				free(o);
			}
			else
			{
				fileobj next = prev->sons_chain->brothers;//获取后继
				prev->sons_chain = next;
				fileobj temp = o->sons_chain;
				fileobj after_free;//防止free(temp)之后 temp无效
				while (temp != NULL)
				{
					after_free = temp->brothers;
					deletefileobj(temp, o);
					temp = after_free;
				}
				free(o);
			}

		}
		else
		{
			//不是从第一个子目录/文件开始的
			if (isfile(o))
			{
				fileobj next = prev->brothers->brothers;
				prev->brothers = next;
				free(o);
			}
			else
			{
				fileobj next = prev->brothers->brothers;
				prev->brothers = next;
				fileobj temp = o->sons_chain;
				fileobj after_free;//防止free(temp)之后 temp无效
				while (temp != NULL)
				{
					after_free = temp->brothers;
					deletefileobj(temp, o);
					temp = after_free;
				}
				free(o);
			}
		}
	}
}
void print_NameandSize(fileobj o, int depth,int size)
{
	int cnt = 0;
	while (cnt < depth)
	{
		printf("  ");
		++cnt;
	}
	printf("%c,size is \"%d\"\n", o->name,size);
}
int Listdir_nameandsize(fileobj f, int depth)
{
	//后续遍历
	if (f != NULL)
	{
		int totalsize = 0;
		if (isfile(f))
		{
			print_NameandSize(f, depth,f->size);
			totalsize+= f->size;
		}
		else
		{
			if (isdir(f))
			{
				fileobj sons = f->sons_chain;
				while (sons !=NULL)
				{
					if (isfile(sons))
					{
						print_NameandSize(sons, depth + 1, sons->size);
						totalsize += sons->size;
						
					}
					else
					{
						totalsize += Listdir_nameandsize(sons, depth + 1);
					}
					sons = sons->brothers;
				}
				print_NameandSize(f, depth,totalsize);
			}
		}
		return totalsize;
	}
}
void ListDirectory_nameandsize(fileobj f)
{
	Listdir_nameandsize(f, 0);
}