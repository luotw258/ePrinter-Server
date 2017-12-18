#include "sql.h"

CSql::CSql()
{cout << "do not use this structure function(CSql)\n";}
CSql::~CSql(){}

CSql::CSql(const char * host, const char * user, const char * passwd, const char * db)
{
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_real_connect(&mysql, host, user, passwd, db, 3306, NULL, 0);
}


int CSql::inquire_not_downloaded(int printer_no)
{
    pthread_mutex_lock(&this->mutex);
    //cout << "get mutex" << endl;
	string	sql_inquire_statement = "select * from sys_file where fprinterno = ";

	sql_inquire_statement += std::to_string(printer_no);
	sql_inquire_statement += " and fdownload = 0;";
	//cout << sql_inquire_statement << endl;
    
	mysql_query(&mysql, sql_inquire_statement.c_str());
	res = mysql_store_result(&mysql); 					//获取结果集
	int num_result = mysql_num_rows(res);
	//printf("%d row(s) were found!\n", num_result);
	if (0 < num_result)
	{
		row = mysql_fetch_row(res);
		mysql_free_result(res);
		pthread_mutex_unlock(&this->mutex);	
	    //cout << "release mutex" << endl;
		return 0;
	}
	else
	{
	    mysql_free_result(res);
	    pthread_mutex_unlock(&this->mutex);	
	    //cout << "release mutex" << endl;
	    return -1;
	}
	
}


int CSql::set_as_downloaded(int64_t fno)
{
    pthread_mutex_lock(&this->mutex);
    ///cout << "get mutex" << endl;
	string	sql_set_statement = "update sys_file set fdownload = 1 where fno = ";

	sql_set_statement += std::to_string(fno);
	//printf("%s\n", sql_set_statement.c_str());

	mysql_query(&mysql, sql_set_statement.c_str());
	pthread_mutex_unlock(&this->mutex);
	//cout << "release mutex" << endl;
	return 0;
}

int CSql::set_as_printed(int64_t fno)
{
    pthread_mutex_lock(&this->mutex);
    ///cout << "get mutex" << endl;
	string	sql_set_statement = \
	    "update sys_file set fprint = 1 where fno = ";

	sql_set_statement += std::to_string(fno);
	//printf("%s\n", sql_set_statement.c_str());

	mysql_query(&mysql, sql_set_statement.c_str());
	pthread_mutex_unlock(&this->mutex);
	//cout << "release mutex" << endl;
	return 0;
}
int CSql::analyze_MYSQL_ROW(OrderInfo *order)
{
    pthread_mutex_lock(&this->mutex);
    //cout << "get mutex" << endl;
	order->fno = atoi(row[0]);
	strcpy(order->uphone, row[1]);
	order->fprinterno = atoi(row[2]);
	strcpy(order->fname, row[3]);
	strcpy(order->furl, row[4]);
	order->fnum = atoi(row[5]);
	order->fdownload = atoi(row[6]);
	order->fprint = atoi(row[7]);
	order->fside = atoi(row[8]);
	order->fcolor = atoi(row[9]);
	order->fstart = atoi(row[10]);
	order->fend = atoi(row[11]);
	order->fcopies = atoi(row[12]);
	order->fpapersize = atoi(row[13]);
	order->fsidenum = atoi(row[14]);
	order->fstyle = atoi(row[15]);
	strcpy(order->fuploadtime, row[16]);
	order->fplantime = atoi(row[17]);
	order->fmodel = atoi(row[18]);
	order->fspent = atoi(row[19]);
	pthread_mutex_unlock(&this->mutex);
	//cout << "release mutex" << endl;
	return 0;
}
int CSql::print_order_info(OrderInfo * order)
{
	cout << "-----------------------------------------------" << endl;
	cout << "fno is " << order->fno << endl;
	cout << "uphone is " << order->uphone << endl;
	cout << "fprinterno is " << order->fprinterno << endl;
	cout << "fname is " << order->fname << endl;
	cout << "furl is " << order->furl << endl;
	cout << "fnum is " << order->fnum << endl;
	cout << "fdownload is " << order->fdownload << endl;
	cout << "fprint is " << order->fprint << endl;
	cout << "fside is " << order->fside << endl;
	cout << "fcolor is " << order->fcolor << endl;
	cout << "fstar is " << order->fstart << endl;
	cout << "fend is " << order->fend << endl;
	cout << "fcopies is " << order->fcopies << endl;
	cout << "fpapersize is " << order->fpapersize << endl;
	cout << "fsidenum is " << order->fsidenum << endl;
	cout << "fstyle is " << order->fstyle << endl;
	cout << "fuploadtime is " << order->fuploadtime << endl;
	cout << "fplantime is " << order->fplantime << endl;
	cout << "fmodel is " << order->fmodel << endl;
	cout << "fspent is " << order->fspent << endl;
	cout << "-----------------------------------------------" << endl;
	return 0;
}