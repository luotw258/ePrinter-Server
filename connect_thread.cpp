#include "sql.h"
#include "order_info.h"
#include <iostream>
#include "server_connect.h"

using std::cout;
using std::endl;

void *connect_thread(void* message)
{
    cout << "one connect_thread is runing\n";
    CConnect connect = *((CConnect*)message);
    int request_type = -1;
    while(1)
    {
        request_type = connect.get_request_type();
        if(-1 == request_type)
        {
            return NULL;
        }
        switch(request_type)
        {
            case OrderResuest : 
            cout << "  order request" << endl;
            connect.process_order_request();
            break;

            case FileRequest : 
            cout << "file request" << endl;
            connect.process_file_request();
            break;

            case PushRequest : 
            cout << "push request" << endl;
            connect.process_push_request();
            break;

            case TimeRequest :
            cout << "time request" << endl;
            connect.process_time_request();
            break;
            
            default : 
            cout << "unrecognized request" << endl;
            break;
        }
    }
	return NULL;
}
