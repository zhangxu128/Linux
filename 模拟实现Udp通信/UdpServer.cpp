/*===============
 * zhang
 * 实现服务端程序
 *=============*/

#include "UdpSocket.hpp"

int main(int argc,char* argv[]){
		
	if(argc != 3){
		std::cout<<"./UDP ser ip port"<<std::endl;
		return -1;
	}
	std::string ip = argv[1];
	uint16_t port = atoi(argv[2]);

	UdpSocket us;
	us.Socket();
	us.Bind(ip,port);

	while(1){
		std::string buf;
		struct sockaddr_in cli_addr;
		us.Recv(buf,&cli_addr);
		std::cout<<"client say:"<<buf<<std::endl;
		std::cout<<"server say:";
		fflush(stdout);
		std::cin>>buf;
		us.Send(buf,&cli_addr);
	}
	us.Close();
	return 0;
}
