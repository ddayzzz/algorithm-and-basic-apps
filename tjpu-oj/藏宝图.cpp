#include <iostream>
int direct[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
int **dfsmap;
int r,c;
int dfs(int begx,int begy)
{
    int stepcount=1;
    if((begx <0 || begx >=r || begy <0 || begy >c) || dfsmap[begx][begy]==0 )
        return 0;
    for(int i=0;i<4;++i)
    {
        int tx=begx+direct[i][0];
        int ty=begy+direct[i][1];
        if(dfsmap[tx][ty])
        {
            dfsmap[tx][ty]=0;
            stepcount +=dfs(tx,ty);
        }
    }
    return stepcount;
}
int main()
{
    int row;
    int column;
    while(std::cin>>row>>column)
    {
        int **maps=new int*[row];
        for(int i=0;i<row;++i)
        {
            maps[i]=new int[column];
            for(int o=0;o<column;++o)
                std::cin>>maps[i][o];
        }
        int coutn;int maxcount=0;
        for(int i=0;i<row;++i)
        {
            for(int j=0;j < column;++j)
            {
                coutn=dfs(i,j);
                if(coutn > maxcount)
                    maxcount=coutn;
            }
        }

    }
    return 0;
}
