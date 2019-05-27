#include <iostream>

using namespace std;

void print(int array[],int size){

	for(int i = 0;i < size;i++){
		cout<<array[i]<<" ";

	}
	cout<<endl;
}

void swap(int &a,int &b){
	int tmp = a;
	a = b;
	b = tmp;
		
}

void InsertSort(int array[],int size){

	for(int i = 1; i<size;i++){
		if(array[i] < array[i - 1]){
			int tmp = array[i];
			int j ;
			for(j = i - 1;j >= 0 && tmp < array[j];j--){
				array[j+1] = array[j];
			}
			array[j+1] = tmp;
		}
	}
}

int main(){
	int array[] = {9,5,2,7,3,8,6,1,4};
	int size = sizeof(array) / sizeof(int);
	print(array,size);
	InsertSort(array,size);
	print(array,size);
	return 0;
}
