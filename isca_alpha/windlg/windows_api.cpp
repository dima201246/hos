#include "internal_windlg.h"
#include "../../include/system_defines.h"
#include "../../include/isca_alpha.h"

using namespace std;

struct nearest_obj
{
	list_of_objects	*obj;
	unsigned int	num,
					size;
};

void clear_space(unsigned int	start_x, unsigned int	start_y, unsigned int	end_x, unsigned int	end_y) {	// Заливка области пустотой
	unsigned i = 0;
	for (unsigned int	x = 0; x < end_x; x++, i++) {
		for (unsigned int	y = 0; y < end_y; y++) {
			mvprintw(y + start_y, x + start_x, " ");
		}
	}
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
		*temp_objstr				= {};
		temp_objstr->redraw			= true;	// Чотбы сразу, при первом вызове, объект перерисовался
		temp_value.point_to_struct	= temp_objstr;
		temp_value.memory_leak		= true;
	} else {
		point_to_conf->redraw		= true;
		temp_value.point_to_struct	= point_to_conf;
		temp_value.point_to_struct->user_init	= true;
	}

	temp_value.text					= text_on_object;
	temp_value.color_object			= color_obj;
	obj_list.push_back(temp_value);
}

void get_obj_size(list_of_objects	item, unsigned int &x, unsigned int &y) {	// Получение предполагаемого размера объекта
	// add_to_filef(MAIN_LOGFILE, "Type : %d\n", item.type_obj);
	switch (item.type_obj) {
		case WIN_BUTTON:	if (item.point_to_struct->posXmax == 0) {
								x	= item.text.length() + 2;
								// add_to_filef(MAIN_LOGFILE, "posXmax = 0 : %ld\n", x);
							} else {
								x	= item.point_to_struct->posXmax;
								// add_to_filef(MAIN_LOGFILE, "posXmax != 0 : %ld\n", x);
							}
							if (item.point_to_struct->posYmax == 0) {
								y	= 1;
								// add_to_filef(MAIN_LOGFILE, "posYmax = 0 : %ld\n", y);
							} else {
								y	= item.point_to_struct->posYmax;
								// add_to_filef(MAIN_LOGFILE, "posYmax != 0 : %ld\n", y);
							}
							break;
	}
}
/*
void display_prev_obj(vector<list_of_objects> &obj_list, unsigned int &first_display_obj, unsigned int &last_display_obj, unsigned int win_posXmax, unsigned int win_posY) {	// Спуск в окне (поднятие всех объектов выше)
	bool				button_ahead;

	unsigned int		size_obj_x,
						size_obj_y,
						size_ahead_obj_x,
						// size_ahead_obj_y,
						line_y;

	button_ahead		= false;
	line_y				= 0;
	size_obj_x			= 0;
	size_obj_x			= 0;
	size_ahead_obj_x	= 0;
	// size_ahead_obj_y	= 0;

	add_to_filef(MAIN_LOGFILE, "last_display_obj: %d\n", last_display_obj);
	// Стирание самой нижней строки Начало
	line_y	= obj_list[last_display_obj].point_to_struct->posY;
	add_to_filef(MAIN_LOGFILE, "line_y: %d\n", line_y);

	for (unsigned int	i	= last_display_obj; i > 0; i--)
	{
		if (obj_list[i].point_to_struct->posY == line_y)
			last_display_obj--;
		else
			break;
	}
	// Стирание самой нижней строки Конец
			add_to_filef(MAIN_LOGFILE, "last_display_obj: %d\n", last_display_obj);

	// Сдвиг всех объектов вниз Начало
	for (unsigned int	i	= first_display_obj; i <= last_display_obj; i++)
	{
		// if ((obj_list[i].point_to_struct->posY - 2) > win_posY)	// Чтобы объект не налазил на заголовок окна
		{
			obj_list[i].point_to_struct->posY	+= 2;
			obj_list[i].point_to_struct->redraw = true;
		}
	}
			add_to_filef(MAIN_LOGFILE, "End shift down\n");
	// Сдвиг всех объектов вниз Конец

	for (unsigned int i	= last_display_obj + 1; i < obj_list.size(); i++) {

		if (!obj_list[i].point_to_struct->user_init) {	// Если объект не был инициализирован пользователем
			get_obj_size(obj_list[i], size_obj_x, size_obj_y);	// Получение размеров объекта

			if ((obj_list[i].type_obj == WIN_BUTTON) && ((obj_list[i - 1].point_to_struct->posX + size_ahead_obj_x + size_obj_x + 1) <= win_posXmax)) {
				last_display_obj++;
				button_ahead	= true;
			} else {
				if (button_ahead)
				{
					break;
				}

				last_display_obj++;
				break;
			}

			size_ahead_obj_x	= size_obj_x;
			// size_ahead_obj_y	= size_obj_y;
		}
	}
}
*/
void display_next_obj_line(vector<list_of_objects> obj_list, unsigned int &first_display_obj, unsigned int &last_display_obj, unsigned int win_posY, unsigned int win_posYmax) {	// Спуск в окне (поднятие всех объектов выше)
	bool			collision_fail	= false;

	unsigned int	line_y	= 0;

	// Стирание самой высокой строки с экрана Начало
	for (unsigned int	i	= 0; i < obj_list.size(); i++)	// Поиск самого высокого активного объекта
	{
		if ((obj_list[i].point_to_struct->active_obj) && ((obj_list[i].point_to_struct->posY < line_y) || (i == 0)))
			line_y	= obj_list[i].point_to_struct->posY;
	}

	for (unsigned int	i	= 0; i < obj_list.size(); i++)
	{
		if (obj_list[i].point_to_struct->posY == line_y)
		{
			obj_list[i].point_to_struct->active_obj	= false;
			obj_list[i].point_to_struct->redraw		= false;
		}
	}
	// Стирание самой высокой строки с экрана Конец

	for (unsigned int	i	= 0; i < obj_list.size(); i++)	// Сдвиг всех активных объектов вверх Начало
	{
		if (obj_list[i].point_to_struct->active_obj)
		{
			obj_list[i].point_to_struct->posY	-= 2;
			obj_list[i].point_to_struct->redraw	= true;

			if (obj_list[i].point_to_struct->posY <= win_posY)	// Отключние объекта, если он залез на границу окна
			{
				obj_list[i].point_to_struct->posY	= win_posY + 1;
				obj_list[i].point_to_struct->redraw	= false;
			}
		}
	}

	for (unsigned int i	= 0; i < obj_list.size(); i++)	// Вывод на экран нижней линии
	{
		if ((!obj_list[i].point_to_struct->active_obj) && (obj_list[i].point_to_struct->posY < win_posYmax) && (obj_list[i].point_to_struct->posY >= win_posYmax - 2))
		{
			for (unsigned int j = 0; j < obj_list.size(); ++j)
			{
				if ((obj_list[j].point_to_struct->active_obj) && (obj_list[j].point_to_struct->posY == obj_list[i].point_to_struct->posY) && (obj_list[j].point_to_struct->posX == obj_list[i].point_to_struct->posX))
				{
					collision_fail	= true;
					break;
				}
			}

			if (collision_fail)
			{
				collision_fail	= false;
				continue;
			}

			obj_list[i].point_to_struct->active_obj	= true;
			obj_list[i].point_to_struct->redraw		= true;
		}
	}
}

