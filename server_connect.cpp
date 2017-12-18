#include "server_connect.h"

CConnect::CConnect()
{cout << "do not use this structure function(CConnect)\n";}
CConnect::~CConnect(){}
CConnect::CConnect(CServerNet connect_socket, CSql *sql)
{
    this->connect_socket = connect_socket;
    this->sql = sql;
    this->file_url = new char[256]();
}

int CConnect::get_request_type(void)
{
    int recv_len = 4 * sizeof(int);
    char *recv_buf = new char[recv_len]();
    this->connect_socket.xrecv(recv_buf, recv_len);

    int start_num = *((int*)(recv_buf));
    if(1314 != start_num)
    {
        cout << "start num is not 1314!" <<endl;
        return -1;
    }

    int printer_no = *((int*)(recv_buf + sizeof(int)));
    this->printer_no = printer_no;
    cout << "printer_no is " << printer_no;
    
    int request_type = *((int*)(recv_buf + 2 * sizeof(int)));

    int rest_len = *((int*)(recv_buf + 3 * sizeof(int))) - recv_len;
    //cout << "rest RecvLen : " << rest_len << endl;
    char *rest_buf = new char[rest_len]();
    this->connect_socket.xrecv(rest_buf, rest_len);   
    strcpy(this->file_url, (const char*)rest_buf);
    
    delete rest_buf;
    delete recv_buf;
    return request_type;
}

int CConnect::process_order_request(void)
{
    this->order.fno = -1;
    if(0 == this->sql->inquire_not_downloaded(this->printer_no))
    {
        this->sql->analyze_MYSQL_ROW(&(this->order));
        this->sql->print_order_info(&(this->order));
        this->connect_socket.xsend((char*)&(this->order), \
                                  (int)sizeof(this->order));
        return 0;
    }
    else
    {
        this->connect_socket.xsend((char*)&order, (int)sizeof(order));
        return -1;
    }
}

int CConnect::process_file_request(void)
{
    cout << this->file_url << endl;
    struct stat sb;
    int ret = stat(this->file_url, &sb);
    if (ret) 
    {
        perror("stat");
        return -1;
    }

    int filefd = open(this->file_url, O_RDONLY);
    if(-1 == filefd)
    {
        perror("open");
        cout << "url:" << file_url << endl;
        return -1;
    }   
    int file_size = (int)sb.st_size;
    cout << file_size << " bytes will been sent\n";
    this->connect_socket.xsend((char*)&file_size, (int)sizeof(int));
    cout << (int)sendfile(this->connect_socket.get_connfd(), \
    filefd, NULL, file_size) \
    << " bytes has been sent(file contect)\n";
    close(filefd);  
    this->sql->set_as_downloaded(this->order.fno);
    return 0;
}

int CConnect::process_push_request(void)
{
    int push_type;
    int64_t fno;
    this->connect_socket.xrecv((char*)(&push_type), sizeof(push_type));
    switch (push_type)
    {
    case CompletePrint:
        this->connect_socket.xrecv((char*)(&fno), sizeof(fno));
        this->sql->set_as_printed(fno);
        break;

    default:
        break;
    }
    return 0;
}

int CConnect::process_time_request(void)
{
    long long current_time = (long long)time(NULL);
    this->connect_socket.xsend((char*)&current_time, (int)sizeof(long long));
    cout << "current time : " << current_time << endl;
    return 0;
}



