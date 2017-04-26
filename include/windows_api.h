#ifndef WINDOWS_API_H
#define WINDOWS_API_H

	#include <string>
	#include <ncurses.h>
	#include <vector>
	#include "screen.h"
	
	#define WIN_EMPTY		0
	#define WIN_BUTTON		1
	#define WIN_TEXT_FIELD	2
	#define WIN_IPUT_TEXT	3
	#define WIN_TOP_BAR		4
	#define WIN_CHECKBOX	5
	#define WIN_MENU		6
	#define WIN_TABLE		7

	typedef	int	win_object;
	typedef	int	hotkey_t;

	struct WINOBJ
	{
		unsigned int	posX,
						posY,
						posYdisplay,
						posXmax,
						posYmax,
						std_selected,
						animation_delay;

		bool			redraw,
						manual_locator,
						user_init,
						active_obj;	// Выводится ли данный объект на экран или нет

		hotkey_t		obj_hotkey;	// Горячая кнопка

		void			*system_point;
	};

	struct list_of_objects
	{
		win_object	type_obj;

		int		(*point_to_function)(WINOBJ *, std::string, color_t);

		WINOBJ		*point_to_struct;

		std::string	text;

		color_t		color_object;

		unsigned int	display_posY,
						display_negative_posY;

		bool		memory_leak;
	};

	struct returned_str
	{
		std::vector<std::string>	*returned_text;	// Текст с текстовых полей
		int							key;
	};

	#define InitWINOBJ(name_var)	WINOBJ	name_var	= {}
	#define InitObjVec(name_var)	std::vector<list_of_objects>	name_var

	void add_to_win(std::vector<list_of_objects>&, win_object, std::string, color_t, WINOBJ*);
	returned_str win(WINOBJ*, std::vector<list_of_objects>, std::string, color_t);
	std::string get_ver_winapi();
#endif