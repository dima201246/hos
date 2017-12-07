#include "../include/isca_alpha.h"
#include "../include/system_defines.h"

#include "./include/video_buf.h"

#include <string.h>

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <vector>

pid_t video_pid;

unsigned int video_buffer[VIDEO_SIZE_X][VIDEO_SIZE_Y];

app_container_strct	*new_video_app_obj,
					*up_obj;

std::vector <app_container_strct> apps_list;

bool video_cycle_run;

void end_video()
{
	pid_t	video_pid = new_video_app_obj->pid_video;
	kill(video_pid, SIGTERM);
	waitpid(video_pid, NULL, WUNTRACED);
}

int init_video_memory()
{
	/*Buffer for add apps to display*/
	int am = shm_open(VIDEO_ADD_APP, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR); // Создание объекта общей памяти

	if (ftruncate(am, sizeof(struct app_container_strct)) == -1) // Задание размера этой памяти
	{
		return VIDEO_CANT_SHARED_MEMORY;
	}

	new_video_app_obj = (app_container_strct*) mmap(NULL, sizeof(struct app_container_strct), PROT_READ | PROT_WRITE, MAP_SHARED, am, 0);	// Подключение общей памяти к переменной
	new_video_app_obj->busy = false;

	return 0;
}

/*void shutdown_video()
{
	for (unsigned int i = 0; i < apps_list.size(); ++i) {
		if ((apps_list[i].point != NULL) && (apps_list[i].point->video_buffer != NULL)) {
			apps_list[i].point
		}
	}
}
*/
void fulling_buffer()	// Заполнение главного видео-буфера
{
	for (unsigned int i = 0; i < apps_list.size(); ++i) {
		add_to_filef("./hos.log", "Print app\n");
		if ((apps_list[i].point != NULL) && (apps_list[i].point->video_buffer != NULL) && (apps_list[i].point->display)) {
			apps_list[i].point->display = false;

			for (unsigned int y = 0; y < VIDEO_SIZE_Y; ++y) {
				for (unsigned int x = 0; x < VIDEO_SIZE_X; ++x) {
					if (apps_list[i].point->video_buffer[x][y] != 0) {
						video_buffer[x][y] = apps_list[i].point->video_buffer[x][y];
					}
				}
			}
		}
	}
}

void video_run()
{
	video_cycle_run = true;

	init_display();
	init_color();

	for (unsigned int y = 0; y < VIDEO_SIZE_Y; ++y)
	{
		for (unsigned int x = 0; x < VIDEO_SIZE_X; ++x)
		{
			video_buffer[x][y] = 0;
		}
	}

	while (video_cycle_run)
	{
		fulling_buffer();
		for (unsigned int y = 0; y < /*VIDEO_SIZE_X*/23; y++)
		{
			for (unsigned int x = 0; x < /*VIDEO_SIZE_X*/80; x++)
			{
				mvprintw(y, x, "%c", (char)video_buffer[x][y]);
			}
		}
		refresh();
		usleep(500000);
	}
	endwin();
}

void hdl(int sig)
{
	if (sig == SIGUSR1)
	{
		new_video_app_obj->busy = true;	// Установка флага о том, что добавление новых приложений пока невозможно
		int tm;

		// app testing operation
		app_container_strct temp_addon_obj;	// Создание временного  объекта для добавления приложения в вектор
		strcpy(temp_addon_obj.name_buf, new_video_app_obj->name_buf);

		temp_addon_obj.pid_app = new_video_app_obj->pid_app;

		tm = shm_open(new_video_app_obj->name_buf, O_RDWR, 0777);
		temp_addon_obj.point = (video_bufer_app_strct*) mmap(NULL, sizeof(struct video_bufer_app_strct), PROT_READ | PROT_WRITE, MAP_SHARED, tm, 0);


		apps_list.insert(apps_list.end(), temp_addon_obj);

		new_video_app_obj->busy = false;	// Разрешение на внесение новых приложений
	}

	if (sig == SIGTERM)
	{
		// shutdown_video();
		video_cycle_run = false;
		endwin();
		shm_unlink(VIDEO_ADD_APP);
		add_to_filef("./test", "Exit..Video\n");
	}
}

int init_video_signal()
{
	struct sigaction act;
	memset(&act, 0, sizeof(act));
	act.sa_handler = hdl;
	sigset_t   set; 
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGTERM);
	// sigaddset(&set, SIGUSR2);
	act.sa_mask = set;
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGTERM, &act, 0);
	// sigaction(SIGUSR2, &act, 0);

	new_video_app_obj->pid_video = getpid();
	return 0;
}

int video_init()
{
	pid_t pid;

	if (init_video_memory() != VIDEO_CANT_SHARED_MEMORY)
	{
		switch(pid = fork()) {
			case -1:	return VIDEO_CANT_FORK_VIDEO;
						break;
			case 0:		init_video_signal();
						video_run();
						break;
			default:	video_pid = pid;
						return VIDEO_OK;
		}
	}
	else
	{
		return VIDEO_CANT_SHARED_MEMORY;
	}

	return VIDEO_OK;
}