#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
//命名管道读端
int main(){
	char * file = "fifo.txt";
	//打开管道文件
	int fd  = open(file,O_RDONLY);
	if(fd < 0){
		perror("open error");
	}
	printf("open fifo.txt success!\n");
	//建立命名管道
	umask(0);
	int ret = mkfifo(file,0664);
	if(ret < 0){
		if(errno != EEXIST)
		perror("mkfifo error");
	}
	printf("creat fifo success!\n");
	//从管道中读取文件
	while(1){
		sleep(20);
		char buf[1024];
		ret = read(fd,buf,1023);
		if(ret < 0){
			perror("read error!\n");
		}else if(ret == 0){
			printf("write closed!\n");
			return -1;
		}
		printf("buf[%s]\n",buf);
	}
	close(fd);
	return 0;
}
