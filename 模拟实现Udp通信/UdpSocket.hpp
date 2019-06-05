//======================
//  zhang
//  UDP 实现服务端客户端
//=====================  


#include <iostream>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>
#include <stdio.h>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>

//定义一个UdpSocket类
class UdpSocket{

	public:
		//构造函数，初始化socket文件描述符为-1
		UdpSocket():_sock(-1){}
		//析构函数不做处理
		~UdpSocket(){}

		//建立socket文件
		bool Socket(){
			_sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
			if(_sock < 0){
				perror("socket error");
				return false;
			}
			return true;
		}
		
		//绑定IP和端口
		bool Bind(std::string& ip,uint16_t port){
			struct sockaddr_in addr;
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);
			addr.sin_addr.s_addr = inet_addr(ip.c_str());
			socklen_t len = sizeof(sockaddr_in);
			
			int ret = bind(_sock,(struct sockaddr*)&addr,len);
			if(ret < 0){
				perror("bind error");
				return false;
			}
			return true;
		}

		//接受消息
		bool Recv(std::string& buf,struct sockaddr_in* saddr){
			char tmp[1500] = {0};
			socklen_t len = sizeof(sockaddr_in);

			int ret = recvfrom(_sock,tmp,1500,0,(struct sockaddr*)saddr,&len);
			if(ret < 0){
				perror("recvfrom error");
				return false;
			}
			buf.assign(tmp,ret);
			return true;
		}

		//发送消息

		bool Send(std::string& buf,struct sockaddr_in* caddr){
			socklen_t len = sizeof(sockaddr_in);
			int ret = sendto(_sock,buf.c_str(),buf.size(),0,(struct sockaddr*)caddr,len);
			if(ret < 0){
				perror("send error");
				return false;
			}
			return true;
		}

		//关闭文件
		bool Close(){
			close(_sock);
			_sock = -1;
		}
	private:
		int _sock;
};
