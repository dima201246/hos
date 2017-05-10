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

int text_obj(WINOBJ *obj_conf, std::string text, color_t color)
{
	std::vector<std::string> text_array;

	clear_space(obj_conf->posX, obj_conf->posYdisplay, obj_conf->posXmax, obj_conf->posYmax);

	if (obj_conf->redraw)
	{

		textParcer(text_array, text, obj_conf->posXmax - 5, 1);

		if ((obj_conf->posXmax != 0) || (obj_conf->posYmax != 0)) {
			mvprintw(obj_conf->posYdisplay + 1, obj_conf->posX + 1, "%s...", text_array[0].c_str());
		}
	}
	else
	{
		timeout(-1);

		int key = 0;

		unsigned int how_many = textParcer(text_array, text, obj_conf->posXmax - 2, obj_conf->posYmax - 3);
		
		draw_box(1, "", (how_many > (obj_conf->posYmax - 2) ? 1 : 0), obj_conf->posX, obj_conf->posYdisplay, obj_conf->posXmax, obj_conf->posYmax - 1, color, get_inv_color(color));

		for (unsigned int i = 0; i < text_array.size(); ++i)
		{
			mvprintw(obj_conf->posYdisplay + 1 + i, obj_conf->posX + 1, "%s", text_array[i].c_str());
		}

		key = getch();

		while ((key != H_KEY_ESC) && (key != H_KEY_TAB) && (key != KEY_LEFT) && (key != KEY_RIGHT))
		{
			/*switch (key)
			{
				case KEY_DOWN: if ()
			}*/

			key = getch();
		}

		return key;
	}

	return 0;
}
/*TEXT FIELD END*/