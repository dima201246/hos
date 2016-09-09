#include "internal_windlg.h"
#include "../../include/windows_api.h"
#include "../../include/system_defines.h"
#include "../../include/isca_alpha.h"

using namespace std;

void clear_space(unsigned int	start_x, unsigned int	start_y, unsigned int	end_x, unsigned int	end_y) {	// Заливка области пустотой
	unsigned i = 0;
	for (unsigned int	x = 0; x < end_x; x++, i++) {
		for (unsigned int	y = 0; y < end_y; y++) {
			mvprintw(y + start_y, x + start_x, " ");
		}
	}
}

int button_obj(WINOBJ *button_conf, string text, color_t color_button) {
	if (button_conf->redraw) {
		coloron(color_button);
		if ((button_conf->posXmax != 0) || (button_conf->posYmax != 0)) {
			if (button_conf->posXmax == 0)
				button_conf->posXmax = 1;

			if (button_conf->posYmax == 0)
				button_conf->posYmax = 1;

			clear_space(button_conf->posX, button_conf->posY, button_conf->posXmax, button_conf->posYmax);			
			mvprintw(button_conf->posY, button_conf->posX, "[%s]", text.c_str());
		} else {
			mvprintw(button_conf->posY, button_conf->posX, "[%s]", text.c_str());
		}
		coloroff(color_button);
	} else {
		coloron(get_inv_color(color_button));
		if ((button_conf->posXmax != 0) || (button_conf->posYmax != 0)) {
			if (button_conf->posXmax == 0)
				button_conf->posXmax = 1;

			if (button_conf->posYmax == 0)
				button_conf->posYmax = 1;

			clear_space(button_conf->posX, button_conf->posY, button_conf->posXmax, button_conf->posYmax);			
			mvprintw(button_conf->posY, button_conf->posX, ">%s<", text.c_str());
		} else {
			mvprintw(button_conf->posY, button_conf->posX, ">%s<", text.c_str());
		}
		coloroff(get_inv_color(color_button));
		return getch();
	}

	return 0;
}

void add_to_win(vector<list_of_objects> &obj_list, win_object object_type, std::string text_on_object, color_t color_obj, WINOBJ* point_to_conf) {	// Добавление объекта в окно
	list_of_objects	temp_value	= {};	// Переменная для получение объекта из вектора

	switch (object_type) {	// Определение типа передаваемого объекта
		case WIN_BUTTON:	temp_value.point_to_function	= &button_obj;
							temp_value.type_obj				= WIN_BUTTON;
							break;
	}

	if (point_to_conf == NULL) {	// Проверка, была ли передана структура вместе с объектом
		WINOBJ *temp_objstr			= new WINOBJ;	// Если нет, то выделение под неё памяти
		temp_objstr->posX			= 0;
		temp_objstr->posXmax		= 0;
		temp_objstr->posY			= 0;
		temp_objstr->posYmax		= 0;
		temp_objstr->manual_locator	= false;
		temp_objstr->user_init		= false;
		temp_objstr->redraw			= true;	// Чотбы сразу, при первом вызове, объект перерисовался
		temp_value.point_to_struct	= temp_objstr;
		temp_value.memory_leak		= true;
	} else {
		point_to_conf->redraw		= true;
		temp_value.point_to_struct	= point_to_conf;
	}

	temp_value.text					= text_on_object;
	temp_value.color_object			= color_obj;
	obj_list.push_back(temp_value);
}

void get_obj_size(list_of_objects	item, unsigned int &x, unsigned int &y) {	// Получение предполагаемого размера объекта
	switch (item.type_obj) {
		case WIN_BUTTON:	if (item.point_to_struct->posXmax == 0) {
								x	= item.text.length() + 2;
							} else {
								x	= item.point_to_struct->posXmax;
							}
							if (item.point_to_struct->posYmax == 0) {
								y	= 1;
							} else {
								y	= item.point_to_struct->posYmax;
							}
							break;
	}
}

