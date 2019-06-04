#include <iostream>

using namespace std;

void print(int array[],int size){
	for(int i = 0 ; i < size; i++){
		cout<<array[i]<<" ";
	}
	cout<<endl;
}

void swap(int &a,int &b){
	int tmp = a;
	a = b;
	b = tmp;
}


void Merge(int array[],int left,int mid,int right,int *tmp){
	int left1 = left;
	int right1 = mid;
	int left2 = mid+1;
	int right2 = right;
	int len =0;
	while(left1<=right1 && left2<=right2){
		if(array[left1]<array[left2]){
			tmp[len++] = array[left1++];
		}
		else{
			tmp[len++] = array[left2++];
		}
	}
	while(left1<=right1){
		tmp[len++] = array[left1++];
	}
	while(left2<=right2){
		tmp[len++] = array[left2++];
	}

	for(int i = 0 ; i < len;i++){
		array[i+left] = tmp[i];
	}
}

void MergeInner(int array[],int left,int right,int *tmp){
	if(left >= right){
		return;
	}
	int mid = (left+right) / 2;
	MergeInner(array,left,mid,tmp);
	MergeInner(array,mid+1,right,tmp);
	Merge(array,left,mid,right,tmp);
}

void MergeSort(int array[],int size){
	int *tmp = new int[size];
	MergeInner(array,0,size -1,tmp);
	delete[] tmp;
}

int main(void){

	int array[] = {9,5,2,7,3,8,1,4,6};
	int size = sizeof(array) / sizeof(int);
	print(array,size);
	MergeSort(array,size);
	print(array,size);
	return 0;
}
