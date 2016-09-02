#ifndef HOS_API_H
#define HOS_API_H

	#include <unistd.h>

	extern	pid_t	loading_title_pid;

	void loading_title_start();
	void kill_loading_title();

#endif