#include "internal_windlg.h"
#include "../../include/system_defines.h"
#include "../../include/isca_alpha.h"

const unsigned int FREE_SPACE_Y = 2;

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

		case WIN_TEXT_FIELD:	temp_value.point_to_function	= &text_obj;
							temp_value.type_obj				= WIN_TEXT_FIELD;
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

nearest_obj close_side_obj(list_of_objects *first_obj, list_of_objects *second_obj)
{
	unsigned int	f_size_x,
					f_size_y,
					s_size_x,
					s_size_y;

	nearest_obj		temp = {};

	get_obj_size(*first_obj, f_size_x, f_size_y);
	get_obj_size(*second_obj, s_size_x, s_size_y);
	
	for (unsigned int i = first_obj->point_to_struct->posY; i <= (first_obj->point_to_struct->posY + f_size_y); ++i)	// Цикл проверяющий каждый "пиксель" уже выделенного объекта
	{
		if (((i >= second_obj->point_to_struct->posY) && (i <= (second_obj->point_to_struct->posY + s_size_y))))
		{
			temp = {
				.obj = second_obj,	// Сохранение ссылки на объект
				.num = i,	// Сохранение номера объекта в векторе
				.size = 0,
			};

			if (first_obj->point_to_struct->posY <= second_obj->point_to_struct->posY)
			{
				if ((first_obj->point_to_struct->posY + f_size_x) <= (second_obj->point_to_struct->posY + s_size_y))
				{
					temp.size	= (((second_obj->point_to_struct->posY - first_obj->point_to_struct->posY) > s_size_y) ? ((second_obj->point_to_struct->posY - first_obj->point_to_struct->posY) - s_size_y) : (s_size_y - (second_obj->point_to_struct->posY - first_obj->point_to_struct->posY)));
				}

				else
				{
					temp.size	= s_size_y;
				}
			}
			else
			{
				temp.size	= (((first_obj->point_to_struct->posY - second_obj->point_to_struct->posY) > s_size_y) ? ((first_obj->point_to_struct->posY - second_obj->point_to_struct->posY) - s_size_y) : (s_size_y - (first_obj->point_to_struct->posY - second_obj->point_to_struct->posY)));
			}

			break;
		}
	}

	return temp;
}

