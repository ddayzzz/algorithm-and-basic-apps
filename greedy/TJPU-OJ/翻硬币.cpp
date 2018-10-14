#include "stdio.h"
#include "string.h"
char src[1002];
char dest[1002];
int main()
{
	scanf("%s",&src[1]);
	scanf("%s",&dest[1]);
	int i=1;
	int len=strlen(&src[1]);
	int minstep=0;
	for(;i<len;++i)
	{
		if(src[i]==dest[i])
			continue;
		int j=i+1;
		if(src[i]=='*')
			src[i]='o';
		else src[i]='*';
		
		if(src[j]=='*')
			src[j]='o';
		else src[j]='*';++minstep;
	}
	printf("%d",minstep);
	return 0;
}
