/*======================x=======
 * zhang
 * 由于Accept与Recv都是阻塞等待
 * 故单进程服务端与客户端只能通信
 * 一次，故此实现多线程版本
 *============================*/

#include "tcpsocket.hpp"
#include <pthread.h>

void* thr_start(void* arg){
	TcpSocket* sock = (TcpSocket*)arg;
	while(true){
		std::string buf;
		sock->Recv(buf);
		std::cout<<"client say:"<<buf<<std::endl;;

		buf.clear();
		std::cout<<"server say:";
		fflush(stdout);
		std::cin>>buf;
		sock->Send(buf);
	}
	sock->Close();
	delete sock;
	return NULL;
}


int main(int argc,char* argv[]){

	if(argc != 3){
		std::cout<<"输入错误"<<std::endl;
		return -1;
	}
	std::string ip = argv[1];
	uint16_t port = atoi(argv[2]);
	
	TcpSocket sock;

	CHECKRET(sock.Socket());
	CHECKRET(sock.Bind(ip,port));
	CHECKRET(sock.Listen(10));

	while(true){
		TcpSocket* csock = new TcpSocket();
		struct sockaddr_in caddr;
		
		if(sock.Accept(*csock,&caddr) == false){
			continue;
		}
		printf("client ip %s , port %d\n",inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port));	
		pthread_t tid;
		pthread_create(&tid,NULL,thr_start,(void*)csock);
		pthread_detach(tid);
	}
	sock.Close();
	return 0;

}
