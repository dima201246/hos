//#include "../shutdown/shutdown.h"
#include "../windlg/windlg.h"
#include "../fswork/fswork.h"


#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <curses.h>

using namespace std;

string local_user;

int draw_desktop(int selected, bool open_label, bool new_draw, unsigned int maxX, unsigned int maxY) {
	unsigned x, y;
	if (new_draw) {
		for (x = 15; x < maxX; x++) mvprintw(0, x, "-");
		for (x = 0; x < maxX; x++) mvprintw(maxY - 1, x, "-");
		for (y = 0; y < maxY; y++) {mvprintw(y, 0, "|"); mvprintw(y, maxX - 1, "|");}
	}
		if (selected == 0) attron(COLOR_PAIR(1) | A_BOLD); // Белый цвет
		mvprintw(0, 1, "Menu");
		if (selected == 0) attroff(COLOR_PAIR(1) | A_BOLD);
		if (selected == 1) attron(COLOR_PAIR(1) | A_BOLD); // Белый цвет
		mvprintw(0, 6, "Edit");
		if (selected == 1) attroff(COLOR_PAIR(1) | A_BOLD);
		if (selected == 2) attron(COLOR_PAIR(1) | A_BOLD); // Белый цвет
		mvprintw(0, 11, "Exit");
		if (selected == 2) attroff(COLOR_PAIR(1) | A_BOLD);
	return 0;
}

int work_desktop() {
	unsigned int maxY, maxYb = 0, maxX, maxXb = 0;
	bool cycle = true, open_label = false, new_draw = false;
	int key_pressed, selected = 2;
	while (cycle) {
		getmaxyx(stdscr, maxY, maxX); // Получение размера терминала
		if ((maxX != maxXb) || (maxY != maxYb)) {
			new_draw = true;
			erase();
		}
		timeout(0);
		draw_desktop(selected, open_label, new_draw, maxX, maxY);
		new_draw = false;
		key_pressed = getch();
		switch (key_pressed) {
			case KEY_RIGHT: if (selected != 2) selected++; break;
			case KEY_LEFT: if (selected != 0) selected--; break;
			case '\n': switch (selected) {
							case 2: cycle = false; break;
							// default: warning_win("Ooops... It's not work...", 0); /*open_label = true;*/ break;
						}
			case 27: if (open_label) open_label = false;
					/*else shutdown_process();*/
					break;
		}
	}
	return 0;
}

int main_desktop(string user_name/*...*/) {
	local_user = user_name;
	work_desktop();
	return 0;
}