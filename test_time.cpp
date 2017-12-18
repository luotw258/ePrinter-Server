#include <iostream>
#include <time.h>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	time_t settime = 0;
	cout << time(NULL) << endl;
	stime(&settime);
	cout << time(NULL) << endl;
	return 0;
}
