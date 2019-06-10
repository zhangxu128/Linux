/*=============================
 * zhang
 * 由于Accept与Recv都是阻塞等待
 * 故单进程服务端与客户端只能通信
 * 一次，故此实现多进程版本
 *============================*/

#include "tcpsocket.hpp"
#include <sys/wait.h>
#include <signal.h>
void child(int signo){
	while(waitpid(-1,NULL,WNOHANG)>0);
}


int main(int argc,char* argv[]){

	if(argc != 3){
		std::cout<<"输入错误"<<std::endl;
		return -1;
	}
	std::string ip = argv[1];
	uint16_t port = atoi(argv[2]);
	
	signal(SIGCHLD,child);
	TcpSocket sock;

	CHECKRET(sock.Socket());
	CHECKRET(sock.Bind(ip,port));
	CHECKRET(sock.Listen(10));

	while(true){
		TcpSocket csock;
		struct sockaddr_in caddr;
		
		if(sock.Accept(csock,&caddr) == false){
			continue;
		}
		printf("client ip %s , port %d\n",inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port));
		
		pid_t pid = fork();
		if(pid<0){
			perror("fork error");
			return -1;
		}else if(pid == 0){
			while(true){
				std::string buf;
				csock.Recv(buf);
				std::cout<<"client say:"<<buf<<std::endl;
				buf.clear();
				
				std::cout<<"server say:";
				fflush(stdout);
				std::cin>>buf;
				csock.Send(buf);
			}	
		}
		csock.Close();
	}
	sock.Close();
	return 0;
}
