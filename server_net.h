#ifndef __SERVER_NET_H_
#define __SERVER_NET_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h> 
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
using std::cout;
using std::endl;
using std::string;

class CServerNet
{
public:
	CServerNet();
	~CServerNet();
	CServerNet(unsigned short port);
    CServerNet(CServerNet &net);
public:
	int start_listen(void);
	int accept_connect(void);
	int xrecv(char *buf, int len, int display_schedule = 0);
	int xsend(char *buf, int len, int display_schedule = 0);
    int get_connfd(void);
private:
	unsigned short	port;					// 本地端口 
	int 			sockfd;
	struct sockaddr_in my_addr;				//本地地址结构体
	int connfd;
};

#endif // !__SERVER_NET_H_