//#include "../shutdown/shutdown.h"
#include "../windlg/windlg.h"
#include "../fswork/fswork.h"
#include "../apps_starter/apps_starter.h"

#include "./header/menu_apps.h"

#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

using namespace std;

void open_menu(vector <string>& app_list) {
	DLGSTR menu_panel = {};
	menu_panel.xpos = 1;
	menu_panel.ypos = 1;
	// menu_panel.style = 3;
	menu_panel.border_menu = true;
	bool cycle = true;
	int key;
	while (cycle) {
		menu_win(menu_panel, app_list);
		key = getch();
		switch (key) {
			case 27: cycle = false; break;
			case KEY_UP: if (menu_panel.selected != 1) menu_panel.selected--; break;
			case KEY_DOWN: if (menu_panel.selected != menu_panel.second_border) menu_panel.selected++; break;
			case '\n': app_start(menu_panel.selected, ""); break;
		}
	}
	return;
}

int draw_desktop(int selected, bool open_label, bool new_draw, unsigned int maxX, unsigned int maxY) {
	unsigned x, y;
	if (new_draw) {
		for (x = 0; x < maxX; x++) {
			mvprintw(maxY - 1, x, "-");
			mvprintw(0, x, "-");
		}
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

int work_desktop(vector <string> app_list, string user_name) {
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
							case 0: open_menu(app_list); break;
							case 2: cycle = false; break;
						}
			case 27: if (open_label) open_label = false;
					/*else shutdown_process();*/
					break;
		}
	}
	return 0;
}

int main_desktop(string user_name/*...*/) {
	vector <string> app_list;
	get_apps_list(app_list);
	work_desktop(app_list, user_name);
	return 0;
}