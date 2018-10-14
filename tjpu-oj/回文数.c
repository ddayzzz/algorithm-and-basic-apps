#include "stdio.h"
#include <iostream>
int main()
{
    int changeflag=0;
    int n;
    while(std::cin>>n)
    {
        for(int i=1;i<=9;++i)
    {
        for(int j=0;j<=9;++j)
        {
            for(int k=0;k<=9;++k)
            {
                if(2*(i+j)+k==n)
                {
                    changeflag=1;
                    printf("%d%d%d%d%d",i,j,k,j,i);
                }
            }
        }
    }

    for(int i=1;i<=9;++i)
    {
        for(int j=0;j<=9;++j)
        {
            for(int k=0;k<=9;++k)
            {
                if(2*(i+j+k)==n)
                {
                    changeflag=1;
                    printf("%d%d%d%d%d%d",i,j,k,k,j,i);
                }
            }
        }
    }
    if(!changeflag)
        printf("%d",-1);
    }
    return 0;
}
