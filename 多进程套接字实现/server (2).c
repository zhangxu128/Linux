/*==============
 *    zhang
 * 多进程c/s模型
 *=============*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <ctype.h>
#include <errno.h>
#include <strings.h>
#include <arpa/inet.h>
#include <signal.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 6666

//注册信号回收子进程
void wait_child(int signo){

	while(waitpid(0,NULL,signo)>0);
	return;
}


int main(void){

	int sfd;// server fd
	int cfd;// client fd
	struct sockaddr_in serv_addr,clie_addr;
	socklen_t clen;
	pid_t pid;
	char buf[BUFSIZ],clie_IP[BUFSIZ];
	int n,i;
	//建立socket文件
	sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1){
		printf("socket error!\n");
		return -1;
	}
	
	//init
	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	inet_pton(AF_INET,SERV_IP,&serv_addr.sin_addr.s_addr);//IP
	//serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(SERV_PORT);//PORT
	
	//bind IP PORT
	bind(sfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

	//设定可以连接的上限数,默认最大128
	listen(sfd,3);
	printf("wait client connect~~~~~~~~~~~~~~~~~\n");
	while(1){
		clen = sizeof(clie_addr);
		//阻塞等待客户端连接
		cfd = accept(sfd,(struct sockaddr*)&(clie_addr),&clen);
		printf("client IP : %s , PORT : %d\n",inet_ntop(AF_INET,&clie_addr.sin_addr.s_addr,clie_IP,sizeof(clie_IP)),
				ntohs(clie_addr.sin_port));

		pid = fork();
		if(pid<0){
			perror("fork error");
			return -1;
		}else if(pid == 0){
			close(sfd);
			n = read(cfd,buf,sizeof(buf));
			for(i = 0;i < n;i++){
				buf[i] = toupper(buf[i]);
			}
			write(cfd,buf,n);
			return 0;	
		}
		else{
			close(cfd);
			signal(SIGCHLD,wait_child);
		}
	}
	return 0;
}
