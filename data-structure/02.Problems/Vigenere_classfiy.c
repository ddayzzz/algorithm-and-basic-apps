//弗吉尼亚加密法问题
#include <stdio.h>
//解法1 索引
//弗吉尼亚加密法问题
//解法1 索引
char* Vigenere_classfiy( char *tobedone, const int *key, int sizeoftobedone, int sizeofkey)
{
	if (sizeofkey <= sizeoftobedone)
	{
		int i = 0;
		int j = 0;
		for (; j < sizeoftobedone; ++j)
		{
			//设置偏移的位数
			int ascii;
			if (i >= sizeofkey)
			{
				i = 0;
			}
			ascii = tobedone[j] + key[i++];
			if (ascii > 'z')
			{
				ascii = 'a' + ascii - 'z'-1;
			}
			tobedone[j] = ascii;
		}
		
	}
	return tobedone;
}
int main()
{
    char ch[] = { 'y','o','u','a','r','e','i','n','d','a','n','g','e','r','\0' };
    int key[6] = { 6,9,8,5,9,2 };
    Vigenere_classfiy(ch, key, 15, 6);
    printf("%s\n", ch);
}