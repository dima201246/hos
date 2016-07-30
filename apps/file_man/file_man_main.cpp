#include "../../include/isca_alpha.h"

using namespace std;

string title_path_fixer(unsigned int maxX, string title_path) {
	if (llength(title_path) > maxX / 2 - 2) {	// ??TEMP?? Разъясни что здесь творится
		while (llength(title_path) + 3 > (maxX / 2 - 2)) // Отвечаю - это обрезка полного пути, он выводится в шапке,
			title_path.erase(0, 1); // если он слишком длинный начало обрезается и вставляется три точки
		title_path.insert(0, "...");
	}

	return title_path;
}

bool menu_prop(MENSTR	panel_str, vector <string>	file_list, vector <FILEINFO>	list_of_files, string	&panel_path) {
	Init_MENSTR(menu_prop_str);

	vector <string>	menu_prop_list;

	menu_prop_list.push_back("Open");
	menu_prop_list.push_back("Rename");
	menu_prop_list.push_back("Copy");
	menu_prop_list.push_back("Cut");
	menu_prop_list.push_back("Delete");
	menu_prop_list.push_back("Info");

	menu_prop_str.posX	= panel_str.returned_x;
	menu_prop_str.posY	= panel_str.returned_y;

	switch (menu_win(&menu_prop_str, "", menu_prop_list, BLUE_WIN)) {
		case 1:	panel_path += file_list[panel_str.returned_selected] + "/";
				return true;
				break;
	}
}

void interface_fm() {
	Init_MENSTR(left_panel_str);
	Init_MENSTR(right_panel_str);

	vector <string>		fv_left_panel;
	vector <string>		fv_right_panel;

	vector <FILEINFO>	list_of_files_left;
	vector <FILEINFO>	list_of_files_right;

	fv_left_panel.push_back("TEST0");
	fv_left_panel.push_back("TEST1");
	fv_left_panel.push_back("TEST2");
	fv_right_panel.push_back("TEST10");
	fv_right_panel.push_back("TEST11");
	fv_right_panel.push_back("TEST12");

	unsigned int	maxX,
					maxY;
					/*left_selected,
					right_selected;*/

	int				key_presed,
					state;

	bool			cycle,
					update_fs;

	string			left_panel_path,
					right_panel_path;

	getmaxyx(stdscr, maxY, maxX);

	// left_panel_str.posY		= right_panel_str.posY	= 1;
	right_panel_str.posX	= maxX / 2 + 1;
	left_panel_str.posYmax	= right_panel_str.posYmax	= maxY;
	left_panel_str.posXmax	= maxX / 2 - 2;
	right_panel_str.posXmax	= (maxX - maxX / 2) - 2;
	right_panel_str.redraw	= true;

	left_panel_path			= right_panel_path	= "/";

	cycle					= true;
	update_fs				= true;

	state					= 1;

	/*
	STATE:
		1 - SELECTED LEFT PANEL
		2 - SELECTED RIGHT PANEL
		3 - SELECTED MENU
	*/

	while (cycle) {

		if (update_fs) {
			get_files(left_panel_path, list_of_files_left); // Загрузка списка файлов
			get_files(right_panel_path, list_of_files_right); // Загрузка списка файлов

			files_sort_by('n', list_of_files_left); // Сортировка
			files_sort_by('n', list_of_files_right); // Сортировка

			fv_in_strv_out(list_of_files_left, fv_left_panel);
			fv_in_strv_out(list_of_files_right, fv_right_panel);

			update_fs	= false;
		}

		switch (state) {
			case 1:	left_panel_str.redraw	= false;
					right_panel_str.redraw	= true;
					break;

			case 2:	left_panel_str.redraw	= true;
					right_panel_str.redraw	= false;
					break;
		}

		if (state == 1) {
			menu_win(&right_panel_str, title_path_fixer(maxX, right_panel_path), fv_right_panel, WHITE_WIN);
			menu_win(&left_panel_str, title_path_fixer(maxX, left_panel_path), fv_left_panel, BLUE_WIN);
		} else {
			menu_win(&left_panel_str, title_path_fixer(maxX, left_panel_path), fv_left_panel, WHITE_WIN);
			menu_win(&right_panel_str, title_path_fixer(maxX, right_panel_path), fv_right_panel, BLUE_WIN);
		}

		left_panel_str.std_selected		= left_panel_str.returned_selected + 1;
		right_panel_str.std_selected	= right_panel_str.returned_selected + 1;

		if ((left_panel_str.returned_key == H_KEY_TAB) || (right_panel_str.returned_key == H_KEY_TAB)) {	// Смена панели
			if (state != 2) {
				state++;
			} else {
				state	= 1;
			}
		}

		if ((left_panel_str.returned_key == H_KEY_ENTER) || (right_panel_str.returned_key == H_KEY_ENTER)) {
			if (state == 1) {
				update_fs	= menu_prop(left_panel_str, fv_left_panel, list_of_files_left, left_panel_path);
			} else {
				update_fs	= menu_prop(right_panel_str, fv_right_panel, list_of_files_right, right_panel_path);
			}
		}

		/*if ((left_panel_str.returned_key == H_KEY_ESC) || (right_panel_str.returned_key == H_KEY_ESC)) {
			cycle	= false;
		}*/
	}
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "");

	init_display();
	init_color();
	interface_fm();
	endwin();
	return 0;
}
