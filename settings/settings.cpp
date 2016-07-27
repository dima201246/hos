#include "settings_head.h"

struct conf_str {
	string			path_to_configuration_file; // Путь к конфигурационному файлу
	vector <string>	point_to_vector; // Указатель на вектор с конфигурационным файлом
};

struct items_list_str {
	string			name_item,
					comment_item,
					type_item,
					path_to_conf,
					parametr,
					value_item,
					action;

	vector <string>	list_values;
};

void load_list_values(string	values_line, vector <string>	&list_values) {
	list_values.clear();

	string	temp_vl;

	temp_vl.clear();

	values_line	+= ",";

	for (unsigned int	vl	= 0; vl < llength(values_line); vl++) {
		if ((values_line[vl] == ',') && (vl != 0) && (values_line[vl - 1] != '\\') && (!temp_vl.empty())) {
			list_values.insert(list_values.end(), temp_vl);
			temp_vl.clear();
			continue;
		}

		if ((values_line[vl] == '\\') && (values_line[vl + 1] == ','))
			continue;

		temp_vl	+= values_line[vl]; 
	}
}

void draw_border(string	settings_lng, string	set_name, unsigned int	maxX, unsigned int	maxY) {
	erase();

	unsigned int	i	= 0;

	attron(COLOR_PAIR(main_system_color) | A_BOLD);
	
	for (i	= 0; i < maxX; i++, mvprintw(0, i, "-"), mvprintw(maxY - 1, i, "-")); // Рисование верхней и нижней рамок

	for (i	= 0; i < maxY; i++, mvprintw(i - 1, 0, "|"), mvprintw(i - 1, maxX - 1, "|")); // Рисование левой и правой рамок

	attroff(COLOR_PAIR(main_system_color) | A_BOLD);

	if (llength(settings_lng) + llength(set_name) > maxX - 4) {
		set_name.erase(maxX - 7 - llength(settings_lng), llength(set_name));
		set_name	+= "...";
	}

	attron(COLOR_PAIR(main_system_color_selection) | A_BOLD);
	mvprintw (0, 2, "%s %s", set_name.c_str(), settings_lng.c_str());
	attroff(COLOR_PAIR(main_system_color_selection) | A_BOLD);
}

bool search_in_struct(string path, vector <conf_str> conf_vec, conf_str &out_struct) { // Поиск в векторе нужного конфигурационного файла
	unsigned int	v;
	conf_str		s_temp;

	for (v	= 0; v < conf_vec.size(); v++) {
		s_temp	= conf_vec[v];

		if (path == s_temp.path_to_configuration_file) {
			out_struct	= s_temp;
			return true;
		}
	}
	return false;
}

bool load_item(	vector <string>	setfile_vec,
				unsigned int	num,
				string			&name_item,
				string			&comment_item,
				string			&type_item,
				string			&parametr_config_item,
				string			&path_to_conf_item,
				string			&list,
				string			&action) {
	string	temp;
	DLGSTR	failwin	= {};
	failwin.style	= RED_WIN;
	failwin.title	= "Error reading settings file on " + str(num) + " item";

	bool	action_type	= false;

	if ((temp = conf(str(num) + "_item", setfile_vec)) == "0x1") {
		failwin.line	= "Setfile is incorrect! Not found item parametr!";
		msg_win(failwin);
		return false;
	} else {
		name_item	= temp;
	}

	if ((temp = conf(str(num) + "_item_comment", setfile_vec)) == "0x1") {
		comment_item.clear();
	} else {
		comment_item	= temp;
	}

	if ((temp = conf(str(num) + "_type_input", setfile_vec)) == "0x1") {
		failwin.line	= "Setfile is incorrect! Not found type_input parametr!";
		msg_win(failwin);
		return false;
	} else {
		type_item	= temp;
		if (type_item == "action")
			action_type	= true;
	}

	if ((!action_type) && ((temp = conf(str(num) + "_parametr_config", setfile_vec)) == "0x1")) {
		failwin.line	= "Setfile is incorrect! Not found parametr_config parametr!";
		msg_win(failwin);
		return false;
	} else {
		parametr_config_item	= temp;
	}

	if ((!action_type) && ((temp = conf(str(num) + "_conf_file", setfile_vec)) == "0x1")) {
		failwin.line	= "Setfile is incorrect! Not found conf_file parametr!";
		msg_win(failwin);
		return false;
	} else {
		path_to_conf_item	= temp;
	}

	if ((temp = conf(str(num) + "_action", setfile_vec)) == "0x1") {
		action.clear();
	} else {
		action				= temp;
	}

	if ((temp = conf(str(num) + "_list", setfile_vec)) == "0x1") {
		list.clear();
	} else {
		list				= temp;
	}

	return true;
}

