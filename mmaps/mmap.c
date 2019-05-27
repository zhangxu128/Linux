#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/mman.h>
//通过映射区操作文件
int main(){

	int fd = open("mytest.txt",O_CREAT|O_RDWR, 0777);
	if(fd < 0){
		perror("open error");
		exit(1);
	}
	
	int len = ftruncate(fd,20);
	if(len < 0){
		perror("ftruncate error");
		exit(1);
	}
	
	//创建映射
	char * p = NULL;
	p = mmap(NULL,4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(p == MAP_FAILED){
		perror("mmap error");
		exit(1);
	}
	strcpy(p,"abc");  //写数据
	int ret;
	ret = munmap(p,4);
	if(ret == -1){
		perror("munmap error");
		exit(1);
	}
	close(fd);
	return 0;
}
