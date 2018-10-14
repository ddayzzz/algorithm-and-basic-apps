#include<cstdio>
#include<cstring>
using namespace std;

const int maxn=40;
int n,m,a[maxn+20],b[maxn+20],c[maxn+20];
int f[maxn+20][10][maxn+20];

void multi(int d[],int p[],int q[])
{
  int i,j,k,last=0;
  d[0]=p[0]+q[0]-1;
  for(k=1;k<=d[0];k++)
    {
      for(d[k]=last,i=1;i<=p[0];i++)
        if(k+1-i>=1 && k+1-i<=q[0])d[k]+=p[i]*q[k+1-i];
      last=d[k]/10,d[k]%=10;
	} 
  if(last>0)d[++d[0]]=last;
}

void MAX(int p[],int q[])
{
  int i;
  if(p[0]>q[0])return;
  if(p[0]==q[0])
    {
      for(i=p[0];i>=1;i--)
        {
          if(p[i]>q[i])return;
          if(p[i]<q[i])break;
		}
	  if(i<1)return;
	}
  for(i=0;i<=q[0];i++)p[i]=q[i];
}

int main()
{
  int i,j,k,x;  
  scanf("%d%d\n",&n,&m);
  for(i=1;i<=n;i++)a[i]=getchar()-'0';
  for(i=1;i<=n;i++)
    for(f[i][0][0]=i,j=1;j<=i;j++)
      f[i][0][j]=a[i+1-j];
      
  for(k=1;k<=m;k++)
    for(i=k+1;i<=n;i++)
      for(j=k;j<i;j++)
        {
          for(b[0]=0,x=i;x>j;x--)b[++b[0]]=a[x];
          multi(c,f[j][k-1],b);
          MAX(f[i][k],c);
		}
  for(i=f[n][m][0];i>=1;i--)printf("%d",f[n][m][i]);
  return 0; 
}
