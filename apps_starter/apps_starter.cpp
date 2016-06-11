#include "../lang/lang.h"
#include "../configurator/configurator.h"
#include "../windlg/windlg.h"
#include "../screen/screen.h"
#include "apps_starter.h"

int app_start(int number_of_app, const char* parametrs) {
	std::string full_path = configurator(APPS_FILE, str(number_of_app) + "_app_path", "", false) + "/" + configurator(APPS_FILE, str(number_of_app) + "_app_launcher", "", false);

	erase();
	endwin();

	int		status;
	pid_t	chpid	= fork();

	if (chpid == 0) {
		if (execl(full_path.c_str(), parametrs, NULL) == -1) // parent process
			exit(0);
	} else {
		waitpid(chpid,&status,WUNTRACED);
		init_display();
	}
	return 0;
}