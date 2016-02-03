/*
	:DV company (c) 1997-2016
	!!!DO NOT COPY!!!
	HOS - NOT OPEN SOURCE
*/

// #include "../lang/lang.h"
#include "../windlg/windlg.h"
#include "../configurator/configurator.h"
#include "../desktop/desktop.h"
#include "../fswork/fswork.h"

#include <unistd.h>
// #include <stdio.h>
#include <curses.h>
#include <vector>
//#include <errno.h>

#include <sys/stat.h>
// #include <sys/types.h>


using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "");
	initscr();
	start_color();
	keypad (stdscr, true);
	noecho();
	curs_set(0);
	erase();

	init_pair (0, COLOR_WHITE, COLOR_BLACK);
	init_pair (1, COLOR_BLACK, COLOR_WHITE);
	init_pair (2, COLOR_RED, COLOR_BLACK);
	init_pair (3, COLOR_BLACK, COLOR_RED);
	init_pair (4, COLOR_GREEN, COLOR_BLACK);
	init_pair (5, COLOR_BLACK, COLOR_GREEN);
	init_pair (6, COLOR_BLUE, COLOR_BLACK);
	init_pair (7, COLOR_BLACK, COLOR_BLUE);
	init_pair (8, COLOR_YELLOW, COLOR_BLACK);
	init_pair (9, COLOR_BLACK, COLOR_YELLOW);
	
	timeout(-1);
	string test_output;
	DLGSTR teststr = {}; // Только так!!!
	teststr.title = "Pre pre pre ... Alpha";
	teststr.style = 1;
	teststr.line = "Dear user, it's not full version of OS!/nThis is just an example of how might look this OS.";
	msg_win(teststr);
	erase();
	
	/*DEBUG*/
	vector <string> items;
	teststr.style = 0;
	teststr.border_menu = true;
	teststr.selected = 2;
	teststr.ymax = 5;
	items.insert(items.end(), "test");
	items.insert(items.end(), "test2");
	items.insert(items.end(), "test3");
	items.insert(items.end(), "test4");
	items.insert(items.end(), "test5");
	items.insert(items.end(), "test6");
	items.insert(items.end(), "test7");
	items.insert(items.end(), "test8");
	items.insert(items.end(), "test9");
	items.insert(items.end(), "test10");

	int key = 0;
	while (key != 27) {
		menu_win(teststr, items);
		key = getch();
		switch (key) {
			case KEY_UP: if (teststr.selected != 0) teststr.selected--; break;
			case KEY_DOWN: if (teststr.selected != 10) teststr.selected++; break;
		}
	}
	teststr.xpos = teststr.xreturn;
	teststr.ypos = teststr.yreturn;
	menu_win(teststr, items);
	
	mvprintw(10, 10, "%i", teststr.xreturn);
	mvprintw(11, 10, "%i", teststr.yreturn);
	getch();
	/*DEBUG*/

	/*if (!FileExists("hos_configs")) {
		warning_win("Sorry, I can't find configs directory./nCant't boot...", 0);
		endwin();
		return 32;
	}*/

	// main_desktop("user_name");
	//add_to_file("test", "test");
	endwin();
	return 0;
}