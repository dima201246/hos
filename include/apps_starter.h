#ifndef APPS_STARTER_H
#define APPS_STARTER_H

	#include <wait.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <unistd.h>
	#include <signal.h>
	#include <termios.h>
	#include <string>
	#include <vector>

	struct job						// Структура запущенной программы
	{
		std::string		name;		// Имя программы
		pid_t			pid;		// PID программы
		struct termios	tmode;		// Настройки терминала для данной программы
		bool			running;	// Работает ли процесс или он остановлен
	};

	extern	struct termios		hos_tmode;
	extern	std::vector<job>	apps_vect;

	/* Инициализация обработки сигналов */
	void init_signals(); 

	/* параметры: номер выбранного элемента в списке приложений
	 и параметры, передаваемые в запускаемую программу (массив строк) */
	int app_start(int, std::string);

	void list_process();

#endif