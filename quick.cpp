#include <iostream>

using namespace std;

void print(int array[],int size){
	for(int i = 0 ; i < size; i++){
	
		cout<<array[i]<<" ";
	}
	cout<<endl;
}

void QuickSort(int array[],int left,int right){
	int i = left;
	int j = right;
	int privot = array[left]; //保存基准值
	if(i < j){
	
		while(i < j){
			//从后往前找小于基准值的数
			while(i<j && array[j]>privot){
				j--;
			}
			//填坑
			if(i<j){
				array[i] = array[j];
				i++;
			}
			//从前往后找大于基准值的数
			while(i<j && array[i] < privot){
				i++;
			}
			//填坑
			if(i<j){
				array[i] = array[j];
				j--;
			}
			
		}
		//循环结束，交换基准值
		array[i] = privot;
		//递归左半边
		
		QuickSort(array,left,i-1);
		//递归右半边
		QuickSort(array,i+1,right);
	}
	
}

int main(void){

	int array[] = {9,5,2,7,3,8,6,4,1};
	int size = sizeof(array) / sizeof(int);
	cout<<"排序前序列："<<endl;
	print(array,size);
	cout<<"排序后序列："<<endl;
	QuickSort(array,0,size - 1);
	print(array,size);
	return 0;
}
