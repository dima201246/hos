#include "internal_windlg.h"

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
int text_obj(WINOBJ *obj_conf, std::string text, color_t color)
{
	if (obj_conf->redraw)
	{
		if ((obj_conf->posXmax != 0) || (obj_conf->posYmax != 0)) {
			clear_space(obj_conf->posX, obj_conf->posYdisplay, obj_conf->posXmax + 1, obj_conf->posYmax + 1);			
			draw_box(1, "", 0, obj_conf->posX, obj_conf->posYdisplay, obj_conf->posXmax, obj_conf->posYmax, color, get_inv_color(color));
			// mvprintw(obj_conf->posYdisplay, obj_conf->posX, "!%s!", text.c_str());
		}
	}
	else
	{
		return getch();
	}

	return 0;
	// return button_obj(obj_conf, text, color);
}
/*TEXT FIELD END*/