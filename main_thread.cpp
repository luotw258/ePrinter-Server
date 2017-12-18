#include <iostream>
#include <string>
#include <pthread.h>
#include "server_net.h"
#include "sql.h"
#include "server_connect.h"

using std::cout;
using std::endl;
using std::string;

extern void *connect_thread(void* message);
int main(int argc, char *argv[])
{
    CSql sql("localhost", "root", "qwe123root", "ePrinter");
    CServerNet listen_socket(1314);
    listen_socket.start_listen();
    pthread_t connection;
    CConnect *connect;
    while(1)
    {
        listen_socket.accept_connect();
        cout << "one printer has been connected!" << endl;
        connect = new CConnect(listen_socket, &sql);
        cout << "新连接地址：" << connect << endl;
        pthread_create(&connection, NULL, connect_thread, (void*)(connect));
	}
}
