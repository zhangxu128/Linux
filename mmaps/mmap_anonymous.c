#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
//父子进程之间通信

//定义一个全局变量
int g_var = 100;

int main(){
	/*//创建辅助文件建立映射区
	int fd = open("mmapfuzi.txt",O_CREAT|O_RDWR,0664);
	if(fd == -1){
		perror("open error");
		exit(1);
	}
	//unlink(fd);   删除目录项，让该文件可删除，真正删除的时间是占用该文件的全部进程终止
	int * p = NULL;

	ftruncate(fd,20);*/


	//采用匿名映射创建映射区
	int *p = NULL;
	p = mmap(NULL,20,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	if(p == MAP_FAILED){
		perror("mmap error");
		exit(1);
	}
	//可通过指针操作内存，辅助文件已没有作用，直接关闭
	//close(fd);
	
	*p = 20;
	printf("数据初始内容：var = %d,p = %d\n",g_var,*p);
	//创建子进程
	int pid = fork();
	if(pid < 0){
		perror("fork error");
		exit(1);
	}else if(pid == 0){//子进程读数据
		*p = 200;
		printf("我是子进程我现在在写入哦！\n");
		printf("var = %d,*p = %d\n",g_var,*p);
		
	}else{//父进程写数据
		sleep(5);
		printf("我是父进程我正在读入数据！\n");
		printf("var = %d,*p = %d\n",g_var,*p);
		wait(NULL);
	}
	
	//释放映射区
	int ret = munmap(p,20);
	if(ret == -1){
		perror("munmap error");
	}
	return 0;
}
