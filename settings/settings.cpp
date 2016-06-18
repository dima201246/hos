#include "settings.h"

using namespace std;

bool load_item(vector <string> setfile_vec, unsigned int num, string &name_item, string &comment_item, string &type_item, string &parametr_config_item, string &path_to_conf_item) {
	string temp;
	attron(COLOR_PAIR(TEXT_RED_BLACK) | A_BOLD);

	if ((temp = conf(str(num) + "_item", setfile_vec)) == "0x1") {
		mvprintw(0, 0, "Setfile is incorrect! Not found item parametr!");
		getch();
		return false;
	} else {
		name_item	= temp;
	}

	if ((temp = conf(str(num) + "_item_comment", setfile_vec)) == "0x1") {
		mvprintw(0, 0, "Setfile is incorrect! Not found item_comment parametr!");
		getch();
		return false;
	} else {
		comment_item	= temp;
	}

	if ((temp = conf(str(num) + "_type_input", setfile_vec)) == "0x1") {
		mvprintw(0, 0, "Setfile is incorrect! Not found type_input parametr!");
		getch();
		return false;
	} else {
		type_item	= temp;
	}

	if ((temp = conf(str(num) + "_parametr_config", setfile_vec)) == "0x1") {
		mvprintw(0, 0, "Setfile is incorrect! Not found parametr_config parametr!");
		getch();
		return false;
	} else {
		parametr_config_item	= temp;
	}

	if ((temp = conf(str(num) + "_conf_file", setfile_vec)) == "0x1") {
		mvprintw(0, 0, "Setfile is incorrect! Not found conf_file parametr!");
		getch();
		return false;
	} else {
		path_to_conf_item	= temp;
	}

	attroff(COLOR_PAIR(TEXT_RED_BLACK) | A_BOLD);
}

int settings(string	path_to_settings_file) {
	erase();

	vector <string>	setfile_vec;
	load_to_vector(path_to_settings_file, setfile_vec);

	unsigned int	maxX,
					maxY,
					selected, // Номер выделенного пункта
					all_items, //Сколько всего будет пунктов
					i;

	bool			cycle;

	string			temp,
					name_item,
					comment_item,
					type_item,
					parametr_config_item,
					path_to_conf_item;

	/*LANG ZONE START*/
	string	settings_lng	= "Settings";
	/*LANG ZONE END*/

	getmaxyx(stdscr, maxY, maxY);

	timeout(-1);

	if ((temp = conf("all_items", setfile_vec)) == "0x1") {
		printw("Setfile is incorrect! Not found all_items parametr!\n");
		getch();
		return -1;
	} else {
		all_items	= atoi(temp.c_str());
	}

	cycle		= true;

	for (i	= 0; i < maxX; i++, mvprintw(0, i, "-"), mvprintw(maxY - 1, i, "-")); // Рисование верхней и нижней рамок

	/*while (cycle) {
		for (i	= 1; i <= all_items; i++) {
			
			if (conf(str(i) + "_type_input", setfile_vec) == "bool") {
				if (llength(conf(str(i) + "_type_input", setfile_vec)))
			}

		}
	}*/

	return 0;
}