
//Memory Time 
//288K   110MS 


#include<iostream>
#include<math.h>
using namespace std;

const int island_max=1000;

int main(void)
{
	int i,j;
	double x[island_max],y[island_max];
	double num,rad;
	for(;;)
	{
		/*Input end*/
     	cin>>num>>rad;
		if(!(num&&rad))break;

		static int count=1;  //��¼case��Ŀ

		/*read in coordinate*/
		bool flag=false;
    	for(i=0;i<num;i++)
		{
	    	cin>>x[i]>>y[i];
	    	if(y[i]>rad)
			flag=true;
		}

		/*case fail*/
		if(flag)
		{
			cout<<"Case "<<count++<<": -1"<<endl;
			continue;
		}

		/*bubble sort*/
		//��������yҪ��x�������򣬲��ܼ򵥵�ʹ�� ����qsort
		double temp;
		for(i=0;i<num-1;i++)
			for(j=0;j<num-i-1;j++)
				if(x[j]>x[j+1])
				{
					temp=x[j];
					x[j]=x[j+1];
					x[j+1]=temp;
					temp=y[j];
					y[j]=y[j+1];
					y[j+1]=temp;
				}

		double left[island_max],righ[island_max];  //����Բ�ں������ϵ����ҽ���
		for(i=0;i<num;i++)
		{
			left[i]=x[i]-sqrt(rad*rad-y[i]*y[i]);
			righ[i]=x[i]+sqrt(rad*rad-y[i]*y[i]);
		}

		int radar=1;
		for(i=0,temp=righ[0];i<num-1;i++)
			if(left[i+1]>temp)
			{
				temp=righ[i+1];
				radar++;
			}
			else if(righ[i+1]<temp)
				temp=righ[i+1];

		cout<<"Case "<<count++<<": "<<radar<<endl;
	}
	return 0;
}
