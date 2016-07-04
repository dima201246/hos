#ifndef SCREEN_H
#define SCREEN_H

	#include <curses.h>
	#include <string>

	extern	int	main_system_color,
				main_system_color_selection;

	void init_display();
	void init_color();
	void get_normal_inv_color(std::string /*Строка с названием цвета*/, int&/*Код цвета*/, int&/*Инвертированный цвет*/);
	int get_inv_color(int);

	/*Colors*/
	#define TEXT_WHITE_BLACK	0
	#define TEXT_WHITE_YELLOW	1
	#define TEXT_WHITE_BLUE		2
	#define TEXT_WHITE_GREEN	3
	#define TEXT_WHITE_RED		4
	#define TEXT_WHITE_MAGENTA	5
	#define TEXT_WHITE_CYAN		6

	#define TEXT_BLACK_WHITE	7
	#define TEXT_BLACK_YELLOW	8
	#define TEXT_BLACK_BLUE		9
	#define TEXT_BLACK_GREEN	10
	#define TEXT_BLACK_RED		11
	#define TEXT_BLACK_MAGENTA	12
	#define TEXT_BLACK_CYAN		13

	#define TEXT_YELLOW_BLACK	15
	#define TEXT_BLUE_BLACK		16
	#define TEXT_GREEN_BLACK	17
	#define TEXT_RED_BLACK		18
	#define TEXT_MAGENTA_BLACK	19
	#define TEXT_CYAN_BLACK		20

	#define TEXT_YELLOW_WHITE	21
	#define TEXT_BLUE_WHITE		22
	#define TEXT_GREEN_WHITE	23
	#define TEXT_RED_WHITE		24
	#define TEXT_MAGENTA_WHITE	25
	#define TEXT_CYAN_WHITE		26
#endif  