bool key_up(vector<list_of_objects> obj_list, unsigned int &selected_obj, unsigned int win_posY, unsigned int win_posYmax, unsigned int &top_line)
{
	std::vector<nearest_obj> obj_bank;

	unsigned int	x_size_selected,
					y_size_selected,
					x_size_temp,
					y_size_temp,
					nearest_obj_num		= 0,
					nearest_obj_size	= 0,
					nearest_obj_posY	= 0;

	// Поиск кнопки выше Начало
	get_obj_size(obj_list[selected_obj], x_size_selected, y_size_selected);	// Узнаём размеры выделенного объекта

	for (unsigned int i = 0; i < obj_list.size(); ++i)				// Проверяем все объекты
	{
		if ((obj_list[i].point_to_struct->active_obj) && (obj_list[i].point_to_struct->posY < obj_list[selected_obj].point_to_struct->posY))	// Небольшая оптимизация, чтобы проверялись только объекты выше выделенного
		{
			get_obj_size(obj_list[i], x_size_temp, y_size_temp);	// Получение размера временного объекта

			for (unsigned int j = obj_list[selected_obj].point_to_struct->posX; j <= (obj_list[selected_obj].point_to_struct->posX + x_size_selected); ++j)	// Цикл проверяющий каждый "пиксель" уже выделенного объекта
			{
				if (((j >= obj_list[i].point_to_struct->posX) && (j < (obj_list[i].point_to_struct->posX + x_size_temp))) && (obj_list[selected_obj].point_to_struct->posY > obj_list[i].point_to_struct->posY))
				{
					nearest_obj	temp;

					temp	= {
						.obj	= &obj_list[i],
						.num	= i,
					};

					if (obj_list[selected_obj].point_to_struct->posX <= obj_list[i].point_to_struct->posX)
					{
						if ((obj_list[selected_obj].point_to_struct->posX + x_size_selected) <= (obj_list[i].point_to_struct->posX + x_size_temp))
						{
							temp.size	= (((obj_list[i].point_to_struct->posX - obj_list[selected_obj].point_to_struct->posX) > x_size_temp) ? ((obj_list[i].point_to_struct->posX - obj_list[selected_obj].point_to_struct->posX) - x_size_temp) : (x_size_temp - (obj_list[i].point_to_struct->posX - obj_list[selected_obj].point_to_struct->posX)));
						}
						else
						{
							temp.size	= x_size_temp;
						}
					}
					else
					{
						temp.size	= (((obj_list[selected_obj].point_to_struct->posX - obj_list[i].point_to_struct->posX) > x_size_temp) ? ((obj_list[selected_obj].point_to_struct->posX - obj_list[i].point_to_struct->posX) - x_size_temp) : (x_size_temp - (obj_list[selected_obj].point_to_struct->posX - obj_list[i].point_to_struct->posX)));
					}

					obj_bank.push_back(temp);
					break;
				}
			}
		}
	}
	// Поиск кнопки выше Конец

	for (unsigned int i = 0; i < obj_bank.size(); ++i)	// Поиск самой близкой координаты Y
	{
		if (nearest_obj_posY < obj_bank[i].obj->point_to_struct->posY)
		{
			nearest_obj_posY	= obj_bank[i].obj->point_to_struct->posY;
		}
	}

	for (unsigned int i = 0; i < obj_bank.size(); ++i)	// Поиск объекта с большей поверхностью соприкосновения
	{
		if ((nearest_obj_size <= obj_bank[i].size) && (nearest_obj_posY == obj_bank[i].obj->point_to_struct->posY))
		{
			nearest_obj_size	= obj_bank[i].size;
			nearest_obj_num		= i;
		}
	}

	if (nearest_obj_size != 0)
	{
		obj_list[selected_obj].point_to_struct->redraw			= true;	// Перерисовка текущего выделенного объекта невыделенным
		selected_obj											= obj_bank[nearest_obj_num].num;
		obj_bank[nearest_obj_num].obj->point_to_struct->redraw	= true;
		return true;
	}
	else
	{

	}

	// display_prev_obj(obj_list, first_display_obj, last_display_obj, win_posXmax, win_posY);

	return false;
}

