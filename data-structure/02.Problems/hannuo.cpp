//汉诺塔问题
#include <iostream>

using namespace std;
void Hannuo_display(int n, char from, char dest)
{

	cout << "盘子" << n << "从" <<from<< "移动到" << dest <<" "<<endl;

}
void Hannuo(int n, char from, char via, char dest)
{
	if (n == 1)
	{
		Hannuo_display(1, from, dest);
	}
	else
	{
		Hannuo(n - 1, from, dest, via);
		Hannuo_display(n, from, dest);
		Hannuo(n - 1, via, from, dest);
	}
}
int main()
{
	Hannuo(3, 'A', 'B', 'C');
}