returned_str win(WINOBJ* win_conf, vector<list_of_objects> obj_list, string title, color_t color) {

	returned_str		returned_value;	// Возвращаемая структура

	list_of_objects		temp_item,
						selected_item;

	WINOBJ				*now_obj_conf,
						*ahead_obj_conf;

	int					key_pressed;

	unsigned int		size_ahead_obj_x,	// Размеры предыдущего объекта, если таковой имелся
						size_ahead_obj_y,
						size_obj_x,			// Для получения размеров текущего объекта
						size_obj_y,
						win_posX,
						win_posY,
						win_posXmax,
						win_posYmax,
						selected_obj,
						next_line,			// Позиция новой строки
						first_display_obj,	// С какого объекта выводить на экран
						last_display_obj,	// ... и до какого
						max_posYmax;

	bool 				cycle,
						found_button,		// Для отслеживания, была ли в окне хоть одна кнопка
						ahead_button,
						refresh_obj;

	size_ahead_obj_x	= 0;
	size_ahead_obj_y	= 0;
	size_obj_x			= 0;
	size_obj_y			= 0;
	selected_obj		= 0;
	first_display_obj	= 0;
	max_posYmax			= 0;
	last_display_obj	= 0;
	next_line			= 2;
	cycle				= true;
	refresh_obj			= true;
	found_button		= false;
	ahead_button		= false;

	getmaxyx(stdscr, win_posYmax, win_posXmax);

	if (win_conf == NULL) {
		win_posX		= 0;
		win_posY		= 0;
	} else {
		win_posX		= win_conf->posX;
		win_posY		= win_conf->posY;

		if (win_conf->posXmax != 0)
			win_posXmax	= win_conf->posXmax;

		if (win_conf->posYmax != 0)
			win_posYmax	= win_conf->posYmax;
	}

	draw_box(1, title, 0, win_posX, win_posY, win_posXmax - win_posX, win_posYmax - win_posY - 1, color, get_inv_color(color));

	for (unsigned int	i	= 0; i < obj_list.size(); i++) {
		if (obj_list[i].type_obj == WIN_BUTTON)
			found_button	= true;
	}

	if (!found_button) {
		add_to_win(obj_list, WIN_BUTTON, "OK", color, NULL);
		return win(win_conf, obj_list, title, color);
	}

	/*Автоматическое расположение объектов в окне НАЧАЛО*/
	if ((win_conf == NULL) || (!win_conf->manual_locator)) {
		for (unsigned int	i	= 0; i < obj_list.size(); i++) {

			temp_item	= obj_list[i];

			now_obj_conf	= temp_item.point_to_struct;

			now_obj_conf->posX	+= 2 + win_posX;
			now_obj_conf->posY	+= next_line + win_posY;

			if (i != 0) {
				ahead_obj_conf	= obj_list[i - 1].point_to_struct;	// Ссылка на предыдущий объект, если он есть
			} else {
				ahead_obj_conf	= NULL;
			}

			get_obj_size(temp_item, size_obj_x, size_obj_y);	// Получение размеров объекта

			if (!now_obj_conf->user_init) {	// Если объект не был инициализирован пользователем
				if ((ahead_button) && (temp_item.type_obj == WIN_BUTTON)) {	 // Если до этого была кнопка

					if (((ahead_obj_conf->posX + size_ahead_obj_x + size_obj_x + 1) >= win_posXmax) && (temp_item.type_obj == WIN_BUTTON)) {	// Если кнопка после кнопки вылазит за пределы окна
						if ((last_display_obj == 0) && ((now_obj_conf->posY + 2 + size_obj_y) >= win_posYmax)) {	// Проверка, чтобы влезало по Y
							last_display_obj	= i;
						}

						now_obj_conf->posY	+= max_posYmax + 1;
						next_line			+= max_posYmax + 1;
						max_posYmax			= 0;
					} else {
						now_obj_conf->posX	= ahead_obj_conf->posX + size_ahead_obj_x + 1;	// Сдвиг кнопки вправо от предыдущей кнопки
					}
				} else if (temp_item.type_obj != WIN_BUTTON) {	// Другие объекты будут каждый с новой строки, вытянуты во всю ширину окна
					if (i != 0)
						now_obj_conf->posY	+= max_posYmax + 1;

					//now_obj_conf->posXmax	= ...;
				}
			} else {
				// if ()
			}

			size_ahead_obj_x	= size_obj_x;	// Получение размеров объекта для позиционирования следующего
			size_ahead_obj_y	= size_obj_y;
`
			if (max_posYmax < size_ahead_obj_y)
				max_posYmax	= size_ahead_obj_y;

			if (temp_item.type_obj == WIN_BUTTON) {
				ahead_button	= true;
			} else {
				ahead_button	= false;
			}

			#ifdef DEBUG
			add_to_file(MAIN_LOGFILE, "Object number: " + str(i));
			add_to_filef(MAIN_LOGFILE, "Function point: %p\n", temp_item.point_to_function);
			add_to_filef(MAIN_LOGFILE, "Struct point: %p\n", temp_item.point_to_struct);
			add_to_file(MAIN_LOGFILE, "Text: " + temp_item.text);
			#endif

			temp_item.point_to_struct	= now_obj_conf;
			obj_list[i]	= temp_item;
		}
	}

	if (last_display_obj == 0) {
		last_display_obj = obj_list.size();
	}
	/*Автоматическое расположение объектов в окне КОНЕЦ*/

	while (cycle) {
		if (refresh_obj) {
			for (unsigned int	i	= first_display_obj; i < last_display_obj; i++) {
				temp_item	= obj_list[i];

				if (selected_obj == i) {
					selected_item	= temp_item;
					key_pressed		= temp_item.point_to_function(temp_item.point_to_struct, temp_item.text, temp_item.color_object);	// Вызов нужного объекта
				} else {
					temp_item.point_to_function(temp_item.point_to_struct, temp_item.text, temp_item.color_object);	// Вызов нужного объекта
				}

				if (selected_obj == i) {
					temp_item.point_to_struct->redraw	= false;
					obj_list[i]	= temp_item;
				}

			}

			refresh_obj	= false;
		} else {
			key_pressed	= selected_item.point_to_function(selected_item.point_to_struct, selected_item.text, selected_item.color_object);	// Вызов нужного объекта
		}

		switch (key_pressed) {
			case H_KEY_ESC:	cycle		= false;
							break;

			case H_KEY_TAB:	obj_list[selected_obj].point_to_struct->redraw	= true;	// Перерисовать объект невыделенным
							obj_list[selected_obj].point_to_function(obj_list[selected_obj].point_to_struct, obj_list[selected_obj].text, obj_list[selected_obj].color_object);	// Обновление элемента
							refresh_obj	= true;

							if (selected_obj != (obj_list.size() - 1)) {
								selected_obj++;
							} else {
								selected_obj	= 0;
							}

							/*if (selected_obj > last_display_obj) {

							}*/

							break;
		}
	}

	
	for (unsigned int	i	= 0; i < obj_list.size(); i++) {	// От утечки памяти
		temp_item	= obj_list[i];

		if (temp_item.memory_leak)
			delete temp_item.point_to_struct;
	}

	return returned_value;
}