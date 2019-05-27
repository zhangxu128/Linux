#include<stdio.h>
#include "calculate.h"

//使用静态库实现加减

int main(){

	int a = 9;
	int b = 3;
	int sum = add(a,b);
	printf("%d\n",sum);

	int su = sub(a,b);
	printf("%d\n",su);
	return 0;
}


