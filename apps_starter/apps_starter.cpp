#include "apps_starter.h"

std::vector<job> apps_vect;			// Определение вектора запущенных программ
struct termios hos_tmode;			// настройки терминала для hos

void sighandler(int signo)
{
	if (signo == SIGTSTP) {

	}

	if (signo == SIGINT) {
		
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

	if(WIFSTOPPED(status)) {
		j.running = false;
		tcsetpgrp(STDIN_FILENO, getpid());
		tcgetattr(STDIN_FILENO, &j.tmode);
		tcsetattr(STDIN_FILENO, TCSADRAIN, &hos_tmode);
	}

	// Если завершился процесс - удаляем из вектора процессов его
	if(WIFEXITED(status)) {
		tcsetpgrp(STDIN_FILENO, getpid());
		tcsetattr(STDIN_FILENO, TCSADRAIN, &hos_tmode);
		for(it = apps_vect.begin() ; it != apps_vect.end(); it++)
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
void list_process() {
	timeout(-1);

	std::vector <std::string>	apps_names;

	DLGSTR						apps_dlg	= {};

	unsigned int				maxX,
								maxY;

	int							key_pressed;

	getmaxyx(stdscr, maxY, maxX);

	apps_dlg.title			= "Background applications";
	apps_dlg.style			= RED_WIN;
	apps_dlg.xpos			= maxX / 2 - llength(apps_dlg.title) / 2;
	apps_dlg.ypos			= maxY / 2;
	apps_dlg.ymax			= maxY / 2;
	apps_dlg.border_menu	= true;

	// Не делаем ничего, вектор если пуст
	if(!apps_vect.empty()) {
		for (unsigned int	i	= 0; i < apps_vect.size(); i++) {
			apps_names.push_back(apps_vect[i].name);
		}

		key_pressed	= 0;

		while (key_pressed != 27) {
			menu_win(apps_dlg, apps_names);
			key_pressed	= getch();					// пользователя ввод обрабатываем мы

			switch (key_pressed) {
				case KEY_UP:	if (apps_dlg.selected != 0)
									apps_dlg.selected--;
								break;

				case KEY_DOWN:	if (apps_dlg.selected != apps_names.size())
									apps_dlg.selected++;
								break;

				case '\n':		// процесс спящий мы будим
								endwin();
								fg_job(apps_vect[apps_dlg.selected - 1]);
								init_display();
								init_color();
								break;
			}
		}
	}
}

int app_start(int number_of_app, char** argv) {
	std::string name_app	= configurator(APPS_FILE, str(number_of_app) + "_app_launcher", "", false);
	std::string path_to_dir	= configurator(APPS_FILE, str(number_of_app) + "_app_path", "", false);
	erase();
	endwin();

	int		status;
	pid_t	chpid	= fork();

	job j = {
		.name = name_app,
		.pid = chpid
	};

	j.running = true;

	// В запущенных процессов список процесс помещаем мы
	apps_vect.insert(apps_vect.end(), j);

	if (chpid == 0) {
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		tcsetpgrp(STDIN_FILENO, getpid());
		chdir(path_to_dir.c_str());
		setpgid(getpid(), getpid());			 	// Создаём группу процессов
		if (execl(name_app.c_str(), "", NULL) == -1) 	// parent process
			exit(0);
	} else {
		waitpid(chpid, &status,WUNTRACED);
		tcsetpgrp(STDIN_FILENO, getpid());
		tcgetattr(STDIN_FILENO, &j.tmode);
		tcsetattr(STDIN_FILENO, TCSADRAIN, &hos_tmode);

		if (WIFSTOPPED(status)) {	/* Если пользователем процесс был остановлен */
			apps_vect.back().running = false;
		}

		if(WIFEXITED(status)) {
			apps_vect.pop_back();
		}

		init_display();
		init_color();
	}
	return 0;
}