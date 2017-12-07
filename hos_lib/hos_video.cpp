#include "../include/hos_video.h"
#include "../include/configurator.h"
#include <string.h>
#include <string>
#include <signal.h>
#include "../include/system_defines.h"

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <vector>

bool video_init = false;

video_bufer_app_strct *video_obj;

std::string buf_name = "test";

void setVideoBufName(std::string name)
{
	buf_name = name;
}

void screen_init()
{
	int am;

	if ((am = shm_open(VIDEO_ADD_APP, O_RDWR, 0777)) == -1)
	{
		add_to_filef("./test", "Init screen NotOK!!\n");
		exit(-1);
	}

	app_container_strct *video_addon_obj = (app_container_strct*) mmap(NULL, sizeof(struct app_container_strct), PROT_READ | PROT_WRITE, MAP_SHARED, am, 0);

	while (video_addon_obj->busy);

	video_addon_obj->busy = true;

	buf_name = "/" + buf_name;

	strcpy(video_addon_obj->name_app, "Main");
	strcpy(video_addon_obj->name_buf, buf_name.c_str());

	int sm = shm_open(video_addon_obj->name_buf, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR); // Создание объекта общей памяти

	if (ftruncate(sm, sizeof(struct video_bufer_app_strct)) == -1) // Задание размера этой памяти
	{
		// return -1;
		add_to_file("./!app_video", "Fail!\n");
	}

	video_obj = (video_bufer_app_strct*) mmap(NULL, sizeof(struct video_bufer_app_strct), PROT_READ | PROT_WRITE, MAP_SHARED, sm, 0);


	for (unsigned int y = 0; y < VIDEO_SIZE_Y; ++y)
	{
		for (unsigned int x = 0; x < VIDEO_SIZE_X; ++x)
		{
			video_obj->video_buffer[x][y] = 0;
		}
	}

	
	add_to_filef("./test", "Video PID: %d\n", video_addon_obj->pid_video);
	kill(video_addon_obj->pid_video, SIGUSR1);

	video_init = true;
}

void mvprint(unsigned int y, unsigned int x, std::string fmt, ...) {
	/*if (!video_init)
	{
		screen_init();
	}*/

	char sbf[STRING_BUF_SIZE];
	va_list ap;

	va_start(ap, fmt);
	vsprintf(sbf, fmt.c_str(), ap);
	va_end(ap);

	for (unsigned int i = 0; i < strlen(sbf); i++)
	{
		video_obj->video_buffer[x + i][y] = sbf[i];
	}
}

void write_display()
{
	video_obj->display = true;
}

unsigned int getKey()
{
	return video_obj->key_pressed;
}

void getscrsize(unsigned int &x, unsigned int &y)
{
	x = 80;
	y = 22;
}