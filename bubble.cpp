#include <iostream>

using namespace std;

void print(int array[],int size){
	for(int i = 0; i < size; i++){
		cout<<array[i]<<" ";
	}
	cout<<endl;
}

void swap(int& a,int& b){
	int tmp = a;
	a = b;
	b = tmp;
}
void BubbleSort(int array[],int size){
	for(int i = 0 ; i < size; i++){
		int flag = 0;
		for(int j = 1; j < size - i; j++){
			if(array[j - 1] > array[j]){
				swap(array[j - 1],array[j]);
				flag = 1;
			}
		}
		if(flag == 0){
			return ;
		}
	}

}

int main(){

	int array[] = {9,5,2,7,3,8,6,4,1};
	int size = sizeof(array) / sizeof(int);
	print(array,size);
	BubbleSort(array,size);
	print(array,size);
	return 0;
}
