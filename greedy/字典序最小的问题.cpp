#include "stdio.h"
#include "string.h"
int main()
{
	char *chs="ACDBCB";
	char tar[2000];
	int pos=0;
	int get;
	int N=6;
	int b=0;
	int t=strlen(chs)-1;
	for(;pos<N;++pos)
	{
		//但是你需要考虑末尾与开头相同的情况
		/*
		if(chs[b]>chs[t])
		{
			tar[pos]=chs[t--];
		}
		else
		{
			tar[pos]=chs[b++];
		}
		*/ 
		bool left=false;
		//逐步向内比较 知道找出不相同的 然后设置标志 
		for(int i=0;b+i<t;++i)
		{
			if(chs[b+i] < chs[t-i])
			{
				left=true;
				break;
			}
			else
			{
				if(chs[b+i] > chs[t-i])
				{
					left=false;
					break;
				}
			}
		}
		if(left)
			tar[pos]=chs[b++];
		else 
			tar[pos]=chs[t--];
	}
	tar[pos]='\0';
	printf("%s",tar);
	return 0;
}
