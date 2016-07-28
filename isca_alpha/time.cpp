#include "../include/time.h"

local_time get_time_now() {
	local_time	time_temp;
	time_t		t;
	
	t	= time(NULL);
	struct tm* now	= localtime(&t);

	time_temp.hours	= now->tm_hour;
	time_temp.min	= now->tm_min;
	time_temp.sec	= now->tm_sec;
	time_temp.mon	= now->tm_mon + 1;
	time_temp.day	= now->tm_mday;
	time_temp.year	= now->tm_year + 1900;
	return time_temp;
}
