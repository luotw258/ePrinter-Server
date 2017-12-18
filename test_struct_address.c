#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "order_info.h"


int main(int argc, char * atgv[])
{
	OrderInfo		order;

	printf("sizeof OrderInfo is %d\n", (int)sizeof(OrderInfo));

	printf("address of fprinterno is %d\n", (int)&(order.fprinterno) - (int)&(order.fprinterno));
	printf("address of fnum is %d\n", (int)&(order.fnum) - (int)&(order.fprinterno));
	printf("address of fdownload is %d\n", (int)&(order.fdownload) - (int)&(order.fprinterno));
	printf("address of fprint is %d\n", (int)&(order.fprint) - (int)&(order.fprinterno));
	printf("address of fside is %d\n", (int)&(order.fside) - (int)&(order.fprinterno));
	printf("address of fcolor is %d\n", (int)&(order.fcolor) - (int)&(order.fprinterno));
	printf("address of fstaris %d\n", (int)&(order.fstart) - (int)&(order.fprinterno));
	printf("address of fend is %d\n", (int)&(order.fend) - (int)&(order.fprinterno));
	printf("address of fcopies is %d\n", (int)&(order.fcopies) - (int)&(order.fprinterno));
	printf("address of fpapersize is %d\n", (int)&(order.fpapersize) - (int)&(order.fprinterno));
	printf("address of fsidenum is %d\n", (int)&(order.fsidenum) - (int)&(order.fprinterno));
	printf("address of fstyle is %d\n", (int)&(order.fstyle) - (int)&(order.fprinterno));
	printf("address of fmodel is %d\n", (int)&(order.fmodel) - (int)&(order.fprinterno));
	printf("address of fplantime is %d\n", (int)&(order.fplantime) - (int)&(order.fprinterno));
	printf("address of fspent is %d\n", (int)&(order.fspent) - (int)&(order.fprinterno));
    printf("address of fno is %d\n", (int)&(order.fno) - (int)&(order.fprinterno));
	printf("address of uphone is %d\n", (int)&(order.uphone) - (int)&(order.fprinterno));
	printf("address of fuploadtime is %d\n", (int)&(order.fuploadtime) - (int)&(order.fprinterno));
	printf("address of fname is %d\n", (int)&(order.fname) - (int)&(order.fprinterno));
	printf("address of furl is %d\n", (int)&(order.furl) - (int)&(order.fprinterno));
	
    
	return 0;
}

