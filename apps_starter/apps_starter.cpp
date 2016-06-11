#include "apps_starter.h"
#include "../lang/lang.h"
#include "../configurator/configurator.h"
#include "../windlg/windlg.h"
#include "../libscreen/libscreen.h"
#include <wait.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <curses.h>

using namespace std;

int stat;

/*int app_start(int number_of_app, const char* parametrs) {
	string full_path = configurator(APPS_FILE, str(number_of_app) + "_app_path", "", false) + "/" + configurator(APPS_FILE, str(number_of_app) + "_app_launcher", "", false);
	erase();
	pid_t pid = fork();
	if (pid == 0)
		execl(full_path.c_str(), parametrs, NULL); // parent process
	else {
		erase();
		wait(&stat);
		refresh();
		// getch();
		
		// timeout(-1);
		// string test_output;
		// DLGSTR teststr = {}; // Только так!!!
		// teststr.title = "Pre pre pre ... Alpha";
		// teststr.style = 1;
		// teststr.line = "Dear user, it's not full version of OS!/nThis is just an example of how might look this OS.";
		// msg_win(teststr);
		// update_screen();
	}
	// TEST
	return 0;
}*/

int app_start(int number_of_app, const char* parametrs) {
	string full_path = configurator(APPS_FILE, str(number_of_app) + "_app_path", "", false) + "/" + configurator(APPS_FILE, str(number_of_app) + "_app_launcher", "", false);
	erase();
	endwin();

	int		status;
	pid_t	chpid = fork();

	if (chpid == 0) {
		execl(full_path.c_str(), parametrs, NULL); // parent process
	} else {
		waitpid(chpid,&status,WUNTRACED);
		initscr();
		start_color();
		keypad (stdscr, true);
		noecho();
		curs_set(0);
		erase();
	}
	return 0;
}