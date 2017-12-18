#ifndef __SQL_H_
#define __SQL_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "mysql/mysql.h"
#include "order_info.h"
#include <pthread.h>

using std::cout;
using std::endl;
using std::string;

class CSql {
public:
	CSql();
	~CSql();
	CSql(const char * host, const char * user, const char * passwd, const char * db);
public:

	int inquire_not_downloaded(int printer_no);
	int set_as_downloaded(int64_t fno);
	int set_as_printed(int64_t fno);
	int analyze_MYSQL_ROW(OrderInfo *order);
	int print_order_info(OrderInfo * order);
private:

	MYSQL			mysql;
	MYSQL_RES * 	res;
	MYSQL_ROW		row;
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
};
#endif // !__SQL_H_
