#ifndef ISCA_ALPHA_H
#define ISCA_ALPHA_H

	#include <string>
	#include <ncurses.h>
	#include <vector>

	#define WIN_BUTTON		1
	#define WIN_TEXT_FIELD	2
	#define WIN_IPUT_TEXT	3
	#define WIN_TOP_BAR		4
	#define WIN_CHECKBOX	5
	#define WIN_MENU		6

	typedef	int	win_object;
	typedef	int	color_t;

	struct WINOBJ {
		unsigned int	posX,
						posY,
						posXmax,
						posYmax;

		bool			redraw;
	};

	struct list_of_objects {
		win_object	type_obj;

		void		(*point_to_function)(WINOBJ *, std::string, color_t);

		WINOBJ		*point_to_struct;

		std::string	text;

		color_t		color_object;
	};

/*	struct MENSTR {
		bool					no_border,			// Если не нужны границы окна !!!НЕИСПОЛЬЗОВАТЬ!!!
								redraw;				// Если нужно только перерисовать вывод

		int						returned_key;		// Возврат нажатой кнопки

		unsigned int			posX,				// Позиция окна
								posY,
								posXmax,			// Максимальные размеры окна
								posYmax,
								returned_x,			// Возвращаемая позиция выделения
								returned_y,
								animation_delay,	// Время анимации
								std_selected,		// Позиция выделения
								returned_selected;	// Номер выделенного элемента, даже если окно было закрыто без выбора
	};*/

	struct returned_str {
		int				key;
	};

	#define InitWINOBJ(name_var)	WINOBJ	name_var	= {}

	void add_to_win(std::vector<list_of_objects>&, win_object, std::string, color_t, WINOBJ*);
	returned_str win(WINOBJ*, std::vector<list_of_objects>);

#endif