nearest_obj test_func(list_of_objects *first_obj, list_of_objects *second_obj)
{
	unsigned int	f_size_x,
					f_size_y,
					s_size_x,
					s_size_y;

	nearest_obj		temp;

	get_obj_size(*first_obj, f_size_x, f_size_y);
	get_obj_size(*second_obj, s_size_x, s_size_y);

	
	for (unsigned int i = first_obj->point_to_struct->posX; i <= (first_obj->point_to_struct->posX + f_size_x); ++i)	// Цикл проверяющий каждый "пиксель" уже выделенного объекта
	{
		if (((i >= second_obj->point_to_struct->posX) && (i < (second_obj->point_to_struct->posX + s_size_x))) && (first_obj->point_to_struct->posY > second_obj->point_to_struct->posY))
		{
			temp = {
				.obj = second_obj,	// Сохранение ссылки на объект
				.num = i,	// Сохранение номера объекта в векторе
			};
			if (first_obj->point_to_struct->posX <= second_obj->point_to_struct->posX)
			{
				if ((first_obj->point_to_struct->posX + f_size_x) <= (second_obj->point_to_struct->posX + s_size_x))
				{
					temp.size	= (((second_obj->point_to_struct->posX - first_obj->point_to_struct->posX) > s_size_x) ? ((second_obj->point_to_struct->posX - first_obj->point_to_struct->posX) - s_size_x) : (s_size_x - (second_obj->point_to_struct->posX - first_obj->point_to_struct->posX)));
				}

				else
				{
					temp.size	= s_size_x;
				}
			}
			else
			{
				temp.size	= (((first_obj->point_to_struct->posX - second_obj->point_to_struct->posX) > s_size_x) ? ((first_obj->point_to_struct->posX - second_obj->point_to_struct->posX) - s_size_x) : (s_size_x - (first_obj->point_to_struct->posX - second_obj->point_to_struct->posX)));
			
			}

			// obj_bank.push_back(temp);
			break;
		}
	}

	return temp;
}

