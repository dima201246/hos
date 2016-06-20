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

			case '\n':		app_start(menu_panel.selected, NULL);
							return;
							break;
		}
	}

	return;
}

void init_desk_color(int &color, int &sel_color) {
	string			color_str	= configurator("configs/system.conf", "system_color", "0", false);

	if (color_str == "cyan") {
		color		= TEXT_CYAN_BLACK;
		sel_color	= TEXT_BLACK_CYAN;
	} else if (color_str == "blue"){
		color		= TEXT_BLUE_BLACK;
		sel_color	= TEXT_BLACK_BLUE;
	} else if (color_str == "red"){
		color		= TEXT_RED_BLACK;
		sel_color	= TEXT_BLACK_RED;
	} else if (color_str == "yellow"){
		color		= TEXT_YELLOW_BLACK;
		sel_color	= TEXT_BLACK_YELLOW;
	} else if (color_str == "magenta"){
		color		= TEXT_MAGENTA_BLACK;
		sel_color	= TEXT_BLACK_MAGENTA;
	} else if (color_str == "green"){
		color		= TEXT_GREEN_BLACK;
		sel_color	= TEXT_BLACK_GREEN;
	} else {
		color		= TEXT_WHITE_BLACK;
		sel_color	= TEXT_BLACK_WHITE;
	}
}

int draw_desktop(int selected, bool open_label, unsigned int maxX, unsigned int maxY, int color, int sel_color) {
		attron(COLOR_PAIR(color) | A_BOLD);
		for (unsigned int	x	= 0; x < maxX; x++) {
			mvprintw(maxY - 1, x, "-");
			mvprintw(0, x, "-");
		}
		for (unsigned int	y	= 0; y < maxY; y++) {mvprintw(y, 0, "|"); mvprintw(y, maxX - 1, "|");}

		local_time	t_n	= get_time_now();
		mvprintw(0, maxX - 10, "%d:%d:%d", t_n.hours, t_n.min, t_n.sec);
		attroff(COLOR_PAIR(color) | A_BOLD);

		if (selected == 0) attron(COLOR_PAIR(sel_color) | A_BOLD);
		else attron(COLOR_PAIR(color) | A_BOLD);
		mvprintw(0, 1, "Menu");
		if (selected == 0) attroff(COLOR_PAIR(sel_color) | A_BOLD);
		else attroff(COLOR_PAIR(color) | A_BOLD);
		if (selected == 1) attron(COLOR_PAIR(sel_color) | A_BOLD);
		else attron(COLOR_PAIR(color) | A_BOLD);
		mvprintw(0, 6, "Edit");
		if (selected == 1) attroff(COLOR_PAIR(sel_color) | A_BOLD);
		else attroff(COLOR_PAIR(color) | A_BOLD);
		if (selected == 2) attron(COLOR_PAIR(sel_color) | A_BOLD);
		else attron(COLOR_PAIR(color) | A_BOLD);
		mvprintw(0, 11, "Exit");
		if (selected == 2) attroff(COLOR_PAIR(sel_color) | A_BOLD);
		else attroff(COLOR_PAIR(color) | A_BOLD);
	return 0;
}

int work_desktop(vector <string> app_list, string user_name) {
	unsigned int	maxY,
					maxYb		= 0,
					maxX,
					maxXb		= 0;

	bool			cycle		= true,
					open_label	= false;

	int				key_pressed,
					selected	= 0,
					color		= 0,
					sel_color	= 0;

	init_desk_color(color, sel_color);

	while (cycle) {
		getmaxyx(stdscr, maxY, maxX); // Получение размера терминала

		if ((maxX != maxXb) || (maxY != maxYb)) {
			erase();
		}

		timeout(500);
		draw_desktop(selected, open_label, maxX, maxY, color, sel_color);
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

								case 1:	settings(DESKTOP_SETTINGS_FILE);
										init_desk_color(color, sel_color);
										break;

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