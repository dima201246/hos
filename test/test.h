#ifndef ISCA_ALPHA_H
#define ISCA_ALPHA_H

	#include <string>
	#include <ncurses.h>
	#include <vector>

	#define WIN_BUTTON	1
	#define TEXT_FIELD	2
	#define TEXT		3

	typedef	int	win_object;
	typedef	int	color_t;

	struct list_of_objects {
		win_object	type_obj;

		void		(*point_to_function)(void *, std::string, color_t);

		void		*point_to_struct;

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

	struct BUTSTR {
		unsigned int	posX,
						posY;

		bool			redraw;
	};

	struct WINSTR {
		unsigned int	posX,
						posY,
						posXmax,
						posYmax;
	};

	struct returned_str {
		int				key;
	};

	void add_to_win(std::vector<list_of_objects>&, win_object, std::string, color_t, void*);
	returned_str win(WINSTR*, std::vector<list_of_objects>);

#endif