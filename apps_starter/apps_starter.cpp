#include "apps_starter.h"
#include "../lang/lang.h"
#include "../configurator/configurator.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <curses.h>

using namespace std;

int app_start(int number_of_app, const char* parametrs) {
	string full_path = configurator(APPS_FILE, str(number_of_app) + "_app_path", "", false) + "/" + configurator(APPS_FILE, str(number_of_app) + "_app_launcher", "", false);
	erase();
	/*TEST*/
	pid_t pid = fork();
	if (pid == 0)
		execl(full_path.c_str(), parametrs, NULL); // parent process
	else {
		erase();
		refresh();
	}
	/*TEST*/
	return 0;
}
