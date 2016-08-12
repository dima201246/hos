#ifndef SCREEN_H
#define SCREEN_H

	#include <string>

	/*Types*/
	typedef int color_t;

	extern	int	main_system_color,
				main_system_color_selection;

	void init_display();
	void init_color();
	void get_normal_inv_color(std::string /*Строка с названием цвета*/, color_t&/*Код цвета*/, color_t&/*Инвертированный цвет*/);
	color_t get_inv_color(color_t);
	color_t	get_color_on_color(color_t, color_t);


	/*Colors*/
	#define TEXT_WHITE_BLACK	0
	#define TEXT_YELLOW_BLACK	1
	#define TEXT_BLUE_BLACK		2
	#define TEXT_GREEN_BLACK	3
	#define TEXT_RED_BLACK		4
	#define TEXT_MAGENTA_BLACK	5
	#define TEXT_CYAN_BLACK		6

	#define TEXT_BLACK_WHITE	7
	#define TEXT_YELLOW_WHITE	8
	#define TEXT_BLUE_WHITE		9
	#define TEXT_GREEN_WHITE	10
	#define TEXT_RED_WHITE		11
	#define TEXT_MAGENTA_WHITE	12
	#define TEXT_CYAN_WHITE		13

	#define TEXT_WHITE_YELLOW	14
	#define TEXT_BLACK_YELLOW	15
	#define TEXT_BLUE_YELLOW	16
	#define TEXT_GREEN_YELLOW	17
	#define TEXT_RED_YELLOW		18
	#define TEXT_MAGENTA_YELLOW	19
	#define TEXT_CYAN_YELLOW	20

	#define TEXT_WHITE_BLUE		21
	#define TEXT_BLACK_BLUE		22
	#define TEXT_YELLOW_BLUE	23
	#define TEXT_GREEN_BLUE		24
	#define TEXT_RED_BLUE		25
	#define TEXT_MAGENTA_BLUE	26
	#define TEXT_CYAN_BLUE		27

	#define TEXT_WHITE_GREEN	28
	#define TEXT_BLACK_GREEN	29
	#define TEXT_YELLOW_GREEN	30
	#define TEXT_BLUE_GREEN		31
	#define TEXT_RED_GREEN		32
	#define TEXT_MAGENTA_GREEN	33
	#define TEXT_CYAN_GREEN		34

	#define TEXT_WHITE_RED		35
	#define TEXT_BLACK_RED		36
	#define TEXT_YELLOW_RED		37
	#define TEXT_BLUE_RED		38
	#define TEXT_GREEN_RED		39
	#define TEXT_MAGENTA_RED	40
	#define TEXT_CYAN_RED		41

	#define TEXT_WHITE_MAGENTA	42
	#define TEXT_BLACK_MAGENTA	43
	#define TEXT_YELLOW_MAGENTA	44
	#define TEXT_BLUE_MAGENTA	45
	#define TEXT_GREEN_MAGENTA	46
	#define TEXT_RED_MAGENTA	47
	#define TEXT_CYAN_MAGENTA	48

	#define TEXT_WHITE_CYAN		49
	#define TEXT_BLACK_CYAN		50
	#define TEXT_YELLOW_CYAN	51
	#define TEXT_BLUE_CYAN		52
	#define TEXT_GREEN_CYAN		53
	#define TEXT_RED_CYAN		54
	#define TEXT_MAGENTA_CYAN	55

	#define	coloron(color_id) attron(COLOR_PAIR(color_id) | A_BOLD)
	#define	coloroff(color_id) attroff(COLOR_PAIR(color_id) | A_BOLD)

#endif