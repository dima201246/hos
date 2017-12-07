#include <string.h>

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

struct conf_str
{
	char config_array[255][100];
}

void init_system_buf()
{
	
}