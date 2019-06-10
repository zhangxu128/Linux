/*==============================
 * zhang
 * 基于 TcpSock 类实现客户端程序
 *============================*/

#include "tcpsocket.hpp"

int main(int argc,char * argv[]){

	if(argc != 3){
	
		std::cout<<"client ip,port"<<std::endl;
		return -1;
	}
	
	std::string ip = argv[1];
	uint16_t port = atoi(argv[2]);

	TcpSocket sock;
	CHECKRET(sock.Socket());
	CHECKRET(sock.Connect(ip,port));

	while(true){
		std::string buf;
		std::cout<<"client say:";
		fflush(stdout);
		std::cin>>buf;
		sock.Send(buf);

		buf.clear();
		sock.Recv(buf);
		std::cout<<"server say:"<<buf<<std::endl;
		
	}
	sock.Close();
}
