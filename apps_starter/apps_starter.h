#ifndef APPS_STARTER_H
#define APPS_STARTER_H

	#include <wait.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <unistd.h>
	#include <signal.h>

	#include "../lang/lang.h"
	#include "../configurator/configurator.h"
	#include "../windlg/windlg.h"
	#include "../screen/screen.h"


	#define APPS_FILE "./apps/apps.list"
	#define APPS_DIR "./apps/" 	// Внимание, всегда должна оканчиваться слешем!!!

	struct job {				// Структура запущенной программы
		std::string	name;		// Имя программы
		pid_t		pid;		// PID программы
		bool		running;	// Работает ли процесс или он остановлен
	};

	extern	std::vector<job> apps_vect;

	/* Инициализация обработки сигналов */
	void init_signals(); 

	/* параметры: номер выбранного элемента в списке приложений
	 и параметры, передаваемые в запускаемую программу (массив строк) */
	int app_start(int, char**);			

#endif