nearest_obj close_obj(list_of_objects *first_obj, list_of_objects *second_obj)
{
	unsigned int	f_size_x,
					f_size_y,
					s_size_x,
					s_size_y;

	nearest_obj		temp = {};

	get_obj_size(*first_obj, f_size_x, f_size_y);
	get_obj_size(*second_obj, s_size_x, s_size_y);
	
	for (unsigned int i = first_obj->point_to_struct->posX; i <= (first_obj->point_to_struct->posX + f_size_x); ++i)	// Цикл проверяющий каждый "пиксель" уже выделенного объекта
	{
		if (((i >= second_obj->point_to_struct->posX) && (i <= (second_obj->point_to_struct->posX + s_size_x))))
		{
			temp = {
				.obj = second_obj,	// Сохранение ссылки на объект
				.num = i,	// Сохранение номера объекта в векторе
				.size = 0,
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

			break;
		}
	}

	return temp;
}

void obj_up(vector<list_of_objects> &obj_list, unsigned int selected_obj, unsigned int win_posY, unsigned int win_posYmax, unsigned int &top_line, unsigned int &bot_line)
{
	unsigned int temp_x, temp_y;

	get_obj_size(obj_list[selected_obj], temp_x, temp_y);

	top_line = obj_list[selected_obj].point_to_struct->posY - 1;	// Изменение области видимых объектов
	bot_line = top_line + (win_posYmax - (((win_posYmax % 2) == 0) ? 3 : 2));

	for (unsigned int i = 0; i < obj_list.size(); i++)	// Сдвиг всех объектов, которые находятся в поле зрения
	{
		if ((obj_list[i].point_to_struct->posY > top_line) && (obj_list[i].point_to_struct->posY <= bot_line))
		{
			obj_list[i].point_to_struct->posYdisplay = obj_list[i].point_to_struct->posY;
			obj_list[i].point_to_struct->posYdisplay -= top_line - 1;
		}
	}
}

void obj_down(vector<list_of_objects> &obj_list, unsigned int selected_obj, unsigned int win_posY, unsigned int win_posYmax, unsigned int &top_line, unsigned int &bot_line)
{			
	unsigned int temp_x, temp_y;

	get_obj_size(obj_list[selected_obj], temp_x, temp_y);

	top_line += temp_y + ((top_line == win_posY + 1) ? 0 : 1);	// Изменение области видимых объектов
	bot_line = top_line + (win_posYmax - (((win_posYmax % 2) == 0) ? 2 : 1));

	for (unsigned int i = 0; i < obj_list.size(); i++)	// Сдвиг всех объектов, которые находятся в поле зрения
	{
		if ((obj_list[i].point_to_struct->posY > top_line) && (obj_list[i].point_to_struct->posY < bot_line))
		{
			obj_list[i].point_to_struct->posYdisplay = obj_list[i].point_to_struct->posY;
			obj_list[i].point_to_struct->posYdisplay -= top_line;
		}
	}
}

bool key_left(vector<list_of_objects> obj_list, unsigned int &selected_obj, unsigned int win_posY, unsigned int win_posYmax, unsigned int &top_line, unsigned int &bot_line)
{
	std::vector<nearest_obj> obj_bank;

	nearest_obj temp_close_obj;

	unsigned int	x_size_selected,
					y_size_selected;

	// Поиск кнопки левее Начало
	get_obj_size(obj_list[selected_obj], x_size_selected, y_size_selected);	// Узнаём размеры выделенного объекта

	for (unsigned int i = 0; i < obj_list.size(); ++i)	// Проверяем все объекты левее объекта
	{
		if ((obj_list[i].point_to_struct->active_obj) && (obj_list[i].point_to_struct->posX < obj_list[selected_obj].point_to_struct->posX))	// Небольшая оптимизация, чтобы проверялись только объекты левее выделенного
		{
			temp_close_obj = close_side_obj(&obj_list[selected_obj], &obj_list[i]);

			if (temp_close_obj.size != 0)
			{
				temp_close_obj.num = i;
				obj_bank.push_back(temp_close_obj);
			}
		}
	}
	// Поиск кнопки левее Конец

	if (obj_bank.size() > 0)
	{
		temp_close_obj = obj_bank[0];

		for (unsigned int i = 1; i < obj_bank.size(); ++i)	// Поиск самого близкого и с большим пересечением
		{
			if (temp_close_obj.obj->point_to_struct->posX <= obj_bank[i].obj->point_to_struct->posX)
			{
				if ((temp_close_obj.obj->point_to_struct->posX == obj_bank[i].obj->point_to_struct->posX) && (temp_close_obj.size <= obj_bank[i].size))
				{
					temp_close_obj = obj_bank[i];
				}
				else if (temp_close_obj.obj->point_to_struct->posX < obj_bank[i].obj->point_to_struct->posX)
				{
					temp_close_obj = obj_bank[i];
				}
			}
		}

		obj_list[selected_obj].point_to_struct->redraw = true;	// Перерисовка текущего выделенного объекта невыделенным
		selected_obj = temp_close_obj.num;
		obj_list[selected_obj].point_to_struct->redraw = true;	// Перерисовка нового выделенного объекта невыделенным

		return true;
	}

	if (obj_bank.size() == 0)
	{
		temp_close_obj = {};

		for (unsigned int i = 0; i < obj_list.size(); ++i)
		{
			if ((obj_list[i].point_to_struct->active_obj) && (obj_list[i].point_to_struct->posY < obj_list[selected_obj].point_to_struct->posY))
			{
				if (temp_close_obj.size == 0)
				{
					temp_close_obj.num = i;
					temp_close_obj.size = 1;
					temp_close_obj.obj = &obj_list[i];
				}
				else if (temp_close_obj.obj->point_to_struct->posY <= obj_list[i].point_to_struct->posY)
				{
					if ((temp_close_obj.obj->point_to_struct->posY == obj_list[i].point_to_struct->posY) && (temp_close_obj.obj->point_to_struct->posX < obj_list[i].point_to_struct->posX))
					{
						temp_close_obj.num = i;
						temp_close_obj.obj = &obj_list[i];
					}
					else if (temp_close_obj.obj->point_to_struct->posY < obj_list[i].point_to_struct->posY)
					{
						temp_close_obj.num = i;
						temp_close_obj.obj = &obj_list[i];	
					}
				}
			}
		}

		if (temp_close_obj.size != 0)
		{

			obj_list[selected_obj].point_to_struct->redraw = true;	// Перерисовка текущего выделенного объекта невыделенным
			selected_obj = temp_close_obj.num;
			obj_list[selected_obj].point_to_struct->redraw = true;	// Перерисовка нового выделенного объекта невыделенным
			// add_to_filef(MAIN_LOGFILE, "Text: %s\n", temp_close_obj.obj->text.c_str());

			if (obj_list[selected_obj].point_to_struct->posY <= top_line)	// Если объект находится за гранью видимого
			{
				obj_up(obj_list, selected_obj, win_posY, win_posYmax, top_line, bot_line);
			}

			return true;
		}
	}

	return false;
}

bool key_up(vector<list_of_objects> obj_list, unsigned int &selected_obj, unsigned int win_posY, unsigned int win_posYmax, unsigned int &top_line, unsigned int &bot_line)
{
	std::vector<nearest_obj> obj_bank;

	nearest_obj temp_close_obj;

	unsigned int	x_size_selected,
					y_size_selected;

	// Поиск кнопки выше Начало
	get_obj_size(obj_list[selected_obj], x_size_selected, y_size_selected);	// Узнаём размеры выделенного объекта

	for (unsigned int i = 0; i < obj_list.size(); ++i)	// Проверяем все объекты под объектом
	{
		if ((obj_list[i].point_to_struct->active_obj) && (obj_list[i].point_to_struct->posY < obj_list[selected_obj].point_to_struct->posY))	// Небольшая оптимизация, чтобы проверялись только объекты ниже выделенного
		{
			temp_close_obj = close_obj(&obj_list[selected_obj], &obj_list[i]);

			if (temp_close_obj.size != 0)
			{
				temp_close_obj.num = i;
				obj_bank.push_back(temp_close_obj);
			}
		}
	}
	// Поиск кнопки выше Конец

	if (obj_bank.size() > 0)
	{
		temp_close_obj = obj_bank[0];

		for (unsigned int i = 1; i < obj_bank.size(); ++i)	// Поиск самого близкого и с большим пересечением
		{
			if (temp_close_obj.obj->point_to_struct->posY <= obj_bank[i].obj->point_to_struct->posY)
			{
				if ((temp_close_obj.obj->point_to_struct->posY == obj_bank[i].obj->point_to_struct->posY) && (temp_close_obj.size <= obj_bank[i].size))
				{
					temp_close_obj = obj_bank[i];
				}
				else if (temp_close_obj.obj->point_to_struct->posY < obj_bank[i].obj->point_to_struct->posY)
				{
					temp_close_obj = obj_bank[i];
				}
			}
		}

		obj_list[selected_obj].point_to_struct->redraw = true;	// Перерисовка текущего выделенного объекта невыделенным
		selected_obj = temp_close_obj.num;
		obj_list[selected_obj].point_to_struct->redraw = true;	// Перерисовка нового выделенного объекта невыделенным

		if (obj_list[selected_obj].point_to_struct->posY <= top_line)	// Если объект находится за гранью видимого
		{
			obj_up(obj_list, selected_obj, win_posY, win_posYmax, top_line, bot_line);
		}

		return true;
	}

	return false;
}

bool key_right(vector<list_of_objects> obj_list, unsigned int &selected_obj, unsigned int win_posY, unsigned int win_posYmax, unsigned int &top_line, unsigned int &bot_line)
{
	std::vector<nearest_obj> obj_bank;

	nearest_obj temp_close_obj = {};

	unsigned int	x_size_selected,
					y_size_selected;

	// Поиск кнопки левее Начало
	get_obj_size(obj_list[selected_obj], x_size_selected, y_size_selected);	// Узнаём размеры выделенного объекта

	for (unsigned int i = 0; i < obj_list.size(); ++i)	// Проверяем все объекты левее объекта
	{
		if ((obj_list[i].point_to_struct->active_obj) && (obj_list[i].point_to_struct->posX > obj_list[selected_obj].point_to_struct->posX))	// Небольшая оптимизация, чтобы проверялись только объекты левее выделенного
		{
			temp_close_obj = close_side_obj(&obj_list[selected_obj], &obj_list[i]);

			if (temp_close_obj.size != 0)
			{
				temp_close_obj.num = i;
				obj_bank.push_back(temp_close_obj);
			}
		}
	}
	// Поиск кнопки левее Конец

	if (obj_bank.size() > 0)
	{
		temp_close_obj = obj_bank[0];

		for (unsigned int i = 1; i < obj_bank.size(); ++i)	// Поиск самого близкого и с большим пересечением
		{
			if (temp_close_obj.obj->point_to_struct->posX >= obj_bank[i].obj->point_to_struct->posX)
			{
				if ((temp_close_obj.obj->point_to_struct->posX == obj_bank[i].obj->point_to_struct->posX) && (temp_close_obj.size <= obj_bank[i].size))
				{
					temp_close_obj = obj_bank[i];
				}
				else if (temp_close_obj.obj->point_to_struct->posX > obj_bank[i].obj->point_to_struct->posX)
				{
					temp_close_obj = obj_bank[i];
				}
			}
		}

		obj_list[selected_obj].point_to_struct->redraw = true;	// Перерисовка текущего выделенного объекта невыделенным
		selected_obj = temp_close_obj.num;
		obj_list[selected_obj].point_to_struct->redraw = true;	// Перерисовка нового выделенного объекта невыделенным

		return true;
	}

	if (obj_bank.size() == 0)
	{
		temp_close_obj = {};

		for (unsigned int i = 0; i < obj_list.size(); ++i)
		{
			if ((obj_list[i].point_to_struct->active_obj) && (obj_list[i].point_to_struct->posY > obj_list[selected_obj].point_to_struct->posY))
			{
				if (temp_close_obj.size == 0)
				{
					temp_close_obj.num = i;
					temp_close_obj.size = 1;
					temp_close_obj.obj = &obj_list[i];
				}
				else if (temp_close_obj.obj->point_to_struct->posY >= obj_list[i].point_to_struct->posY)
				{
					if ((temp_close_obj.obj->point_to_struct->posY == obj_list[i].point_to_struct->posY) && (temp_close_obj.obj->point_to_struct->posX > obj_list[i].point_to_struct->posX))
					{
						temp_close_obj.num = i;
						temp_close_obj.obj = &obj_list[i];
					}
					else if (temp_close_obj.obj->point_to_struct->posY > obj_list[i].point_to_struct->posY)
					{
						temp_close_obj.num = i;
						temp_close_obj.obj = &obj_list[i];	
					}
				}
			}
		}

		if (temp_close_obj.size != 0)
		{

			obj_list[selected_obj].point_to_struct->redraw = true;	// Перерисовка текущего выделенного объекта невыделенным
			selected_obj = temp_close_obj.num;
			obj_list[selected_obj].point_to_struct->redraw = true;	// Перерисовка нового выделенного объекта невыделенным
			// add_to_filef(MAIN_LOGFILE, "Text: %s\n", temp_close_obj.obj->text.c_str());

			if (obj_list[selected_obj].point_to_struct->posY >= bot_line)	// Если объект находится за гранью видимого
			{
				obj_down(obj_list, selected_obj, win_posY, win_posYmax, top_line, bot_line);
			}

			return true;
		}
	}

	return false;
}

bool key_down(vector<list_of_objects> obj_list, unsigned int &selected_obj, unsigned int win_posY, unsigned int win_posYmax, unsigned int &top_line, unsigned int &bot_line)
{
	std::vector<nearest_obj> obj_bank;

	nearest_obj temp_close_obj;

	unsigned int	x_size_selected,
					y_size_selected;

	// Поиск кнопки ниже Начало
	get_obj_size(obj_list[selected_obj], x_size_selected, y_size_selected);	// Узнаём размеры выделенного объекта

	for (unsigned int i = 0; i < obj_list.size(); ++i)	// Проверяем все объекты под объектом
	{
		if ((obj_list[i].point_to_struct->active_obj) && (obj_list[i].point_to_struct->posY > obj_list[selected_obj].point_to_struct->posY))	// Небольшая оптимизация, чтобы проверялись только объекты ниже выделенного
		{
			temp_close_obj = close_obj(&obj_list[selected_obj], &obj_list[i]);

			if (temp_close_obj.size != 0)
			{
				temp_close_obj.num = i;
				obj_bank.push_back(temp_close_obj);
			}
		}
	}
	// Поиск кнопки ниже Конец

	if (obj_bank.size() > 0)
	{
		temp_close_obj = obj_bank[0];

		for (unsigned int i = 1; i < obj_bank.size(); ++i)	// Поиск самого близкого и с большим пересечением
		{
			if (temp_close_obj.obj->point_to_struct->posY >= obj_bank[i].obj->point_to_struct->posY)
			{
				if ((temp_close_obj.obj->point_to_struct->posY == obj_bank[i].obj->point_to_struct->posY) && (temp_close_obj.size <= obj_bank[i].size))
				{
					temp_close_obj = obj_bank[i];
				}
				else if (temp_close_obj.obj->point_to_struct->posY > obj_bank[i].obj->point_to_struct->posY)
				{
					temp_close_obj = obj_bank[i];
				}
			}
		}

		obj_list[selected_obj].point_to_struct->redraw = true;	// Перерисовка текущего выделенного объекта невыделенным
		selected_obj = temp_close_obj.num;
		obj_list[selected_obj].point_to_struct->redraw = true;	// Перерисовка нового выделенного объекта невыделенным

		if (obj_list[selected_obj].point_to_struct->posY >= bot_line)	// Если объект находится за гранью видимого
		{
			obj_down(obj_list, selected_obj, win_posY, win_posYmax, top_line, bot_line);
		}

		return true;
	}

	return false;
}

list_of_objects	*collision(std::vector<list_of_objects> &obj_list, unsigned int num, unsigned int x, unsigned int y)
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
				{
/*add_to_filef(MAIN_LOGFILE, "-> INPUT Text: %s\n", obj_list[num].text.c_str());
add_to_filef(MAIN_LOGFILE, "Text: %s\n", obj_list[i].text.c_str());*/
					return &obj_list[i];
				}
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
						free_space_y	= FREE_SPACE_Y;	// Отступ между объектами по вертикали

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
						unsigned int	temp_size_x,
										temp_size_y;

					get_obj_size(*collision_obj, temp_size_x, temp_size_y);

					if (collision_obj->type_obj == temp_item->type_obj)	// Совпадает ли тип объекта с которым соприкоснулся текущий объект или нет
					{
						if ((collision_obj->point_to_struct->posX + temp_size_x + free_space_x + size_obj_x) < endX)	// Разместить сразу за объектом, если хватает места
						{
							ahead_pos_x	= collision_obj->point_to_struct->posX + temp_size_x + free_space_x;
						}
						else
						{
							ahead_pos_x	= startX + indent_x;
							ahead_pos_y	= collision_obj->point_to_struct->posY + FREE_SPACE_Y;
						}
					}
					else
					{
						ahead_pos_x	= startX + indent_x;
						ahead_pos_y	= collision_obj->point_to_struct->posY + FREE_SPACE_Y + temp_size_y;
					}
				}

				temp_item->point_to_struct->posX = ahead_pos_x;
				temp_item->point_to_struct->posY = ahead_pos_y;
				temp_item->point_to_struct->posYdisplay = ahead_pos_y;

				ahead_pos_x		+= size_obj_x + free_space_x;
				ahead_type_obj	= temp_item->type_obj;
			}
			else
			{
				temp_item->point_to_struct->posYdisplay = temp_item->point_to_struct->posY;
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

	top_line = win_posY + 1;
	bot_line = win_posY + win_posYmax - (((win_posYmax % 2) == 0) ? 2 : 1);

	while (cycle)
	{
		if (refresh_obj)
		{
			clear_space(win_posX + 1, win_posY + 1, win_posXmax - 2, win_posYmax - 2);

			for (unsigned int i = 0; i < obj_list.size(); i++)
			{
				if (((obj_list[i].point_to_struct->posY > top_line) && (obj_list[i].point_to_struct->posY < bot_line)) && (obj_list[i].point_to_struct->active_obj))
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

			case H_KEY_TAB:	if (key_right(obj_list, selected_obj, win_posY, win_posYmax, top_line, bot_line))
							{
								refresh_obj	= true;
							}
							break;

			case KEY_UP:	if (key_up(obj_list, selected_obj, win_posY, win_posYmax, top_line, bot_line))
							{
								refresh_obj	= true;
							}
							break;

			case KEY_DOWN:	if (key_down(obj_list, selected_obj, win_posY, win_posYmax, top_line, bot_line))
							{
								refresh_obj	= true;
							}
							break;

			case KEY_RIGHT:	if (key_right(obj_list, selected_obj, win_posY, win_posYmax, top_line, bot_line))
							{
								refresh_obj	= true;
							}
							break;

			case KEY_LEFT:	if (key_left(obj_list, selected_obj, win_posY, win_posYmax, top_line, bot_line))
							{
								refresh_obj	= true;
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