int settings(string	path_to_settings_file) {
	DLGSTR					failwin	= {};
	failwin.style			= RED_WIN;

	if (!FileExists(path_to_settings_file)) {
		failwin.title		= "Can't find setfile!";
		failwin.line		= path_to_settings_file;
		msg_win(failwin);
		return -1;
	}

	vector <string>			setfile_vec, // Вектор для основного файла настроек
							temp_vec;

	vector <conf_str>		confs_vec; // Вектор который содержит указатели на загруженные конфигурационные файлы

	vector <items_list_str>	items_list;

	load_to_vector(path_to_settings_file, setfile_vec);
	items_list.clear();
	confs_vec.clear();

	unsigned int	maxX,
					maxY,
					selected,							// Номер выделенного пункта
					all_items,							//Сколько всего будет пунктов
					i,
					j,
					first_write,						// С кокого элемента будет выводиться
					last_write,							// До какого, включительно будет выводиться
					position_write,						// С какой строки начинать писать
					cut_selected_name,					// Обрезка выделенного пункта
					cut_selected_comment,				// -//-
					wait_selected_name,					// Задержка при достижении начала или конца строки
					wait_selected_comment,				// -//-
					right_border;						// С какой позиции писать значение

	bool			cycle,
					want_to_moving_selected_name,		// Надо ли вообще проматывать выбранный пункт
					want_to_moving_selected_comment,	// Надо ли вообще проматывать выбранный пункт
					animation_move;						// Двигать ли длинные строки при выделении

	string			temp,
					name_item,							// Имя пункта
					comment_item,						// Комментарий пункта
					type_item,							// Тип пункта
					parametr_config_item,				// Параметр для изменения
					path_to_conf_item,					// Путь к конфигурационному файлу для этого пункта
					selected_name,						// Имя выделенного пункта
					selected_comment,					// Комментарий выделенного пункта
					selected_type,						// Тип выбранного пункта
					selected_value,						// Значение выбранного пункта
					action_item,						// Действие пункта
					list_item;							// Список значений пункта

	conf_str		temp_conf_str;

	items_list_str	item_temp;

	int				key_pressed;

	/*LANG ZONE START*/
	string	settings_lng	= "settings",
			set_name		= conf("name_app", setfile_vec);
	/*LANG ZONE END*/

	getmaxyx(stdscr, maxY, maxX);

	timeout(-1);

	if ((temp = conf("all_items", setfile_vec)) == "0x1") {
		failwin.title 		= "Error reading settings file";
		failwin.line		= "Setfile is incorrect! Not found all_items parametr!";
		msg_win(failwin);
		return -1;
	} else {
		all_items	= atoi(temp.c_str());
	}

	cycle		= true;

	draw_border(settings_lng, set_name, maxX, maxY);

	for (i	= 1; i <= all_items; i++) { // Загрузка всех конфигурационных файлов и заполнение вектора, который будет выводиться на экран
		path_to_conf_item	= conf(str(i) + "_conf_file", setfile_vec); // Путь к файлу конфигураций

		if ((confs_vec.size() == 0) || (!search_in_struct(path_to_conf_item, confs_vec, temp_conf_str))) { // Проверка есть ли уже такой загруженный файл конфигураций
			load_to_vector(path_to_conf_item, temp_vec); // Загрузка файла конфигураций
			temp_conf_str.path_to_configuration_file	= path_to_conf_item;
			temp_conf_str.point_to_vector				= temp_vec;
			confs_vec.insert(confs_vec.end(), temp_conf_str);
		}

		if (!load_item(setfile_vec, i, name_item, comment_item, type_item, parametr_config_item, path_to_conf_item, list_item, action_item)) { // Получение значений пункта
			return -1;
		}

		item_temp.name_item		= name_item; // Заполнение временной переменной
		item_temp.comment_item	= comment_item; // Комментарий
		item_temp.type_item		= type_item; // Тип пункта
		item_temp.path_to_conf	= path_to_conf_item; // Путь к конфигурационному файлу
		item_temp.parametr		= parametr_config_item; // Параметр в конфигурационном файле
		item_temp.action		= action_item; // Действие

		if (!list_item.empty()) { // Загрузка списка значений пункта, если он есть
			load_list_values(list_item, item_temp.list_values);
		}

		search_in_struct(path_to_conf_item, confs_vec, temp_conf_str);
		temp_vec				= temp_conf_str.point_to_vector;
		item_temp.value_item	= conf(parametr_config_item, temp_vec);

		if ((item_temp.type_item != "action") && (item_temp.value_item == "0x1")) {
			failwin.title 		= "Error reading configuration file";
			failwin.line		= "Error read value " + parametr_config_item + " in " + path_to_conf_item;
			msg_win(failwin);
			return -1;
		}

		items_list.insert(items_list.end(), item_temp); // Заполнение списка-вектора для вывода на экран
	}

	first_write						= 0;
	position_write					= 0;
	selected						= 0;
	key_pressed						= KEY_UP;
	right_border					= (maxX - 2) - maxX / 4;
	cut_selected_name				= 0;
	cut_selected_comment			= 0;
	wait_selected_name				= 0;
	wait_selected_comment			= 0;
	want_to_moving_selected_name	= false;
	want_to_moving_selected_comment	= false;

	if (conf("scroll_long_lines_in_settings", main_config_base) == "1") {
		animation_move				= true;
	} else {
		animation_move				= false;
	}

	if ((all_items * 3 + 2) > maxY) {
		last_write					= (maxY - 2) / 3;
	} else {
		last_write					= all_items;
	}

	while (cycle) {
		timeout(200);
		position_write	= 2;
		if ((key_pressed == KEY_UP) || (key_pressed == KEY_DOWN) || (key_pressed == '\n')) { // Вывод невыделенных пунктов
			for (i	= first_write; i < last_write; i++) {
				item_temp = items_list[i];

				if (selected == i) { // Пропуск выделенного пункта
					selected_name			= item_temp.name_item;
					selected_comment		= item_temp.comment_item;
					selected_type			= item_temp.type_item;
					selected_value			= item_temp.value_item;
					cut_selected_name		= 0;
					wait_selected_name		= 0;
					cut_selected_comment	= 0;
					wait_selected_comment	= 0;

					if (((llength(selected_name) + 3) > right_border) && (animation_move)) {
						want_to_moving_selected_name	= true;
					} else {
						if (((llength(selected_name) + 3) > right_border)) {
							selected_name.erase(right_border - 6, llength(selected_name));
							selected_name	+= "...";
						}

						want_to_moving_selected_name	= false;
					}

					if (((llength(selected_comment) + 4) > right_border) && (animation_move)) {
						want_to_moving_selected_comment	= true;
					} else {
						if ((llength(selected_comment) + 4) > right_border) {
							selected_comment.erase(right_border - 7, llength(selected_comment));
							selected_comment	+= "...";
						}

						want_to_moving_selected_comment	= false;
					}

					position_write			+= 3;
					continue;
				}

				for (j	= 0; j < maxX - 2; j++, mvprintw(position_write, j, " "), mvprintw(position_write + 1, j, " ")); // Зачистка поля

				if (llength(item_temp.name_item) + 3 > right_border) {
					item_temp.name_item.erase(right_border - 6, llength(item_temp.name_item));
					item_temp.name_item	+= "...";
				}

				attron(COLOR_PAIR(main_system_color) | A_BOLD);
				mvprintw(position_write, 2, "%s", item_temp.name_item.c_str());

				if (!item_temp.comment_item.empty()) {
					if (llength(item_temp.comment_item) + 4 > right_border) {
						item_temp.comment_item.erase(right_border - 7, llength(item_temp.comment_item));
						item_temp.comment_item	+= "...";
					}
					mvprintw(position_write + 1, 3, "%s", item_temp.comment_item.c_str());
				}
				attroff(COLOR_PAIR(main_system_color) | A_BOLD);

				if (item_temp.type_item == "bool") {
					if (item_temp.value_item == "1") {
						attron(COLOR_PAIR(TEXT_GREEN_BLACK) | A_BOLD);
						mvprintw(position_write, maxX - ((maxX - right_border) / 2), "ON");
						attroff(COLOR_PAIR(TEXT_GREEN_BLACK) | A_BOLD);
					} else {
						attron(COLOR_PAIR(TEXT_RED_BLACK) | A_BOLD);
						mvprintw(position_write, maxX - ((maxX - right_border) / 2), "OFF");
						attroff(COLOR_PAIR(TEXT_RED_BLACK) | A_BOLD);
					}
				}  else if (item_temp.type_item != "action") {
					attron(COLOR_PAIR(main_system_color) | A_BOLD);
					if (llength(item_temp.value_item) > (maxX - right_border - 3)) {
						item_temp.value_item.erase((maxX - right_border - 6), llength(item_temp.value_item));
						item_temp.value_item	+= "...";
					}
					mvprintw(position_write, right_border + 1, "%s", item_temp.value_item.c_str());
					attroff(COLOR_PAIR(main_system_color) | A_BOLD);
				}

				if (item_temp.type_item == "action") {
					attron(COLOR_PAIR(main_system_color) | A_BOLD);
					mvprintw(position_write, maxX - 3, ">");
					attroff(COLOR_PAIR(main_system_color) | A_BOLD);
				}

				position_write	+= 3;
			}
		}

		/*DRAW SELECTED ELEMENT START*/
		if ((key_pressed == KEY_UP) || (key_pressed == KEY_DOWN) || (key_pressed == '\n')) {
			attron(COLOR_PAIR(main_system_color_selection) | A_BOLD);
			for (j	= 0; j < maxX - 2; j++, mvprintw(2 + (selected - first_write) * 3, j, " "), mvprintw(3 + (selected - first_write) * 3, j, " ")); // Заполнение цветом выделения
			attroff(COLOR_PAIR(main_system_color_selection) | A_BOLD);
		
			if (selected_type == "bool") {
				if (selected_value == "1") {
					attron(COLOR_PAIR(get_color_on_color(TEXT_GREEN_BLACK, main_system_color)) | A_BOLD);
					mvprintw(2 + (selected - first_write) * 3, maxX - ((maxX - right_border) / 2), "ON");
					attroff(COLOR_PAIR(get_color_on_color(TEXT_GREEN_BLACK, main_system_color)) | A_BOLD);
				} else {
					attron(COLOR_PAIR(get_color_on_color(TEXT_RED_BLACK, main_system_color)) | A_BOLD);
					mvprintw(2 + (selected - first_write) * 3, maxX - ((maxX - right_border) / 2), "OFF");
					attroff(COLOR_PAIR(get_color_on_color(TEXT_RED_BLACK, main_system_color)) | A_BOLD);
				}
			} else if (selected_type != "action") {
				attron(COLOR_PAIR(main_system_color_selection) | A_BOLD);
				if (llength(selected_value) > (maxX - right_border - 3)) {
					selected_value.erase((maxX - right_border - 6), llength(selected_value));
					selected_value	+= "...";
				}
				mvprintw(2 + (selected - first_write) * 3, right_border + 1, "%s", selected_value.c_str());
			}

			if (selected_type == "action") {
				attron(COLOR_PAIR(main_system_color_selection) | A_BOLD);
				mvprintw(2 + (selected - first_write) * 3, maxX - 3, ">");
			}
			attroff(COLOR_PAIR(main_system_color_selection) | A_BOLD);
		}

		attron(COLOR_PAIR(main_system_color_selection) | A_BOLD);

		if (want_to_moving_selected_name) {
			if (wait_selected_name == 0) { // Двигатель имени пункта
				temp	= selected_name;
				temp.erase(0, cut_selected_name); // Обрезка начала

				if (cut_selected_name == 0) // Если начато всё сначала остановиться и подождать
					wait_selected_name	= WAIT_START;

				cut_selected_name++; // Сколько символов нужно обрезать спереди

				if (llength(temp) + 3 > right_border) { // Обрезка конца
					temp.erase(right_border - 3, llength(temp));
				} else {
					wait_selected_name	= WAIT_END; // Если достигло конца, то подождать
					cut_selected_name	= 0;
				}

				mvprintw(2 + (selected - first_write) * 3, 2, "%s", temp.c_str()); // Вывести на экран
			} else {
				wait_selected_name--; // Счётчик ожидания
			}

		} else {
			mvprintw(2 + (selected - first_write) * 3, 2, "%s", selected_name.c_str());
		}

		if (want_to_moving_selected_comment) {
			if (wait_selected_comment == 0) { // Двигатель имени пункта
				temp	= selected_comment;
				temp.erase(0, cut_selected_comment); // Обрезка начала

				if (cut_selected_comment == 0) // Если начато всё сначала остановиться и подождать
					wait_selected_comment	= WAIT_START;

				cut_selected_comment++; // Сколько символов нужно обрезать спереди

				if (llength(temp) + 4 > right_border) { // Обрезка конца
					temp.erase(right_border - 4, llength(temp));
				} else {
					wait_selected_comment	= WAIT_END; // Если достигло конца, то подождать
					cut_selected_comment	= 0;
				}

				mvprintw(3 + (selected - first_write) * 3, 3, "%s", temp.c_str()); // Вывести на экран
			} else {
				wait_selected_comment--; // Счётчик ожидания
			}

		} else {
			mvprintw(3 + (selected - first_write) * 3, 3, "%s", selected_comment.c_str());
		}

		attroff(COLOR_PAIR(main_system_color_selection) | A_BOLD);
		/*DRAW SELECTED ELEMENT END*/

		key_pressed	= getch();

		switch (key_pressed) {
			case KEY_UP:	if (selected != 0) {

								if (selected == first_write) {
									first_write--; 
									last_write--; 
								}

								selected--;
							}
							break;

			case KEY_DOWN:	if (selected != all_items - 1) {

								if (selected == last_write - 1) {
									first_write++; 
									last_write++; 
								}

								selected++;
							}
							break;

			case '\n':		item_temp		= items_list[selected];
							if (item_temp.type_item == "bool") {
								DLGSTR	setwin	= {}; // Только так!!!

								setwin.title	= item_temp.name_item;

								if (item_temp.comment_item.empty()) {
									setwin.line		= item_temp.name_item;
								} else {
									setwin.line		= item_temp.comment_item;
								}

								setwin.style	= CYAN_WIN;
								setwin.keys		= 3;
								setwin.f_button	= "ON";
								setwin.s_button	= "OFF";
								setwin.t_button	= "Cancel";

								if (item_temp.value_item == "1") {
									setwin.selected	= 2;
								} else {
									setwin.selected	= 1;
								}

								int	select	= msg_win(setwin);

								if ((select == 1) && (item_temp.value_item != "1")) {
										item_temp.value_item	= "1";
										configurator(item_temp.path_to_conf, item_temp.parametr, item_temp.value_item, true);
										items_list[selected]	= item_temp;
								}

								if ((select == 2) && (item_temp.value_item != "0")) {
										item_temp.value_item	= "0";
										configurator(item_temp.path_to_conf, item_temp.parametr, item_temp.value_item, true);
										items_list[selected]	= item_temp;
								}

								draw_border(settings_lng, set_name, maxX, maxY);
							}

							if (item_temp.type_item == "list") { // Оставил вызов и работу со старой менюшкой для наглядности
								/*DLGSTR			setwin		= {}; // Только так!!!
								vector <string>	menu_vec;

								item_temp					= items_list[selected];

								setwin.style				= CYAN_WIN;
								setwin.border_menu			= true;
								setwin.xpos					= maxX - ((maxX - right_border) / 2);
								setwin.ypos					= 2 + (selected - first_write) * 3;
								if (item_temp.list_values.size() + 2 > maxY) {
									setwin.ymax					= maxY - (4 + (selected - first_write) * 3);
								} else {
									setwin.ymax					= 0;
								}
								key_pressed					= 0;
								menu_vec					= item_temp.list_values;

								timeout(-1);

								while ((key_pressed != '\n') && (key_pressed != 27)) {
									menu_win(setwin, menu_vec);
									
									key_pressed		= getch();

									switch (key_pressed) {
										case KEY_UP:	if (setwin.selected != 0)
															setwin.selected--;
														break;

										case KEY_DOWN:	if (setwin.selected != item_temp.list_values.size())
															setwin.selected++;
														break;

										case '\n':		if (item_temp.value_item != item_temp.list_values[setwin.selected - 1]) {
															item_temp.value_item	= item_temp.list_values[setwin.selected - 1];
															configurator(item_temp.path_to_conf, item_temp.parametr, item_temp.value_item, true);
															items_list[selected]	= item_temp;
														}
														break;
									}
								}
								
								draw_border(settings_lng, set_name, maxX, maxY);
								key_pressed			= KEY_UP;*/
								Init_MENSTR(setwin);

								setwin.posX			= maxX - ((maxX - right_border) / 2);
								setwin.posY			= 2 + (selected - first_write) * 3;

								unsigned int	selected_menu	= menu_win(&setwin, "", item_temp.list_values, CYAN_WIN);

								if ((selected_menu != 0) && (item_temp.value_item != item_temp.list_values[selected_menu - 1])) {
									item_temp.value_item	= item_temp.list_values[selected_menu - 1];
									configurator(item_temp.path_to_conf, item_temp.parametr, item_temp.value_item, true);
									items_list[selected]	= item_temp;
								}

								draw_border(settings_lng, set_name, maxX, maxY);
								key_pressed			= KEY_UP;
							}

							if (item_temp.type_item == "text") {
								DLGSTR	setwin	= {}; // Только так!!!

								setwin.title	= item_temp.name_item;

								if (item_temp.comment_item.empty()) {
									setwin.line		= item_temp.name_item;
								} else {
									setwin.line		= item_temp.comment_item;
								}

								setwin.style	= CYAN_WIN;
								setwin.keys		= 2;
								setwin.f_button	= "OK";
								setwin.s_button	= "Cancel";

								string	us_input;

								int		selected_dlg;

								bool	cant_be_empty	= false;

								do {
									if (cant_be_empty) {
										DLGSTR	failwin	= {}; // Только так!!!
										failwin.style	= RED_WIN;
										failwin.title	= "Error!";
										failwin.line	= "This field can not be empty!";
										msg_win(failwin);
									}

									selected_dlg	= dlg_win(setwin, us_input);
									cant_be_empty	= true;
								} while ((selected_dlg == 1) && (us_input.empty()));

								if ((selected_dlg == 1) && (item_temp.value_item != us_input)) {
										item_temp.value_item	= us_input;
										configurator(item_temp.path_to_conf, item_temp.parametr, item_temp.value_item, true);
										items_list[selected]	= item_temp;
								}

								draw_border(settings_lng, set_name, maxX, maxY);
							}

							if (item_temp.type_item == "action") {
								action_parcer(item_temp.action);
								draw_border(settings_lng, set_name, maxX, maxY);
							}
							break;

			case KEY_BACKSPACE:	cycle = false;
								break;

			case H_KEY_BACKSPACE:	cycle = false;
								break;

			case 27:		cycle = false;
							break;
		}
	}

	return 0;
}