bool key_down(vector<list_of_objects> obj_list, unsigned int &selected_obj, unsigned int &top_line)
{
	std::vector<nearest_obj> obj_bank;

	unsigned int	x_size_selected,
					y_size_selected,
					x_size_temp,
					y_size_temp,
					nearest_obj_num		= 0,
					nearest_obj_size	= 0,
					nearest_obj_posY	= 0;

	// Поиск кнопки выше Начало
	get_obj_size(obj_list[selected_obj], x_size_selected, y_size_selected);	// Узнаём размеры выделенного объекта

	for (unsigned int i = 0; i < obj_list.size(); ++i)				// Проверяем все объекты
	{
		if ((obj_list[i].point_to_struct->active_obj) && (obj_list[i].point_to_struct->posY > obj_list[selected_obj].point_to_struct->posY))	// Небольшая оптимизация, чтобы проверялись только объекты ниже выделенного
		{
			temp = test_func();

			if (temp.size != 0)
			{
				obj_bank.push_back(temp);
			}
		}
	}
	// Поиск кнопки выше Конец

	for (unsigned int i = 0; i < obj_bank.size(); ++i)	// Поиск самой близкой координаты Y
	{
		if (nearest_obj_posY < obj_bank[i].obj->point_to_struct->posY)
		{
			nearest_obj_posY	= obj_bank[i].obj->point_to_struct->posY;
		}
	}

	for (unsigned int i = 0; i < obj_bank.size(); ++i)	// Поиск объекта с большей поверхностью соприкосновения
	{
		if ((nearest_obj_size <= obj_bank[i].size) && (nearest_obj_posY == obj_bank[i].obj->point_to_struct->posY))
		{
			nearest_obj_size	= obj_bank[i].size;
			nearest_obj_num		= i;
		}
	}

	if (nearest_obj_size != 0)
	{
		obj_list[selected_obj].point_to_struct->redraw			= true;	// Перерисовка текущего выделенного объекта невыделенным
		selected_obj											= obj_bank[nearest_obj_num].num;
		obj_bank[nearest_obj_num].obj->point_to_struct->redraw	= true;
		return true;
	}
	else
	{

	}

	// display_prev_obj(obj_list, first_display_obj, last_display_obj, win_posXmax, win_posY);

	return false;
}

list_of_objects	*collision(std::vector<list_of_objects> obj_list, unsigned int num, unsigned int x, unsigned int y)
{
	unsigned int	temp_size_x = 0,
					temp_size_y = 0,
					size_x = 0,
					size_y = 0,
					end_x = x + size_x;

	get_obj_size(obj_list[num], size_x, size_y);

	for (unsigned int i = 0; i < obj_list.size(); ++i)
	{
		if (num == i)
		{
			continue;
		}

		get_obj_size(obj_list[i], temp_size_x, temp_size_y);

		if ((obj_list[i].point_to_struct->posY <= y) && (y <= (obj_list[i].point_to_struct->posY + temp_size_y)))	// Исправить в будущем, так как данная конструкция подходит только для объектов в одну линию
		{
			for (unsigned int tx = x; tx <= end_x; ++tx)
			{
				if ((obj_list[i].point_to_struct->posX >= tx) && (tx <= (obj_list[i].point_to_struct->posX + temp_size_x)))
					return &obj_list[i];
			}
		}
	}

	return NULL;
}

