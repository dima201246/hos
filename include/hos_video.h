#ifndef HOS_VIDEO_H
#define HOS_VIDEO_H

#include "../include/system_defines.h"

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <cstdarg>

#define STRING_BUF_SIZE 256

#pragma pack(push, 1)
struct video_bufer_app_strct	// Структура принадлежащяя приложению и содержащяя его видео память
{
	unsigned int video_buffer[VIDEO_SIZE_X][VIDEO_SIZE_Y];
	unsigned int key_pressed;	// Для получения нажатия кнопки
	bool	minimized,	// Если приложение свёрнуто
			display,	// Для обновления видео буфера
			warning;
};

struct app_container_strct	// Контейнер для добавления нового приложения в видео память
{
	char name_app[STRING_BUF_SIZE];	// Имя приложения, берётся из конфигурационного файла
	char name_buf[STRING_BUF_SIZE];	// Имя буфера, генерируется автоматически
	pid_t pid_app;	// Идентификатор процесса
	bool busy;	// Занятость контейнера
	video_bufer_app_strct *point;	// Ссылка на видео память приложения
};
#pragma pack(pop)

void mvprint(unsigned int y, unsigned int x, std::string fmt, ...);
void getscrsize(unsigned int &y, unsigned int &x);
void setVideoBufName(std::string name);
unsigned int getKey();
void write_display();
void screen_init();

#endif