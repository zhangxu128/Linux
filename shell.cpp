#include <iostream>

using namespace std;

void print(int array[],int size){
	for(int i = 0 ; i < size; i++){
		cout<<array[i]<<" ";
	}
	cout<<endl;
}

void swap(int& a,int& b){
	int tmp = a;
	a = b;
	b= tmp;
}

void ShellSort(int array[],int size){
	int gap = size;
	do{
		gap = gap / 3 + 1;
		for(int i = 0;i<gap;i++){
			
			for(int j = gap + i;j < size;j += gap){
				if(array[j]<array[j - gap]){
					int tmp = array[j];
					int k;
					for(k = j - gap;k >= 0 && tmp < array[k];k -= gap){
						array[k + gap] = array[k];
					}
					array[k + gap] = tmp;
				}
			}
		}
	
	}while(gap>1);
}

int main(void){
	
	int array[] = {9,5,2,7,3,6,4,8,1};
	int size = sizeof(array) / sizeof(int);
	print(array,size);
	ShellSort(array,size);
	print(array,size);
	return 0;
}
