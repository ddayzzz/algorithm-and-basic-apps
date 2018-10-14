#include <iostream>

int main()
{
	int rabbitstatus=1;//0 for rest, 1 for moving
	char winner;
	int v1,v2,t,s,l;
	scanf("%d %d %d %d %d",&v1,&v2,&t,&s,&l);
	int rabbitx=0,totx=0;
	int countdown=t;
	int time;
	for(time=1;time <=l / v2;++time)
	{
		//check delta X
		if(rabbitstatus==0)
		{
			--countdown;
		}
		else
		{
			rabbitx+=v1*1;
		}
		totx+=v2;
		if(rabbitx ==l && totx==l)
		{
			winner='D';break;
		}
		else
		{
			if(rabbitx>=l)
			{
				winner='R';break;
			}	
			else {
			winner='T';break;
			}
		}
		if(rabbitx-totx>=s)
		{
			rabbitstatus=0;
		}
		if(countdown==0)
		{
			rabbitstatus=1;
			countdown=t;
		}
	}
	printf("%c\n%d",winner,time);
	return 0;
}
