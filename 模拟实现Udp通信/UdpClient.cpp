/*=================
 * zhang
 * 实现客户端
 *================*/


#include "UdpSocket.hpp"


int main(int argc,char* argv[]){
		
	if(argc != 3){
		std::cout<<"udp_cli ip,port"<<std::endl;
		return -1;
	}
	
	UdpSocket us;

	std::string ip = argv[1];
	uint16_t port = atoi(argv[2]);

	us.Socket();
	
	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = inet_addr(ip.c_str());

	while(1){
		std::string buf;
		std::cout<<"client say:";
		fflush(stdout);
		std::cin>>buf;
		us.Send(buf,&saddr);
		us.Recv(buf,&saddr);
		std::cout<<"server say:"<<buf<<std::endl;
	}
	us.Close();
	return 0;
}
