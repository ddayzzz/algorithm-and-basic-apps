
#include "base.h"
#include "compare.h"
constexpr int f()
{
	return 5;
}
int main()
{
	/*constexpr int h = f();

	Vocabulary vol("C:\\Users\\Shu\\source\\repos\\2018WordBook\\2018WordBook\\text.txt");
	vol.print(1);*/
	compare_para("C:\\Users\\Shu\\source\\repos\\2018WordBook\\2018WordBook\\ml_test.txt",
		"C:\\Users\\Shu\\source\\repos\\2018WordBook\\2018WordBook\\ml_lib.txt");
	/*compare_para("C:\\Users\\Shu\\source\\repos\\2018WordBook\\2018WordBook\\text.txt",
		"C:\\Users\\Shu\\source\\repos\\2018WordBook\\2018WordBook\\lib.txt");*/
	return 0;
}