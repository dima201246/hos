#include "../include/desktop.h"

#define TAB		9

using namespace std;

void open_menu(vector <string>& app_list) {
	Init_MENSTR(menu_panel);

	menu_panel.posX				= 1;
	menu_panel.posY				= 1;
	menu_panel.animation_delay	= 100;

	unsigned int	selected_menu	= menu_win(&menu_panel, "", app_list, main_system_color);

	if (selected_menu) {
		app_start(selected_menu, NULL);
	}
}

int draw_desktop(int selected, bool open_label, unsigned int maxX, unsigned int maxY, int color, int sel_color, bool	show_clock) {
		attron(COLOR_PAIR(color) | A_BOLD);
		for (unsigned int	x	= 0; x < maxX; x++) {
			mvprintw(maxY - 1, x, "-");
			mvprintw(0, x, "-");
		}
		for (unsigned int	y	= 0; y < maxY; y++) {mvprintw(y, 0, "|"); mvprintw(y, maxX - 1, "|");}

		if (show_clock) {
			local_time	t_n	= get_time_now();
			int		time_fixer;

			if (conf("time_style", main_config_base) == "12") {
				time_fixer	= 2;
				t_n.hours	+= 5;

				if ((t_n.hours <= 12 ? t_n.hours : t_n.hours - 12) < 10) {
					mvprintw(0, maxX - 12, "0%d", (t_n.hours <= 12 ? t_n.hours : t_n.hours - 12));
				} else {
					mvprintw(0, maxX - 12, "%d", (t_n.hours <= 12 ? t_n.hours : t_n.hours - 12));
				}

				if (t_n.hours <= 12) {
					mvprintw(0, maxX - 4, "AM");
				} else {
					mvprintw(0, maxX - 4, "PM");
				}
			} else {
				time_fixer	= 0;

				if (t_n.hours < 10) {
					mvprintw(0, maxX - 10, "0%d", t_n.hours);
				} else {
					mvprintw(0, maxX - 10, "%d", t_n.hours);
				}
			}

			if (t_n.min < 10) {
				mvprintw(0, maxX - 8 - time_fixer, ":0%d", t_n.min);
			} else {
				mvprintw(0, maxX - 8 - time_fixer, ":%d", t_n.min);
			}

			if (t_n.sec < 10) {
				mvprintw(0, maxX - 5 - time_fixer, ":0%d", t_n.sec);
			} else {
				mvprintw(0, maxX - 5 - time_fixer, ":%d", t_n.sec);
			}
		}

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
					open_label	= false,
					show_clock;

	int				key_pressed,
					selected	= 0,
					color		= 0,
					sel_color	= 0;

	get_normal_inv_color(conf("system_color", main_config_base), color, sel_color);

	if (conf("clock_on_desktop", main_config_base) == "1") {
		show_clock	= true;
	} else {
		show_clock	= false;
	}

	while (cycle) {
		getmaxyx(stdscr, maxY, maxX); // Получение размера терминала

		if ((maxX != maxXb) || (maxY != maxYb)) {
			erase();
		}

		if (show_clock) {
			timeout(500);
		} else {
			timeout(-1);
		}

		draw_desktop(selected, open_label, maxX, maxY, color, sel_color, show_clock);

		key_pressed	= getch();

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

								case 1:	settings(MAIN_SETFILE);
										get_normal_inv_color(conf("system_color", main_config_base), color, sel_color);
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

			case TAB:		list_process();
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