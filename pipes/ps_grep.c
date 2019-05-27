#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

//实现管道命令
int main(){
	
	int fd[2];
	int ret = pipe(fd);
	if(ret < 0){
		perror("pipe error");
		return -1;
	}
	int pid1 = fork();
	if(pid1 < 0){
		perror("fork error");
	}
	else if(pid1 == 0){
		close(fd[0]);
		dup2(fd[1],1);
		//将数据处理结果打印到标准输出
		execlp("ps","ps","-aux",NULL);
		exit(1);
	}
	int pid2 = fork();
	if(pid2 < 0){
		perror("fork error");
	}
	else if(pid2 == 0){
		close(fd[1]);
		dup2(fd[0],0);
		//循环从标准输入读取数据
		execlp("grep","grep","pipe",NULL);
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1,NULL,0);
	printf("child ps exit!\n");
	waitpid(pid2,NULL,0);
	printf("child grep exit!\n");
	return 0;
}
