#include "../include/isca_alpha.h"
#include "../include/system_defines.h"
#include "../include/apps_starter.h"

#include <errno.h>
#include <stdio.h>
#include <cstring>

std::vector<job> apps_vect;			// Определение вектора запущенных программ
struct termios hos_tmode;			// настройки терминала для hos

char	**init_out_parametr(std::string	parametrs, unsigned int	&count)
{
	unsigned int	space_counter;

	bool			always_read;

	std::string		temp;

	parametrs		+= " ";

	space_counter	= 0;
	always_read		= false;

	temp.clear();

	for (unsigned int	i	= 0; i < parametrs.length(); i++)
	{
		if ((parametrs[i] == '"') && ((i == 0) || (parametrs[i - 1] != '\\')))
		{
			(always_read ? always_read	= false : always_read	= true);
		}

		if ((!always_read) && (parametrs[i] == ' '))
		{
			space_counter++;
		}
	}

	char **out_parametrs_temp = new char* [space_counter + 1];

	out_parametrs_temp[space_counter]	= NULL;

	always_read		= false;
	space_counter	= 0;

	for (unsigned int	i	= 0; i < parametrs.length(); i++)
	{
		if ((parametrs[i] == '"') && ((i == 0) || (parametrs[i - 1] != '\\')))
		{
			(always_read ? always_read	= false : always_read	= true);
		}

		if ((!always_read) && (parametrs[i] == ' '))
		{
			out_parametrs_temp[space_counter]	= new char [temp.length() + 1];
			strcpy(out_parametrs_temp[space_counter], temp.c_str());
			temp.clear();
			space_counter++;
			continue;
		}

		temp	+= parametrs[i];
	}

	count	= space_counter + 1;

	return	out_parametrs_temp;
}

void sighandler(int signo)
{
	if (signo == SIGTSTP)
	{

	}

	if (signo == SIGINT)
	{

	}
}

// Спящего процесса возобновление
void fg_job(job &j)
{
	int status;
	std::vector<job>::iterator it;

	// Терминальной группы главной установка
	j.running = true;
	tcsetpgrp(STDIN_FILENO, j.pid);

	// Спящий процесс будим мы
	kill(-j.pid, SIGCONT);
	waitpid(j.pid, &status, WUNTRACED);

	if(WIFSTOPPED(status))
	{
		j.running = false;
		tcsetpgrp(STDIN_FILENO, getpid());
		tcgetattr(STDIN_FILENO, &j.tmode);
		tcsetattr(STDIN_FILENO, TCSADRAIN, &hos_tmode);
	}

	// Если завершился процесс - удаляем из вектора процессов его
	if(WIFEXITED(status))
	{
		tcsetpgrp(STDIN_FILENO, getpid());
		tcsetattr(STDIN_FILENO, TCSADRAIN, &hos_tmode);

		for(it = apps_vect.begin() ; it < apps_vect.end(); ++it)
			if (it->pid == j.pid)
				apps_vect.erase(it);
	}
}

// Сигналов обработку определяем мы
void init_signals()
{
	signal(SIGINT, &sighandler);
	signal(SIGTSTP, &sighandler);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
}

// Фоновых процессов список отображаем мы
void list_process()
{
	std::vector <std::string>	apps_names;

	Init_MENSTR(apps_menu);

	getmaxyx(stdscr, apps_menu.posY, apps_menu.posX);

	apps_menu.posX		= apps_menu.posX / 2 - 12;
	apps_menu.posY		= apps_menu.posY / 2;
	apps_menu.posXmax	= 25;

	// Не делаем ничего, вектор если пуст
	if(!apps_vect.empty())
	{
		for (unsigned int	i	= 0; i < apps_vect.size(); i++)
		{
			apps_names.push_back(apps_vect[i].name);
		}

		unsigned int	selected	= menu_win(&apps_menu, "Background applications", apps_names, main_system_color);

		if (selected != 0)	// процесс спящий мы будим
		{
			endwin();
			fg_job(apps_vect[selected - 1]);
			init_display();
			init_color();
		}
	}
}

int app_start(int number_of_app, std::string	parametrs)
{
	std::string name_app	= configurator(MAIN_APPS_FILE, str(number_of_app) + "_app_launcher", "", false);
	std::string path_to_dir	= configurator(MAIN_APPS_FILE, str(number_of_app) + "_app_path", "", false);
	std::string type_app	= configurator(MAIN_APPS_FILE, str(number_of_app) + "_app_type", "", false);
	unsigned int	parametrs_count	= 0;

	erase();
	endwin();

	int		status;
	char	**out_parametrs	= NULL;

	pid_t	chpid	= fork();

	if (chpid == 0)
	{
		for (unsigned int	i	= 0; i < name_app.length(); i++)	// Из имени приложения параметры выхватывать пытаемя мы
		{
			if (name_app[i] == ' ')
			{
				std::string app_parametrs;
				app_parametrs	= name_app;
				name_app.erase(i, name_app.length());
				app_parametrs.erase(0, i + 1);

				(parametrs.empty() ? parametrs	= app_parametrs : parametrs.insert(0, app_parametrs + " "));	// В конец параметры добовляем
				break;
			}
		}

		if (!parametrs.empty())	// Параметры если есть какие, массив сделать из них
			out_parametrs	= init_out_parametr(parametrs, parametrs_count);

		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		tcsetpgrp(STDIN_FILENO, getpid());
		chdir(path_to_dir.c_str());
		setpgid(getpid(), getpid());			 	// Создаём группу процессов

		if (execv(name_app.c_str(), out_parametrs) < 0)	// parent process
		{
			init_display();
			init_color();
			DLGSTR	failwin	= {};	// Только так!!!
			failwin.line	= "Can't start app!!!";
			failwin.style	= RED_WIN;
			msg_win(failwin);
			endwin();

			exit(0);
		}
	}
	else
	{
		job j = {
			.name = configurator(MAIN_APPS_FILE, str(number_of_app) + "_app_package_name", "", false),
			.pid = chpid
		};

		j.running = true;

		// В запущенных процессов список процесс помещаем мы
		apps_vect.insert(apps_vect.end(), j);

		waitpid(chpid, &status,WUNTRACED);
		tcsetpgrp(STDIN_FILENO, getpid());
		tcgetattr(STDIN_FILENO, &j.tmode);
		tcsetattr(STDIN_FILENO, TCSADRAIN, &hos_tmode);

		if (WIFSTOPPED(status))	// Если пользователем процесс был остановлен
		{
			apps_vect.back().running = false;
		}

		if(WIFEXITED(status))
		{
			apps_vect.pop_back();
		}

		init_display();
		init_color();
	}

	return 0;
}
