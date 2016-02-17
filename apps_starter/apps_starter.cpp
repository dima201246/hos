#include "apps_starter.h"
#include "../lang/lang.h"
#include "../configurator/configurator.h"

#include <stdio.h>
#include <unistd.h>

#include <curses.h>

using namespace std;

int app_start(int number_of_app, const char* parametrs) {
	string full_path = configurator(APPS_FILE, str(number_of_app) + "_app_path", "", false) + "/" + configurator(APPS_FILE, str(number_of_app) + "_app_launcher", "", false);
	execl(full_path.c_str(), parametrs, NULL);
	// fork(full_path.c_str(), parametrs, NULL);
	printw("%s", full_path.c_str()); getch();
	return 0;
}