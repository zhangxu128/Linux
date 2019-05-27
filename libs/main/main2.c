#include<stdio.h>
#include "calculate.h"

//使用动态库计算乘除

int main(){

	int a = 6;
	int b = 2;
	int s = mul(a,b);
	int d = div(a,b);
	printf("%d\n",s);
	printf("%d\n",d);
	return 0;
}
