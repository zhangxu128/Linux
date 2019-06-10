/*====================
 * zhang
 * 实现一个 TcpSocket 类
 *==================*/


#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define CHECKRET(q) if((q) == false){return -1;}
//实现TcpSocket类
class TcpSocket{

	public:
		//初始化
		TcpSocket() : _sockfd(-1){}

		//建立套接字文件
		bool Socket(){
			_sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
			if(_sockfd < 0){
				perror("socket error");
				return false;
			}
			return true;
		}

		//绑定地址信息
		bool Bind(std::string& ip,uint16_t port){
			struct sockaddr_in addr;
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);
			addr.sin_addr.s_addr = inet_addr(ip.c_str());
			socklen_t len = sizeof(addr);

			int ret = bind(_sockfd,(struct sockaddr*)&addr,len);
			if(ret < 0){
				perror("bind error");
				return false;
			}
			return true;
		}

		//开始监听
		bool Listen(int backlog){
			//backlog : 同一时间客户端并发连接数
			int ret = listen(_sockfd,backlog);
			if(ret < 0){
				perror("listen error");
				return false;
			}
			return true;
		}

		//客户端发起连接
		bool Connect(std::string& ip,uint16_t port){
			struct sockaddr_in saddr;
			saddr.sin_family = AF_INET;
			saddr.sin_port = htons(port);
			saddr.sin_addr.s_addr = inet_addr(ip.c_str());
			socklen_t len = sizeof(saddr);
			
			int ret = connect(_sockfd,(struct sockaddr*)&saddr,len);
			if(ret < 0){
				perror("connect error");
				return false;
			}
			return true;
		}

		void SetSockFd(int fd){
			_sockfd = fd;
		}

		//服务端阻塞等待客户端连接,返回新的文件描述符与指定客户端进行通信
		bool Accept(TcpSocket& sock,struct sockaddr_in* caddr = NULL){
			struct sockaddr_in addr;
			socklen_t len = sizeof(addr);

			int newfd = accept(_sockfd,(struct sockaddr*)&addr,&len);
			if(newfd < 0){
				perror("accept error");
				return false;
			}
			if(caddr != NULL){
				memcpy(caddr,&addr,len);
			}
			sock.SetSockFd(newfd);
			// _sockfd是用来接收客户端请求的
			// newfd 是专门用来与指定客户端进行过通信的
			return true;
		}
		
		//接收数据
		bool Recv(std::string& buf){
			char tmp[4096] = { 0 };
			int ret = recv(_sockfd,tmp,4096,0);
			if(ret < 0){
				perror("recv error");
				return false;
			}
			else if(ret == 0){
				std::cout<<"连接已经断开"<<std::endl;
				return false;
			}
			buf.assign(tmp,ret);
			return true;
		}
		//发送数据
		bool Send(std::string& buf){
			int ret = send(_sockfd,buf.c_str(),buf.size()+1,0);
			if(ret < 0){
				perror("send error");
				return false;
			}
			return true;
		}

		//关闭连接
		bool Close(){
			close(_sockfd);
			_sockfd = -1;
		}
	private:
		int _sockfd;

};
