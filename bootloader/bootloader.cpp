/*
	:DV company (c) 1997-2016
*/

#include <unistd.h>
#include <curses.h>
#include <vector>
#include <sys/stat.h>

#include "../apps_starter/apps_starter.h"
#include "../windlg/windlg.h"
#include "../configurator/configurator.h"
#include "../desktop/desktop.h"
#include "../fswork/fswork.h"
#include "../screen/screen.h"

using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "");
	init_display();
	init_color();
	init_signals();
	apps_vect.clear();

	/*string test_output;
	DLGSTR teststr = {}; // Только так!!!
	teststr.title = "Pre pre pre ... Alpha";
	teststr.style = 1;
	teststr.line = "Dear user, it's not full version of OS!/nThis is just an example of how might look this OS.";
	msg_win(teststr);
	erase();
	
	vector <string> items;
	teststr.style = 2;
	teststr.border_menu = true;
	teststr.selected = 3;
	// teststr.not_view_scrollbar = true;
	teststr.ymax = 4;
	// teststr.xmax = 6;
	items.insert(items.end(), "White");
	items.insert(items.end(), "Red");
	items.insert(items.end(), "Green");
	items.insert(items.end(), "Blue");
	items.insert(items.end(), "Yellow");
	items.insert(items.end(), "Magenta");
	items.insert(items.end(), "Cyan");
	items.insert(items.end(), "Yellow");
	items.insert(items.end(), "Yellow123234234");

	int key = 0;
	while (key != 27) {
		menu_win(teststr, items);
		key = getch();
		switch (key) {
			case KEY_UP: if (teststr.selected != 1) teststr.selected--; break;
			case KEY_DOWN: if (teststr.selected != teststr.second_border) teststr.selected++; break;
			case '\n': switch (teststr.selected) {
						case 1: teststr.style = WHITE_WIN; break;
						case 2: teststr.style = RED_WIN; break;
						case 3: teststr.style = GREEN_WIN; break;
						case 4: teststr.style = BLUE_WIN; break;
						case 5: teststr.style = YELLOW_WIN; break;
						case 6: teststr.style = MAGENTA_WIN; break;
						case 7: teststr.style = CYAN_WIN; break;
					} break;
		}
	}
	teststr.xpos = teststr.xreturn;
	teststr.ypos = teststr.yreturn;
	teststr.style = 4;
	menu_win(teststr, items);
	getch();*/
	/*DEBUG*/

	/*if (!FileExists("hos_configs")) {
		warning_win("Sorry, I can't find configs directory./nCant't boot...", 0);
		endwin();
		return 32;
	}*/

	main_desktop("user_name");
	endwin();
	return 0;
}