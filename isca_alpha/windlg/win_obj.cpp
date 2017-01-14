#include "internal_windlg.h"

int button_obj(WINOBJ *button_conf, std::string text, color_t color_button) {
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