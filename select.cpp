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
void SelectSort(int array[],int size){
	for(int i = 0 ; i < size; i++){
		int min = i;
		for(int j = i + 1;j < size;j++){
			if(array[j] < array[min]){
				min = j;
			}
		}
		if(min != i){
			swap(array[min],array[i]);
		}
	}

}

int main(){

	int array[] = {9,5,2,7,3,8,6,4,1};
	int size = sizeof(array) / sizeof(int);
	print(array,size);
	SelectSort(array,size);
	print(array,size);
	return 0;
}
