/*=============================
 * zhang
 * 基于TcpSock类实现服务端程序
 *===========================*/

#include "tcpsocket.hpp"


int main(int argc,char* argv[]){
	
	if(argc != 3){
		std::cout<<"sever ip,port"<<std::endl;
		return -1;
	}
	
	std::string ip = argv[1];
	uint16_t port = atoi(argv[2]);

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
		printf("client ip %s , port % d\n",inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port));
		std::string buf;
		csock.Recv(buf);
		std::cout<<"client say:"<<buf.c_str()<<std::endl;
		buf.clear();
		std::cout<<"server say:";
		fflush(stdout);
		std::cin>>buf;
		csock.Send(buf);
	}
	sock.Close();

	return 0;
}
