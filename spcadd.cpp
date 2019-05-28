/*============================
 * zhang
 * 不用加减乘除做加法
 * 思路：异或为不带进位的加法
 *       &可以当成进位
 *       利用 ^ & << 实现
 *===========================*/


#include <iostream>

using namespace std;

int spadd(int a,int b){
	int sum = 0;
	while(b != 0){
		sum = a ^ b;
		b = (a & b) << 1;
		a = sum;
	}
	return sum;
}

int main(void){
	int a,b;
	cout<<"请输入两个数：";
	cin>>a>>b;
	cout<<"a+b="<<spadd(a,b)<<endl;
	return 0;
}
