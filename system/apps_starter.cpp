#include "../include/apps_starter.h"

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
void list_process() {
	std::vector <std::string>	apps_names;

	Init_MENSTR(apps_menu);

	getmaxyx(stdscr, apps_menu.posY, apps_menu.posX);

	apps_menu.posX		= apps_menu.posX / 2 - 12;
	apps_menu.posY		= apps_menu.posY / 2;
	apps_menu.posXmax	= 25;

	// Не делаем ничего, вектор если пуст
	if(!apps_vect.empty()) {
		for (unsigned int	i	= 0; i < apps_vect.size(); i++) {
			apps_names.push_back(apps_vect[i].name);
		}

		unsigned int	selected	= menu_win(&apps_menu, "Background applications", apps_names, main_system_color);

		if (selected != 0) {	// процесс спящий мы будим
			endwin();
			fg_job(apps_vect[selected - 1]);
			init_display();
			init_color();
		}
	}
}

int app_start(int number_of_app, char** argv) {
	std::string name_app	= configurator(APPS_FILE, str(number_of_app) + "_app_launcher", "", false);
	std::string path_to_dir	= configurator(APPS_FILE, str(number_of_app) + "_app_path", "", false);
	std::string type_app	= configurator(APPS_FILE, str(number_of_app) + "_app_type", "", false);
	erase();
	endwin();

	int		status;
	pid_t	chpid	= fork();

	job j = {
		.name = configurator(APPS_FILE, str(number_of_app) + "_app_package_name", "", false),
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