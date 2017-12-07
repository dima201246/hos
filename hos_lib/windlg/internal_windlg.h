#ifndef INTERNAL_WINDLG_H
#define INTERNAL_WINDLG_H

	#include <string>
	#include "../../include/screen.h"
	#include "../../include/windows_api.h"

	void draw_box(	int				mode,
					std::string		title,
					unsigned int	progressBarPos,
					unsigned int	x,
					unsigned int	y,
					unsigned int	end_x,
					unsigned int	end_y,
					color_t			win_color_local,
					color_t			win_color_selected);

	int	windlg_input(unsigned int	max_size, unsigned int	&firstItem, unsigned int	&lastItem, unsigned int	&selected, bool	progressBar);
	void clear_space(unsigned int	start_x, unsigned int	start_y, unsigned int	end_x, unsigned int	end_y);
	void get_obj_size(list_of_objects	item, unsigned int &x, unsigned int &y);	// Получение предполагаемого размера объекта

	/*	Объекты для окна
	*	Передаём:
	*		- Указатель на конфиг для объекта
	*		- Текст, который находится в объекте
	*		- Цвет объекта
	*/
	int button_obj(WINOBJ *, std::string, color_t);
	int text_obj(WINOBJ *, std::string, color_t);

#endif