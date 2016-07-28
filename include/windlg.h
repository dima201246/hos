#ifndef WINDLG_H
#define WINDLG_H

	#include <string>
	#include <vector>
	#include <unistd.h>
	#include <stdio.h>
	#include "lang.h"
	#include "screen.h"
	#include "system_defines.h"

	/*Styles*/
	#define WHITE_WIN	TEXT_WHITE_BLACK
	#define RED_WIN		TEXT_RED_BLACK
	#define GREEN_WIN	TEXT_GREEN_BLACK
	#define BLUE_WIN	TEXT_BLUE_BLACK
	#define YELLOW_WIN	TEXT_YELLOW_BLACK
	#define MAGENTA_WIN	TEXT_MAGENTA_BLACK
	#define CYAN_WIN	TEXT_CYAN_BLACK

	struct DLGSTR {
		std::string title, // Title
		line, // Text
		f_button, // Text on first button (maybe empty)
		s_button, // Text on second button (maybe empty)
		t_button; // Text on third button (maybe empty)
		int num_of_chars, // Maximum number of input characters (not work)
		type_input, // TYPE INPUT (not work)
		style, // STYLE
		keys, // Number of keys (1 - 3)
		fix_size; // Unknown
		unsigned int xpos, ypos,
		xmax, ymax,
		selected; // Initial choice
		unsigned int xreturn, yreturn, second_border;
		bool border_menu, active_menu, not_view_scrollbar;
	};
	
	int dlg_win(DLGSTR, std::string&);
	int msg_win(DLGSTR);
	void menu_win_old(DLGSTR&, std::vector<std::string>&);

	/*WINDLG 2.0*/
	struct MENSTR {
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
								std_selected;		// Позиция выделения
	};

	unsigned int menu_win(MENSTR*, std::string, std::vector <std::string>, color_t);

	#define Init_MENSTR(var_name) MENSTR var_name = {};
	/*WINDLG 2.0*/
	
	/* TYPE INPUT:
	0 - any signs
	1 - only numbers
	2 - only signs, not numbers
	3 - only letters, not special symbols, not numbers
	*/
	
	/* STYLE:
	0 - classic, white text
	1 - red text
	2 - green text
	3 - blue text
	4 - yellow text
	5 - magenta text
	6 - cyan text
	*/
#endif
