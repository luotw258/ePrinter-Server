#ifndef __CONNECT_H_
#define __CONNECT_H_
#include <iostream> 
#include <sys/types.h>  
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <errno.h>
#include <fcntl.h> 
#include <stdio.h>
#include <string.h>
#include "server_net.h"
#include "sql.h"
#include "order_info.h"

using std::cout;
using std::endl;
class CConnect
{
public:
    CConnect();
    ~CConnect();
    CConnect(CServerNet connect_socket, CSql *sql);
public:
    int get_request_type(void);
    int process_order_request(void);
    int process_file_request(void);
    int process_push_request(void);
    
private:
    int printer_no;
    OrderInfo order;
    char *file_url;
    
    CServerNet connect_socket;
    CSql *sql;
};

#endif // !__CONNECT_H_
