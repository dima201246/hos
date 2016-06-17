#include "desktop.h"

using namespace std;

void open_menu(vector <string>& app_list) {
	DLGSTR		menu_panel	= {};

	bool	cycle			= true;

	int		key;

	menu_panel.xpos			= 1;
	menu_panel.ypos			= 1;
	menu_panel.style		= BLUE_WIN;
	menu_panel.border_menu	= true;	

	while (cycle) {
		menu_win(menu_panel, app_list);
		key	= getch();
		
		switch (key) {
			case 27:		cycle = false;
							break;

			case KEY_UP:	if (menu_panel.selected != 1)
								menu_panel.selected--;
							break;

			case KEY_DOWN:	if (menu_panel.selected != menu_panel.second_border)
								menu_panel.selected++;
							break;

			case '\n':		app_start(menu_panel.selected, "");
							return;
							break;
		}
	}

	return;
}

int draw_desktop(int selected, bool open_label, unsigned int maxX, unsigned int maxY) {
		for (unsigned int	x	= 0; x < maxX; x++) {
			mvprintw(maxY - 1, x, "-");
			mvprintw(0, x, "-");
		}
		for (unsigned int	y	= 0; y < maxY; y++) {mvprintw(y, 0, "|"); mvprintw(y, maxX - 1, "|");}

		local_time	t_n	= get_time_now();
		mvprintw(0, maxX - 10, "%d:%d:%d", t_n.hours, t_n.min, t_n.sec);

		if (selected == 0) attron(COLOR_PAIR(TEXT_BLACK_WHITE) | A_BOLD);
		mvprintw(0, 1, "Menu");
		if (selected == 0) attroff(COLOR_PAIR(TEXT_BLACK_WHITE) | A_BOLD);
		if (selected == 1) attron(COLOR_PAIR(TEXT_BLACK_WHITE) | A_BOLD);
		mvprintw(0, 6, "Edit");
		if (selected == 1) attroff(COLOR_PAIR(TEXT_BLACK_WHITE) | A_BOLD);
		if (selected == 2) attron(COLOR_PAIR(TEXT_BLACK_WHITE) | A_BOLD);
		mvprintw(0, 11, "Exit");
		if (selected == 2) attroff(COLOR_PAIR(TEXT_BLACK_WHITE) | A_BOLD);
	return 0;
}

int work_desktop(vector <string> app_list, string user_name) {
	unsigned int maxY, maxYb = 0, maxX, maxXb = 0;
	bool cycle = true, open_label = false;
	int key_pressed, selected = 0;
	while (cycle) {
		getmaxyx(stdscr, maxY, maxX); // Получение размера терминала

		if ((maxX != maxXb) || (maxY != maxYb)) {
			erase();
		}

		timeout(0);
		draw_desktop(selected, open_label, maxX, maxY);
		key_pressed = getch();
		switch (key_pressed) {
			case KEY_RIGHT:	if (selected != 2)
								selected++;
							break;

			case KEY_LEFT:	if (selected != 0)
								selected--;
							break;

			case '\n':		switch (selected) {
								case 0:	open_menu(app_list);
										break;

								case 1:	break;

								case 2:	cycle	= false;
										break;
							}
							break;

			case 27:		if (open_label) {
								open_label	= false;
							}
							/*else shutdown_process();*/
							break;
		}
	}

	return 0;
}

int main_desktop(string user_name/*...*/) {
	vector <string>	app_list;
	get_apps_list(app_list);
	work_desktop(app_list, user_name);
	return 0;
}