void structuring_obj(WINOBJ* win_conf, std::vector<list_of_objects> &obj_list, unsigned int startX, unsigned int startY, unsigned int endX, unsigned int endY)
{
	win_object		ahead_type_obj	= WIN_EMPTY;

	unsigned int	/*ahead_size_x	= 0,
					ahead_size_y	= 0,*/
					ahead_pos_x		= 0,
					ahead_pos_y		= 0,
					size_obj_x		= 0,
					size_obj_y		= 0;

	const unsigned int	indent_x		= 2,	// Отступ от края окна по горизонтали
						// indent_y		= 2,	// Отступ от края окна по вертикали
						free_space_x	= 1,	// Отступ между объектами по горизонтали
						free_space_y	= 2;	// Отступ между объектами по вертикали

	list_of_objects	*temp_item		= NULL,/*,
					*ahead_item		= NULL,*/
					*collision_obj	= NULL;

	if ((win_conf == NULL) || (!win_conf->manual_locator))
	{
		for (unsigned int i = 0; i < obj_list.size(); ++i)
		{
			temp_item	= &obj_list[i];

			get_obj_size(*temp_item, size_obj_x, size_obj_y);

			if (!temp_item->point_to_struct->user_init)	// Если объект не был инициализирован пользователем
			{
				if ((ahead_type_obj != temp_item->type_obj) || ((ahead_pos_x + size_obj_x + free_space_x) >= endX))	// Спуск на следующую строку, если сменился тип объекта или нет места
				{
					ahead_pos_x	= startX + indent_x;
					ahead_pos_y	+= free_space_y;
				}

				collision_obj	= collision(obj_list, i, ahead_pos_x, ahead_pos_y);	// Возвращает указатель на объект с котиорым столкнулся

				if (collision_obj != NULL)	// Если выявленно соприкосновение с каким-либо объектом
				{
					if (collision_obj->type_obj == temp_item->type_obj)	// Совпадает ли тип объекта с которым соприкоснулся текущий объект или нет
					{
						unsigned int	temp_size_x,
										temp_size_y;

						get_obj_size(*collision_obj, temp_size_x, temp_size_y);

						if ((collision_obj->point_to_struct->posX + temp_size_x + free_space_x + size_obj_x) < endX)	// Разместить сразу за объектом, если хватает места
						{
							ahead_pos_x	= collision_obj->point_to_struct->posX + temp_size_x + free_space_x;
						}
						else
						{
							ahead_pos_x	= startX + indent_x;
							ahead_pos_y	= collision_obj->point_to_struct->posY + 2;
						}
					}
					else
					{
						ahead_pos_x	= startX + indent_x;
						ahead_pos_y	= collision_obj->point_to_struct->posY + 2;
					}
				}

				temp_item->point_to_struct->posX	= ahead_pos_x;
				temp_item->point_to_struct->posY	= ahead_pos_y;

				ahead_pos_x		+= size_obj_x + free_space_x;
				ahead_type_obj	= temp_item->type_obj;
			}
			else
			{
				// add_to_filef(MAIN_LOGFILE, "User init!: %ld Coord: %ld-%ld\n", i, temp_item->point_to_struct->posX, temp_item->point_to_struct->posY);
			}

			/*ahead_size_x	= size_obj_x;
			ahead_size_y	= size_obj_y;
			ahead_item		= temp_item;*/

			temp_item->point_to_struct->active_obj	= true; // DEBUG
		}
	}
}

