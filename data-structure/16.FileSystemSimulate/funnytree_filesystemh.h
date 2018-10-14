#pragma once
#include "../stdafx.h"
struct FileorDir
{
	char name;
	int size;
	int isfile;//�Ƿ����ļ�
	int isroot;//�Ƿ����ļ���
	FileorDir *sons_chain;//���ļ�/�ļ�����
	FileorDir *brothers;//ͬһ������ļ���/�ļ���
	//��isroot!=0ʱ ��ʾ��һ��root
};
typedef struct FileorDir *fileobj;//�ļ��� �ļ�����
//�����ļ� ���ļ��ж��� �Ƿ����ļ�,�ļ���,�ļ���С,�Ƿ��Ǹ�Ŀ¼
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
//�Ƿ�Ϊroot
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
//�Ƿ����ļ�
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
//�Ƿ����ļ���
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
//����������ڻ�ȡ�ļ�-�ļ�(��)-...-�ļ�(��)����ĩ��֮ǰ��Ԫ�� ����Ը�����Ҫѡ������ķ��� ���Ը��ݱ�������ѡ������λ��
//�ú����Ĳ��� �ļ�/�ļ��ж���ָ��, ������ [F]�Ӹ�ϵ�ļ��з��� [S]�����ļ�/�ļ��з��� [B]���ļ�/�ļ��ж�����ֵ��Ƿ��� , ���[-n]��ʾ��rootǰ��n����� [n] n>0 ���෴
fileobj searchchain(fileobj f,char opssyb,int depth)
{
	return NULL;
}
//��ӡ�ļ��� �ļ�����Ϣ ƫ�Ƶ�λ��ȡ�������
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
//�г��ļ����ֵ�˽�к���
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
//�г��ļ�����Ϣ
void ListDirectory(fileobj f)
{
	Listdir(f, 0);
}
//���ļ�/�ļ��и��ӵ���ϵĿ¼
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
//��ȡ�ļ������ڸ�Ŀ¼�µ�ǰ��
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
//����������Ŀ¼
void freeroot(fileobj o)
{
	if (o != NULL)
	{
		if (isfile(o))
		{
			//���ļ� ��ôɾ���ļ�
			//printf("delete %c\n", o->name);
			free(o);
		}
		else
		{
			//�ļ��� ��ô���Ŀ���ͨ���ݹ�ɾ���������ļ�  ��ͬʱ����Ŀ¼
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
//ɾ���ļ�/�ļ�����Ŀ �ļ�����, ���ĸ�Ŀ¼
void deletefileobj(fileobj o,fileobj hisfather)
{
	if (o != NULL)
	{
		//Ѱ��ǰһ��
		fileobj prev = find_prev(o, hisfather);
		if (prev == hisfather)
		{
			//��ʾɾ�����ǵ�һ��Ŀ¼o=father->son ��ô����Ҫ�޸ĸ�Ŀ¼������
			if (isfile(o))
			{
				fileobj next = prev->sons_chain->brothers;
				prev->sons_chain = next;
				free(o);
			}
			else
			{
				fileobj next = prev->sons_chain->brothers;//��ȡ���
				prev->sons_chain = next;
				fileobj temp = o->sons_chain;
				fileobj after_free;//��ֹfree(temp)֮�� temp��Ч
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
			//���Ǵӵ�һ����Ŀ¼/�ļ���ʼ��
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
				fileobj after_free;//��ֹfree(temp)֮�� temp��Ч
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
	//��������
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