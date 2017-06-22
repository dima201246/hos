#include "internal_windlg.h"
#include "../../include/isca_alpha.h"

void get_obj_size(list_of_objects	item, unsigned int &x, unsigned int &y) {	// Получение предполагаемого размера объекта
	if (item.point_to_struct->posXmax != 0)
		x = item.point_to_struct->posXmax;

	if (item.point_to_struct->posYmax != 0)
		y = item.point_to_struct->posYmax;

	switch (item.type_obj) {
		case WIN_BUTTON:	if (item.point_to_struct->posXmax == 0) {
								x	= item.text.length() + 2;
							}
							if (item.point_to_struct->posYmax == 0) {
								y	= 1;
							}
							break;

		case WIN_TEXT_FIELD:	if (item.point_to_struct->posXmax == 0) {
								x	= item.text.length() + 2;
							}
							if (item.point_to_struct->posYmax == 0) {
								y	= 1;
							}
							break;
	}
}

int button_obj(WINOBJ *button_conf, std::string text, color_t color_button) {
	if (button_conf->redraw) {
		coloron(color_button);
		if ((button_conf->posXmax != 0) || (button_conf->posYmax != 0)) {
			if (button_conf->posXmax == 0)
				button_conf->posXmax = 1;

			if (button_conf->posYmax == 0)
				button_conf->posYmax = 1;

			clear_space(button_conf->posX, button_conf->posYdisplay, button_conf->posXmax + 1, button_conf->posYmax);			
			mvprintw(button_conf->posYdisplay, button_conf->posX, "[%s]", text.c_str());
		} else {
			mvprintw(button_conf->posYdisplay, button_conf->posX, "[%s]", text.c_str());
		}
		coloroff(color_button);
	} else {
		coloron(get_inv_color(color_button));
		if ((button_conf->posXmax != 0) || (button_conf->posYmax != 0)) {
			if (button_conf->posXmax == 0)
				button_conf->posXmax = 1;

			if (button_conf->posYmax == 0)
				button_conf->posYmax = 1;

			clear_space(button_conf->posX, button_conf->posYdisplay, button_conf->posXmax + 1, button_conf->posYmax + 1);			
			mvprintw(button_conf->posYdisplay, button_conf->posX, ">%s<", text.c_str());
		} else {
			mvprintw(button_conf->posYdisplay, button_conf->posX, ">%s<", text.c_str());
		}
		coloroff(get_inv_color(color_button));
		return getch();
	}

	return 0;
}

/*TEXT FIELD START*/
unsigned int textParcer(std::vector<std::string> &text_array, std::string text, unsigned int maxY, unsigned int last_string)
{
	unsigned int count = 0;

	std::string temp_string = text;

	unsigned int return_num = 0;

	text_array.clear();

	if ((text.length() != 0) && (text.length() > maxY))
	{
		return_num = ((double)((double)text.length() / (double)maxY) + 0.999999);
	}

	while (text.length() > maxY)
	{
		temp_string.erase(maxY, text.length());
		text.erase(0, maxY);
		text_array.push_back(temp_string);
		temp_string = text;
		count++;

		if ((last_string != 0) && (count > last_string))
			break;
	}

	if ((!text.empty()) && (count <= last_string))
		text_array.push_back(text);

	return return_num;
}

unsigned int view_text(WINOBJ *obj_conf, std::vector<std::string> &text_array, std::string text, color_t color, unsigned int num_start, unsigned int num_end)
{
	unsigned int count_str = 0;

	clear_space(obj_conf->posX, obj_conf->posYdisplay, obj_conf->posXmax, obj_conf->posYmax);

	unsigned int how_many = textParcer(text_array, text, obj_conf->posXmax - 2, num_end);

	draw_box(1, "", (how_many > (obj_conf->posYmax - 2) ? (obj_conf->posYdisplay + 1) : 0), obj_conf->posX, obj_conf->posYdisplay, obj_conf->posXmax, obj_conf->posYmax - 1, color, get_inv_color(color));

	for (unsigned int i = num_start; i <= num_end; ++i)
	{
		mvprintw(obj_conf->posYdisplay + 1 + count_str, obj_conf->posX + 1, "%s", text_array[i].c_str());
		count_str++;
	}

	draw_box(2, "", (((num_end * obj_conf->posYmax - 2) / how_many) + (obj_conf->posY)), obj_conf->posX, obj_conf->posYdisplay, obj_conf->posXmax, obj_conf->posYmax - 1, color, get_inv_color(color));

	return how_many;
}

int text_obj(WINOBJ *obj_conf, std::string text, color_t color)
{
	std::vector<std::string> text_array;

	clear_space(obj_conf->posX, obj_conf->posYdisplay, obj_conf->posXmax, obj_conf->posYmax);

	if (obj_conf->redraw)
	{
		textParcer(text_array, text, obj_conf->posXmax - 5, 1);
		mvprintw(obj_conf->posYdisplay + 1, obj_conf->posX + 1, "%s...", text_array[0].c_str());
	}
	else
	{
		int key = 0;
		unsigned int pos_str_start = 0,
					 pos_str_end = obj_conf->posYmax - 3;

		timeout(-1);
		unsigned int max_num = view_text(obj_conf, text_array, text, color, pos_str_start, pos_str_end);

		key = getch();

		while ((key != H_KEY_ESC) && (key != H_KEY_TAB) && (key != KEY_LEFT) && (key != KEY_RIGHT))
		{
			switch (key)
			{
				case KEY_UP:	if (pos_str_start != 0)
								{
									pos_str_start--;
									pos_str_end--;
									view_text(obj_conf, text_array, text, color, pos_str_start, pos_str_end);
								}
								break;

				case KEY_DOWN:	if ((max_num - 1) > pos_str_end)
								{
									pos_str_start++;
									pos_str_end++;
									view_text(obj_conf, text_array, text, color, pos_str_start, pos_str_end);
								}
								break;
			}

			key = getch();
		}

		return key;
	}

	return 0;
}
/*TEXT FIELD END*/