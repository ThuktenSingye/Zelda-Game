#define _DEFAULT_SOURCE
#include <time.h>
#include "ucpSleep.h"

void ucpSleep(float sec)
{
	struct timespec ts;
	ts.tv_sec = (int) sec;
	ts.tv_nsec = (sec - ((int) sec)) * 1000000000;
	nanosleep(&ts,NULL);
}
