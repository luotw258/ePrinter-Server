#include "server_net.h"

CServerNet::CServerNet()
{cout << "do not use this structure function(CServerNet)\n";}
CServerNet::~CServerNet(){}
CServerNet::CServerNet(unsigned short port)
{
	this->port = port;
}
CServerNet::CServerNet(CServerNet &net)
{
    this->port = net.port;					// 本地端口 
	this->sockfd = net.sockfd;
	this->my_addr = net.my_addr;				//本地地址结构体
	this->connfd = net.connfd;
}

int CServerNet::start_listen(void)
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0); // 创建通信端点：套接字
	if (sockfd < 0) 
	{
		perror("socket");
		return -1;
	}
	// 设置套接字选项避免地址使用错误  
	int on	= 1;
	if ((setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0) 
	{
		perror("setsockopt failed");
		return -1;
	}
	// 设置本地地址结构体
	bzero(&my_addr, sizeof(my_addr));				// 清空	 
	my_addr.sin_family	= AF_INET;					// ipv4
	my_addr.sin_port	= htons(port);				// 端口
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);	// ip

	// 绑定
	int err_log = bind(sockfd, (struct sockaddr*)&my_addr, \
	            sizeof(my_addr));
	if (err_log != 0) 
	{
		perror("binding");
		close(sockfd);
		return -1;
	}

	err_log = listen(sockfd, 10);		// 监听，监听套接字改为被动
	if (err_log != 0) 
	{
		perror("listen");
		close(sockfd);
		return -1;
	}
	cout << "listen client @port=" << port <<endl;

	return 0;
}

int CServerNet::accept_connect(void)
{
	struct sockaddr_in client_addr;
	socklen_t	cliaddr_len = sizeof(client_addr);
	int connfd;
	// 等待连接
	connfd = accept(sockfd, (struct sockaddr *) &client_addr, &cliaddr_len);
	//printf("connfd:%d\n", connfd);	
	if (connfd < 0) 
	{
		perror("accept");
		return -1;
	}
	this->connfd = connfd;
	return connfd;
}

int CServerNet::xrecv(char *buf, int len, int display_schedule)
{
    int ret;
    
    int recv_size = 0;
    char *schedule_dis = new char[102]();
    const char *schedule_rotate = "|/-\\";
    int rate = 0;
    int max_len = len;
    
    while(len != 0 && (ret = recv(this->connfd, (char*)buf, len, 0)) != 0)
    {
        if(-1 == ret)
        {
            if(EINTR == errno)
                continue;
            perror("recv in xrecv");
            break;
        }
        len -= ret;
        buf += ret;

        if(1 == display_schedule)
        {
            recv_size += ret;
            rate = (int)((float)recv_size/(float)max_len*100.0f);
            schedule_dis[rate] = '#';
            fprintf(stderr, "[%-100s][%3d%%][%c]\r", schedule_dis, rate, schedule_rotate[rate%4]);
            fflush(stderr);
        }
    }
    if(1 == display_schedule)
        fprintf(stderr, "\n");
    delete schedule_dis;
    //printf("There are %d btyes has been downloaded\n", recv_size);
    return 0 == len;
}
int CServerNet::xsend(char *buf, int len, int display_schedule)
{
    int ret;
    
    int send_size = 0;
    
    char *schedule_dis = new char[102]();
    const char *schedule_rotate = "|/-\\";
    int rate = 0;
    int max_len = len;
    while(len != 0 && (ret = send(this->connfd, (char*)buf, len, 0)) != 0)
    {
        if(-1 == ret)
        {
            if(EINTR == errno)
                continue;
            perror("send in xsend");
            break;
        }
        len -= ret;
        buf += ret;
        
        if(1 == display_schedule)
        {
            send_size += ret;
            rate = (int)((float)send_size/(float)max_len*100.0f);
            schedule_dis[rate] = '#';
            fprintf(stderr, "[%-100s][%3d%%][%c]\r", schedule_dis, rate, schedule_rotate[rate%4]);
            fflush(stderr);
        }
    }
    if(1 == display_schedule)
        fprintf(stderr, "\n");
    delete schedule_dis;
    //printf("There are %d btyes has been sent\n", send_size);
    return 0 == len;
}

int CServerNet::get_connfd(void)
{
    return this->connfd;
}