returned_str win(WINOBJ* win_conf, vector<list_of_objects> obj_list, string title, color_t color) {

	returned_str		returned_value;	// Возвращаемая структура

	list_of_objects		temp_item,
						selected_item;

	int					key_pressed;

	unsigned int		win_posX,
						win_posY,
						win_posXmax,
						win_posYmax,
						selected_obj,
						top_line,	// Верхняя граница выводимых объектов
						bot_line;	// Нижняя граница выводимых объектов

	bool 				cycle,
						found_button,	// Для отслеживания, была ли в окне хоть одна кнопка
						refresh_obj;

	selected_obj		= 0;
	cycle				= true;
	refresh_obj			= true;
	found_button		= false;

	getmaxyx(stdscr, win_posYmax, win_posXmax);

	if (win_conf == NULL)
	{
		win_posX		= 0;
		win_posY		= 0;
	}
	else
	{
		win_posX		= win_conf->posX;
		win_posY		= win_conf->posY;

		if (win_conf->posXmax != 0)
			win_posXmax	= win_conf->posXmax;

		if (win_conf->posYmax != 0)
			win_posYmax	= win_conf->posYmax;
	}

	draw_box(1, title, 0, win_posX, win_posY, win_posXmax - win_posX, win_posYmax - win_posY - 1, color, get_inv_color(color));

	for (unsigned int	i	= 0; i < obj_list.size(); i++)
	{
		if (obj_list[i].type_obj == WIN_BUTTON)
			found_button	= true;
	}

	if (!found_button)
	{
		add_to_win(obj_list, WIN_BUTTON, "OK", color, NULL);
		return win(win_conf, obj_list, title, color);
	}

	structuring_obj(win_conf, obj_list, win_posX, win_posY, win_posXmax, win_posYmax);

	top_line = 0;
	bot_line = top_line + (win_posYmax - 2);

	while (cycle)
	{
		if (refresh_obj)
		{
			for (unsigned int i = 0; i < obj_list.size(); i++)
			{
				if (((obj_list[i].point_to_struct->posY >= top_line) && (obj_list[i].point_to_struct->posY <= bot_line)) && (obj_list[i].point_to_struct->active_obj))
				{
					temp_item	= obj_list[i];

					if (selected_obj == i)
					{
						selected_item	= temp_item;
						key_pressed		= temp_item.point_to_function(temp_item.point_to_struct, temp_item.text, temp_item.color_object);	// Вызов нужного объекта
					}
					else
					{
						temp_item.point_to_function(temp_item.point_to_struct, temp_item.text, temp_item.color_object);	// Вызов нужного объекта
					}

					if (selected_obj == i)
					{
						temp_item.point_to_struct->redraw	= false;
						obj_list[i]	= temp_item;
					}
				}
			}

			refresh_obj	= false;
		}
		else
		{
			key_pressed	= selected_item.point_to_function(selected_item.point_to_struct, selected_item.text, selected_item.color_object);	// Вызов нужного объекта
		}

		switch (key_pressed)
		{
			case H_KEY_ESC:	cycle		= false;
							break;

/*			case H_KEY_TAB:	obj_list[selected_obj].point_to_struct->redraw	= true;	// Перерисовать объект невыделенным	//!!!!!!!!!!!!!!!!АБСОЛЮТНАЯ ХЕРНЯ!!!!!!!!!!! УБРАТЬ ЭТО!!!!!!
							obj_list[selected_obj].point_to_function(obj_list[selected_obj].point_to_struct, obj_list[selected_obj].text, obj_list[selected_obj].color_object);	// Обновление элемента
							refresh_obj	= true;

							if (selected_obj != (obj_list.size() - 1)) {
								selected_obj++;
							} else {
								// selected_obj	= 0;
								selected_obj	= first_display_obj;	// ПОКА ТАК, ПОТОМ ИСПРАВИТЬ!!!!
							}

							if (selected_obj > last_display_obj) {
								display_next_obj_line(obj_list, first_display_obj, last_display_obj, win_posY, win_posYmax);
								clear_space(win_posX + 1, win_posY + 1, win_posXmax - win_posX - 2, win_posYmax - win_posY - 2);
								selected_obj	= 10;
							}

							break;
*/
			case KEY_UP:	if (key_up(obj_list, selected_obj, win_posY, win_posYmax, top_line))
							{
								refresh_obj	= true;
								bot_line = top_line + (win_posYmax - 2);
							}

							break;

			case KEY_DOWN:	if (key_down(obj_list, selected_obj, top_line))
							{
								refresh_obj	= true;
								bot_line = top_line + (win_posYmax - 2);
							}

							break;
		}
	}
	
	for (unsigned int	i	= 0; i < obj_list.size(); i++)	// От утечки памяти
	{
		temp_item	= obj_list[i];

		if (temp_item.memory_leak)
		{
			delete temp_item.point_to_struct;
		}
	}

	return returned_value;
}