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

void init_signals()
{
	signal(SIGINT, &sighandler);
	signal(SIGTSTP, &sighandler);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
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

	apps_vect.insert(apps_vect.end(), j);

	if (chpid == 0) {
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		tcsetpgrp(STDIN_FILENO, getpid());
		chdir(path_to_dir.c_str());
		setpgid(getpid(), getpid());			 	// Создаём группу процессов
		if (execv(name_app.c_str(), argv) == -1) 	// parent process
			exit(0);
	} else {
		waitpid(chpid, &status,WUNTRACED);
		tcsetpgrp(STDIN_FILENO, getpid());
		tcgetattr(STDIN_FILENO, &j.tmode);
		tcsetattr(STDIN_FILENO, TCSADRAIN, &hos_tmode);
		init_display();
		init_color();
	}
	return 0;
}