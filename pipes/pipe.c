#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main(){
	int fd[2];
	int ret = pipe(fd);//创建管道
	if(ret == -1){
		perror("pipe error");
		exit(1);
	}
	pid_t pid = fork();//创建子进程
	if(pid == -1){
		perror("fork error");
	}
	else if(pid == 0){//让子进程读数据
		close(fd[1]);  //子进程关闭写操作
		char buf[1024];
		ret = read(fd[0],buf,sizeof(buf));  //读取数据
		if(ret == 0){
			printf("\n");
		}
		//将读取到的数据输出到显示终端
		write(STDOUT_FILENO,buf,ret);
	}
	else{  //父进程写数据
		close(fd[0]);  //父进程关闭读操作，实现数据流通
		write(fd[1],"hello pipe!\n",strlen("hello pipe!\n"));
		wait(NULL);
	}
	return 0;
}
