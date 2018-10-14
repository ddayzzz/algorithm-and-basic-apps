
#include "polynomial_mangage.h"
const unsigned int  MAXSIZE = 20;
const unsigned int MAXSIZE_OFXISHU =20;
static int count = 1;

void input(polynomial_manage *poly,bool initial=true)
{
	//输入表达式截断
	int c;
	char endc;
	char contiu = 'y';
	int temparr[MAXSIZE_OFXISHU];
	if (count == MAXSIZE) { printf("多项式存储已满%d", count); return; }
	unsigned pos = 0;
	do
	{
		
		printf("请输入从常数到最高项的系数(如果该项不存在, 请输入0). 最多%d个项数, 每个系数用\',\'分隔:", MAXSIZE_OFXISHU);
		while ((scanf("%d%c",&c,&endc)) && endc !='\n' && pos <=MAXSIZE_OFXISHU-1)
		{
			temparr[pos] = c;
			++pos;
		}
		temparr[pos] = c;
		int val = 1;
		printf("请输入未知数的值:"); scanf("%d", &val); getchar();
		poly->construct_poly(count-1 , val, pos+1, &temparr[0]);
		//poly->get_address_byindex(startindex)->show_unary_mode('\b', 'X');
		printf("是否继续(y/n)?"); contiu = getchar(); 
		if (contiu == 'Y' || contiu == 'y') { ++count; pos = 0; } getchar();
		
	} while (contiu == 'Y' || contiu == 'y');
}

int main()
{
    
	polynomial_manage pom; pom.initial(MAXSIZE);
	input(&pom);
	polynomial *ptp = NULL;
	int k; char unary='X';
	printf("请输入一个字符表示未知数(例如X,y...):");
	unary = getchar();
	getchar();
	for (k = 1; k <= count; ++k)
	{
		 ptp = pom.get_address_byindex(k-1);
		 if (ptp != NULL)
		 {
			 printf("\n编号[%d] : ",k);
			 ptp->show_unary_mode('\b', unary);
		 }

	}
	//
	char contiu;
	char ops; unsigned l, r; polynomial *lp = NULL; polynomial  *rp = NULL; polynomial dest;
	do
	{
		printf("\n请输入你想要计算的两个多项式, 例如: 想计算第二项和第三项的乘积请输入2*3 (目前支持的运算+和*):");
		scanf("%d%c%d%*c", &l, &ops, &r);
		if (l > count || r > count)
		{
			printf("错误! 多项式的编号太大.");
			continue;
		}
		switch (ops)
		{
		case '+':
			lp = pom.get_address_byindex(l - 1); rp = pom.get_address_byindex(r - 1);
			if(lp !=NULL && rp !=NULL)
			{
				lp->plus_xishuofpoly(rp, &dest, lp->unknownvalue); printf("(");
				lp->show_unary_mode('\b', unary); printf(")%c(", ops);
				rp->show_unary_mode('\b', unary); printf(")=");
				dest.show_calced_value();
				dest.free_poly();
			}
			break;
		case '*':
			lp = pom.get_address_byindex(l - 1); rp = pom.get_address_byindex(r - 1);
			if (lp != NULL && rp != NULL)
			{
				lp->multiply_xishuopoly(rp, &dest, lp->unknownvalue); printf("(");
				lp->show_unary_mode('\b', unary); printf(")%c(", ops);
				rp->show_unary_mode('\b', unary); printf(")=");
				dest.show_calced_value();
				dest.free_poly();
			}
			break;
		default:
			printf("错误! 不支持的运算符");
			break;
		}
		printf("继续? (y/n)");
		contiu = getchar(); getchar();

	} while (contiu =='Y' || contiu=='y');
	// 计算过程没有写
}