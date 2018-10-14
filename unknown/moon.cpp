#include <iostream>
#include <string>
#include <vector>
#define MUL(x,y)(x)*y
using namespace std;
int main()
{
   int a=3;int b=4;
   int c=MUL(a+b,a-b);
   printf("%d",c);
   return 0;
}