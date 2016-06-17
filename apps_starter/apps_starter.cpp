#include "apps_starter.h"

int app_start(int number_of_app, const char* parametrs) {
	std::string name_app	= configurator(APPS_FILE, str(number_of_app) + "_app_launcher", "", false);
	std::string path_to_dir	= configurator(APPS_FILE, str(number_of_app) + "_app_path", "", false);
	erase();
	endwin();

	int		status;
	pid_t	chpid	= fork();

	if (chpid == 0) {
		chdir(path_to_dir.c_str());
		if (execl(name_app.c_str(), parametrs, NULL) == -1) // parent process
			exit(0);
	} else {
		waitpid(chpid,&status,WUNTRACED);
		init_display();
		init_color();
	}
	return 0;
}